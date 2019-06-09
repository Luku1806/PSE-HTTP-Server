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
 * @struct http_credential_array
 *
 * Used to store an array(pointer) to credential pointers together with the count of them.
 */
typedef struct credentialArray {
    http_credentials **credential_array;
    size_t credentialCount;
    size_t maxCredentialCount;
} http_credential_array;


/**
 * Creates (allocates) a new httpCredential and returns a pointer to it.
 * @return The pointer to the allocated httpCredential.
 */
http_credentials *new_httpCredentials();


/**
 * Frees the memory allocated for the httpCredential pointer.
 * @param request The credential pointer to free.
 */
void free_httpCredentials(http_credentials *credentials);


/**
 * Creates (allocates) a new http_credential_array of size max and returns a pointer to it.
 *
 * @param max The maximum of credentials this array can hold.
 * @return The pointer to the allocated http_credential_array.
 */
http_credential_array *new_httpCredentialArray(size_t max);


/**
 * Frees the memory allocated for the http_credential_array pointer.
 * @param request The credential_array pointer to free.
 */
void free_httpCredentialArray(http_credential_array *array);


/**
 * Adds a credential to the array. Returns 1 if the credentials fit into the array, 0 if its already full.
 *
 * @param credentialArray The array to add something to.
 * @param credentials The credentials pointer to add to the array.
 * @return 0 if array is already full, 1 if everything was okay.
 */
char credential_array_add(http_credential_array *credentialArray, http_credentials *credentials);


/**
 * Prints the given credentials to the console.
 * @param credentials The credentials to print to the console.
 */
void printHTTPCredentials(http_credentials *credentials);

/**
 * Prints the given credential array (all credentials it contains) to the console.
 * @param credentials The credential array to print to the console.
 */
void printHTTPCredentialArray(http_credential_array *credentialArray);


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


http_credential_array *loadCredentials();

#endif //HTTP_SERVER_09_HTTP_SECURITY_H
