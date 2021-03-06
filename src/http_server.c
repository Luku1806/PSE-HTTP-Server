
#include "../include/http_string.h"
#include "../include/http_error.h"
#include "../include/http_parser.h"
#include "../include/http_settings.h"

/* Version: 2.1.2 */
#include <errno.h>      // errno
#include <netinet/ip.h> // ^
#include <signal.h>     // sigaction, struct sigaction, siginfo_t, SIGTERM
#include <stdbool.h>    // bool
#include <stdio.h>      // fprintf
#include <stdlib.h>     // exit, malloc, free
#include <string.h>     // memset, strerror
#include <unistd.h> // read, write, close


/**
 * Globale Variablen.
 */
static bool run = true;

/**
 * Behandlung des SIGINT-Signals (Strg+C) um den Server zu beenden.
 */
static void handle_signal(int signum) {
    if (signum != SIGINT) {
        error("ERROR unexpected signal");
    }

    /*
     * Beende den Server nach dem Abarbeiten des letzten Clients.
     */
    run = false;
}

/**
 * Registriert das SIGINT-Signal (Strg+C) um den Server beenden zu können.
 */
static void register_signal() {
    struct sigaction action;

    /*
     * Konfigurieren des Signal-Handlers.
     */
    memset(&action, 0, sizeof(action));
    action.sa_handler = handle_signal;

    /*
     * Registrierung des Signal-Handlers.
     */
    if (sigaction(SIGINT, &action, NULL) < 0) {
        error("ERROR registering signal handler");
    }
}

/**
 * Erstellt und konfiguriert den Netzwerk-Socket, über den die Verbindungen
 * angenommen werden.
 */
static int setup_socket() {

#ifdef STDIN_ONLY
    return STDOUT_FILENO;
#endif

    int opt = 1;
    int sockfd = 0;
    struct sockaddr_in serv_addr;

    /*
     * Setzt Konfigurationsvariablen für den Socket, z.B. die Portnummer.
     */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    /*
     * Erstelle den Socket.
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    /*
     * Verwende den Socket, selbst wenn er aus einer vorigen Ausführung
     * im TIME_WAIT Status ist.
     */
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &opt,
                   sizeof(int)) < 0)
        error("ERROR on setsockopt");

    /*
     * Melde, dass der Socket eingehende Verbindungen akzeptieren soll.
     */
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    /*
     * Horche auf dem Socket nach eingehenden Verbindungen. Es werden maximal
     * fünf gleichzeitige Verbindungen erlaubt.
     */
    if (listen(sockfd, 5) < 0) {
        error("listen");
    }
    return sockfd;
}

/**
 * Die Hauptschleife, in der eingehende Verbindungen angenommen werden.
 */
static void main_loop(int sockfd) {
    int newsockfd;
    ssize_t length;

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    void *const buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        error("ERROR at malloc.");
    }

    /*
     * Die Hauptshleife des Programms.
     */
    while (run) {

#ifndef STDIN_ONLY

        /*
         * Der accept()-Aufruf blockiert, bis eine neue Verbindung rein kommt.
         */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            /*
             * Wenn der Server mit dem SIGINT-Signal beendet wird, schlägt accept
             * mit EINTR (interrupted) fehl.
             */
            if (errno == EINTR) {
                break;
            }
            error("ERROR on accept");
        }

#else
        newsockfd = STDIN_FILENO;
#endif

        /*
         * Lies die ankommenden Daten von dem Socket in das Array buffer.
         */
        memset(buffer, 0, BUFFER_SIZE);
        length = read(newsockfd, buffer, BUFFER_SIZE - 1);
        if (length < 0) {
            if (errno == EINTR) {
                break;
            }
            error("ERROR reading from socket");
        }

        string requestString;
        requestString.str = buffer;
        requestString.len = (size_t) length; //TODO SSIZE_T oder SIZE_T?

        http_request *request = parseRequest(&requestString);

        // Decide if request is for a special site (at the moment only debug) and generate response
        http_response *response;

        // Decide if debug site should be send
        if (request != NULL && request->resource != NULL && chars_equal_str(request->resource, "/debug")) {
            response = generateDebugResponse(request);
        } else {
            response = generateResponse(request);
        }

        string *sendString = httpResponseToString(response);

#ifndef STDIN_ONLY

        /*
         * Schreibe die ausgehenden Daten auf den Socket.
         */
        length = write(newsockfd, sendString->str, sendString->len);
        if (length < 0) {
            error("ERROR writing to socket");
        }

        /*
         * Schließe die Verbindung.
         */
        if (close(newsockfd) < 0) {
            error("ERROR on close");
        }

#else
        /*
        * Gib die eingegangenen Daten auf der Kommandozeile aus.
        */
        if (write(STDOUT_FILENO, sendString->str, sendString->len) < 0) {
            error("ERROR writing to STDOUT");
        }

#endif

        /*
         * Free everything up
         */
        free_httpRequest(request);
        free_httpResponse(response);
        free_str(sendString);

    }

    /*
     * Lösche den Buffer und schließe den Socket. Dieser Aufruf sollte wegen der
     * Endlosschleife niemals ausgeführt werden.
     */
    free(buffer);

#ifndef STDIN_ONLY

    if (close(sockfd) < 0) {
        error("ERROR on close");
    }

#endif

}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    register_signal();
    const int sockfd = setup_socket();

    printf("Server started listening for connections on port %i...\n", PORT);
    fflush(stdout);

    main_loop(sockfd);

    return 0;
}
