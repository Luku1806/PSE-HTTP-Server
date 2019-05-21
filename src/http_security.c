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



