/**
 * @brief This file contains all project settings that can be made to the server.
 * It conatins all paths, the server port etc...
 */

#ifndef HTTP_SERVER_09_HTTP_SETTINGS_H



/********************** General **********************/

/**
 * The name of the server.
 */
#define SERVER_NAME "HTTP-Server 09 1.0"

/**
 * The http version of the server.
 */
#define HTTP_VERSION "HTTP/1.1"





/********************** Network **********************/

/**
 * The tcp port to listen on.
 * The server will be reachable at this port via http protocol
 */
#define PORT 31337


/**
 * The size of the buffer for reading http requests oover the tcp socket.
 * Should be big enough to be able to handle larger requests.
 */
#define BUFFER_SIZE 1024





/********************** Paths **********************/

/**
 * The default document root.
 */
#define DEFAULT_DOCUMENT_ROOT "/usr/local/webroot/default/"

/**
 * The extern document root.
 */
#define EXTERN_DOCUMENT_ROOT "/usr/local/webroot/extern/"

/**
 * The intern document root. To see files you have to authorize.
 */
#define INTERN_DOCUMENT_ROOT "/usr/local/webroot/intern/"


/**
 * The path where all status pages lay.
 */
#define STATUS_SITE_PATH "/usr/local/webroot/status/"


/**
 * The path where the htpasswd file, with all the http credential is located
 */
#define HTPASSWD_PATH "/usr/local/webroot/htpasswd"





/********************** Authorization **********************/

/**
 * The maximum count of credentials to load from the htpasswd file from disk.
 */
#define MAX_CREDENTIALS 15






#define HTTP_SERVER_09_HTTP_SETTINGS_H

#endif //HTTP_SERVER_09_HTTP_SETTINGS_H
