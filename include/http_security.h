#ifndef HTTP_SERVER_09_HTTP_SECURITY_H
#define HTTP_SERVER_09_HTTP_SECURITY_H

#include "http_string.h"
#include "http_parser.h"


/**
 * @file http_fileIO.h
 * @brief This file contains functions and data structures to implement basic HTTP authentication and SHA1 encryption.
 */


/**
 * @struct http_credentials
 *
 * @brief Used to bundle a username and a password.
 */
typedef struct credentials {
    string *user;     /**< @brief The username to store.*/
    string *password; /**< @brief The password corresponding to the username.*/
} http_credentials;


/**
 * @struct http_credential_array
 *
 * @brief Used to store an array(pointer) to credential pointers together with the count of them.
 *
 * New credentials should only be added by calling credential_array_add(), to be sure to not overflow the array.
 * The memory for all credentials up to maxCredentialCount is allocated when creating a new one by calling new_httpCredentialArray().
 */
typedef struct credentialArray {
    http_credentials **credential_array; /**< @brief An array/pointer of credential pointers.*/
    size_t credentialCount;              /**< @brief The currently stored credentials. Should always be <= maxCredentialCount, otherwise an overflow will happen.*/
    size_t maxCredentialCount;           /**< @brief The maximum number of credentials to store, and so to allocate.*/
} http_credential_array;


/**
 * @brief Creates (allocates) a new httpCredential and returns a pointer to it.
 *
 * The allocated memory for the returned http_credentials has to be freed, when its no longer needed by calling free_httpCredentials()!
 *
 * @return The pointer to the allocated httpCredential.
 */
http_credentials *new_httpCredentials();


/**
 * @brief Frees the memory allocated for the httpCredential pointer.
 * @param request The credential pointer to free.
 */
void free_httpCredentials(http_credentials *credentials);


/**
 * @brief Creates (allocates) a new http_credential_array of size max and returns a pointer to it.
 *
 * The allocated memory for the returned credential_array has to be freed, when its no longer needed by calling free_httpCredentialArray()!
 *
 * @param max The maximum of credentials this array can hold.
 * @return The pointer to the allocated http_credential_array.
 */
http_credential_array *new_httpCredentialArray(size_t max);


/**
 * @brief Frees the memory allocated for the http_credential_array pointer, and also for any credential that is saved in there!
 * @param request The credential_array pointer to free.
 */
void free_httpCredentialArray(http_credential_array *array);


/**
 * @brief Adds a credential to the array. Returns 1 if the credentials fit into the array, 0 if its already full.
 *
 * @param credentialArray The array to add something to.
 * @param credentials The credentials pointer to add to the array.
 * @return 0 if array is already full, 1 if everything was okay.
 */
char credential_array_add(http_credential_array *credentialArray, http_credentials *credentials);


/**
 * @brief Prints the given credentials to the console.
 * @param credentials The credentials to print to the console.
 */
void printHTTPCredentials(http_credentials *credentials);

/**
 * @brief Prints the given credential array (all credentials it contains) to the console.
 * @param credentials The credential array to print to the console.
 */
void printHTTPCredentialArray(http_credential_array *credentialArray);


/**
 * @brief Hashes a string with SHA1 using openssl.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param toEncode The string to hash.
 * @return The hashed string.
 */
string *encodeSHA1(string *toEncode);


/**
 * @brief Reads the authentication credentials for basic authentication from a given request and returns them.
 * If authentication scheme is not Basic, no authentication credentials are given, or something is wrong about the credentials, NULL is returned.
 *
 * The allocated memory for the returned http_credentials has to be freed, when its no longer needed by calling free_httpCredentials()!
 *
 * @param request The request to get the credentials from.
 * @return The authentication credentials from the request. NULL if they are not set or something is bad about the syntax.
 */
http_credentials *getAuthenticationCredentials(http_request *request);


/**
 * @brief Checks the credentials against the all credentials of the .htpasswd file.
 * Returns 0 if no match was found, 1 if given credentials match an entry of the file.
 *
 * @param credentials The credentials to check if they exist in the .htpasswd file.
 * @return 0 if no match was found in the file, 1 if there was a match to an entry.
 */
char checkCredentials(http_credentials *credentials);


/**
 * @brief Loads a credential_array from the htpasswd file.
 * The credentials are loaded from the htpasswd file located at a path, specified by HTPASSWD_PATH in http_settings.h.
 *
 * If the htpasswd file doesnt exist, NULL is returned.
 * If the htpasswd file exists, but no credentials are found, an empty array is returned.
 *
 * The allocated memory for the returned credential_array has to be freed, when its no longer needed by calling free_httpCredentialArray()!
 *
 * @return The credential_array filled with all credentials from HTPASSWD. NULL if HTPASSWD doesnt exist.
 */
http_credential_array *loadCredentials();

#endif //HTTP_SERVER_09_HTTP_SECURITY_H
