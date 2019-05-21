#ifndef HTTP_SERVER_09_HTTP_SECURITY_H
#define HTTP_SERVER_09_HTTP_SECURITY_H

#include "http_string.h"
#include "http_parser.h"

/**
 * @struct http_credentials
 *
 * Used to bundle a username and a password.
 */
typedef struct credentials {
    string *user;
    string *password;
} http_credentials;



/**
 * Creates (allocates) a new httpCredential and returns a pointer to it.
 * @return The pointer to the allocated httpCredential.
 */
http_credentials *new_httpCredentials();


/**
 * Frees the memory allocated for the httpRequest pointer.
 * @param request The request pointer to free.
 */
void free_httpCredentials(http_credentials *credentials);


#endif //HTTP_SERVER_09_HTTP_SECURITY_H
