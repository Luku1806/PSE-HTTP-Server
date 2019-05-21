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