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


/**
 * Prints the given credentials to the console.
 * @param credentials The credentials to print to the console.
 */
void printHTTPCredentials(http_credentials *credentials);


/**
 * Hashes a string with SHA1 using openssl.
 *
 * @param toEncode The string to hash.
 * @return The hashed string.
 */
string *encodeSHA1(string *toEncode);


/**
 * Reads the authentication credentials for basic authentication from a given request and returns them.
 * If authentication scheme is not Basic, no authentication credentials are given, or something is wrong about the credentials, NULL is returned.
 *
 * @param request The request to get the credentials from.
 * @return The authentication credentials from the request. NULL if they are not set or something is bad about the syntax.
 */
http_credentials *getAuthenticationCredentials(http_request *request);


/**
 * Checks the credentials against the all credentials of the .htpasswd file.
 * Returns 0 if no match was found, 1 if given credentials match an entry of the file.
 *
 * @param credentials The credentials to check if they exist in the .htpasswd file.
 * @return 0 if no match was found in the file, 1 if there was a match to an entry.
 */
char checkCredentials(http_credentials *credentials);




#endif //HTTP_SERVER_09_HTTP_SECURITY_H
