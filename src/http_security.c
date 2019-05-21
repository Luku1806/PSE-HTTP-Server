#include "../include/http_security.h"
#include "../include/http_string.h"
#include "../include/http_error.h"
#include "../include/http_parser.h"
#include "../include/http_base64.h"

#include <stdlib.h>
#include <openssl/sha.h>
#include <stdio.h>

http_credentials *new_httpCredentials() {
    http_credentials *credentials = calloc(1, sizeof(http_credentials));
    if (credentials == NULL) error("Error allocating memory for HTTP credentials");
    return credentials;
}


void free_httpCredentials(http_credentials *credentials) {
    if (credentials == NULL) return;

    free_str(credentials->user);
    free_str(credentials->password);

    free(credentials);
}


void printHTTPCredentials(http_credentials *credentials) {
    printf("Username: ");
    print_string(credentials->user);
    printf("\n");
    printf("Password: ");
    print_string(credentials->password);
    printf("\n");
    fflush(stdout);
}


string *encodeSHA1(string *toEncode) {
    string *hashed = new_string(SHA_DIGEST_LENGTH);
    SHA1((unsigned char *) toEncode->str, toEncode->len, (unsigned char *) hashed->str);
    return hashed;
}


http_credentials *getAuthenticationCredentials(http_request *request) {
    if (request->authentication == NULL) return NULL;

    string *authHeaderUpper = toUpper_str(request->authentication);

    if (startsWith_str(authHeaderUpper, "BASIC")) {
        free_str(authHeaderUpper);

        // Seperate the base64 encoded credentials
        // TODO Do it more dynamic
        int credentialsLen = request->authentication->len - 6;
        if (credentialsLen < 1) return NULL; // No credentials available
        string *credString = sub_str(request->authentication, 6, credentialsLen);

        // Decode the credentials part from base64
        string *decodedCred = base64_decode_string(credString);
        free_str(credString);
        if (decodedCred == NULL) return NULL; // Credentials not base64

        // Get end of username in string
        size_t usernameLenght = find_chars(decodedCred, ":");
        if (usernameLenght == -1) {
            return NULL; // No ':' seperated username found
        }

        // Check if password is left
        int passwordLen = decodedCred->len - (usernameLenght + 1);
        if (passwordLen < 1) {
            free_str(decodedCred);
            return NULL; // No password left
        }

        string *username = sub_str(decodedCred, 0, usernameLenght);
        string *password = sub_str(decodedCred, usernameLenght + 1, passwordLen);
        free_str(decodedCred);

        http_credentials *credentials = new_httpCredentials();
        credentials->user = username;
        credentials->password = password;

        return credentials;
    }

    free_str(authHeaderUpper);
    return NULL;
}



