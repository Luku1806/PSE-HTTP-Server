/**
 * @file http_settings.h
 *
 * @brief This file contains all project settings that can be made to the server.
 * It contains all paths, the server port and the server name.
 * To adjust these settings
 */

#ifndef HTTP_SERVER_09_HTTP_SETTINGS_H



/********************** General **********************/

/**
 * @def SERVER_NAME
 * @brief The name of the server.
 */
#define SERVER_NAME "HTTP-Server 09 1.0"


/**
 * @def HTTP_VERSION
 * @brief The http version of the server.
 */
#define HTTP_VERSION "HTTP/1.1"





/********************** Network **********************/

/**
 * @def PORT
 * @brief The tcp port to listen on.
 * The server will be reachable at this port via http protocol.
 */
#define PORT 31337


/**
 * @def BUFFER_SIZE
 * @brief The size of the buffer for reading http requests over the tcp socket.
 * Should be big enough to be able to handle larger requests.
 */
#define BUFFER_SIZE 1024





/********************** Paths **********************/

/**
 * @def DEFAULT_DOCUMENT_ROOT
 * @brief The default document root.
 * This folder should contain the website etc. that should be available if no, or a unknown host is requested.
 */
#define DEFAULT_DOCUMENT_ROOT "/usr/local/webroot/default/"


/**
 * @def EXTERN_DOCUMENT_ROOT
 * @brief The extern document root.
 * This folder should contain the website etc. that should be available if the host "extern" is requested.
 */
#define EXTERN_DOCUMENT_ROOT "/usr/local/webroot/extern/"


/**
 * @def INTERN_DOCUMENT_ROOT
 * @brief The intern document root.
 * This folder should contain the website etc. that should be available, if the host "intern" is requested.
 * To see files the client has to authorize with credentials that are stored in the htpasswd file.
 */
#define INTERN_DOCUMENT_ROOT "/usr/local/webroot/intern/"


/**
 * @def STATUS_SITE_PATH
 * @brief The path where all status pages lie.
 * Each status page is named after its status.
 * Each status has its own site, and any html file with a fitting name can be used.
 *
 * For example a page for status 505 is named: "505.html"
 */
#define STATUS_SITE_PATH "/usr/local/webroot/status/"


/**
 * @def HTPASSWD_PATH
 * @brief The path where the htpasswd file, with all the http credentials in it is located.
 *
 * This file can be created by the command: "htpasswd -s -c htpasswd [username]"
 * The server only supports SHA1 encrypted credentials, so keep in mind to set the -s
 * flag when creating credentials with htpasswd.
 */
#define HTPASSWD_PATH "/usr/local/webroot/htpasswd"





/********************** Authorization **********************/

/**
 * @def MAX_CREDENTIALS
 * @brief The maximum count of credentials to load from the htpasswd file from disk.
 * Keep in mind, that when having more credentials in the file than MAX_CREDENTIALS, they will be ignored,
 * so be sure to set it to an appropriate size, without wasting to much memory.
 */
#define MAX_CREDENTIALS 15


#define HTTP_SERVER_09_HTTP_SETTINGS_H

#endif //HTTP_SERVER_09_HTTP_SETTINGS_H
