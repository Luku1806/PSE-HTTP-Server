#include "../include/http_security.h"
#include "../include/http_error.h"
#include "../include/http_base64.h"
#include "../include/http_settings.h"

#include <stdlib.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <limits.h>

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


http_credential_array *new_httpCredentialArray(size_t max) {
    http_credential_array *array = calloc(max, sizeof(http_credential_array));
    if (array == NULL) error("Error allocating memory for HTTP credential itself");
    array->maxCredentialCount = max;
    array->credential_array = calloc(max, sizeof(http_credentials *));
    if (array->credential_array == NULL) error("Error allocating memory for HTTP credential array of size");
    return array;
}


void free_httpCredentialArray(http_credential_array *array) {
    if (array == NULL) return;

    for (int i = 0; i < array->credentialCount; i++) {
        free_httpCredentials(array->credential_array[i]); // Free every single credential
    }

    free(array->credential_array);
    free(array);
}


char credential_array_add(http_credential_array *credentialArray, http_credentials *credentials) {
    if (credentialArray->credentialCount < credentialArray->maxCredentialCount) {
        credentialArray->credential_array[credentialArray->credentialCount] = credentials;
        credentialArray->credentialCount++;
        return 1;
    } else {
        return 0;
    }
}


void printHTTPCredentials(http_credentials *credentials) {
    printf("Username:\t");
    print_string(credentials->user);
    printf(",\t");
    printf("Password:\t");
    print_string(credentials->password);
    printf("\n");
    //fflush(stdout);
}


void printHTTPCredentialArray(http_credential_array *credentialArray) {
    printf("Credential array:\n");
    for (int i = 0; i < credentialArray->credentialCount; i++) {
        printf("%i:\t", i);
        printHTTPCredentials(credentialArray->credential_array[i]);
    }
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


http_credential_array *loadCredentials() {
    FILE *file = fopen(HTPASSWD_PATH, "r");
    if (file != NULL) {
        http_credential_array *credentialArray = new_httpCredentialArray(MAX_CREDENTIALS);

        char line[LINE_MAX];
        while (fgets(line, sizeof(line), file) != NULL) {
            // Parse the line
            string *str_line = cpy_str(line);
            size_t endUser = find_chars(str_line, ":");

            // NO : --> Invalid line
            if (endUser == -1) {
                free_str(str_line);
                continue;
            }

            // Get the hashed password part
            string *hashedPw = sub_str(str_line, endUser + 1, str_line->len - (endUser + 2));

            // Nothing left behind the :
            if (hashedPw == NULL) {
                free_str(str_line);
                free_str(hashedPw);
                continue;
            }

            // Not a SHA hashed password
            if (!startsWith_str(hashedPw, "{SHA}")) {
                free_str(str_line);
                free_str(hashedPw);
                continue;
            }

            string *passwd = sub_str(hashedPw, 5, hashedPw->len - 5);

            // Line contains valid password, save it.
            if (passwd != NULL) {
                http_credentials *newCredentials = new_httpCredentials();
                newCredentials->password = passwd;
                newCredentials->user = sub_str(str_line, 0, endUser);
                if (!credential_array_add(credentialArray, newCredentials)) {
                    free_str(str_line);
                    free_str(hashedPw);
                    free_httpCredentials(newCredentials);
                    fprintf(stderr,
                            "Too many credentials found in htpasswd file.\nThe server is configured to only load up to %i credentials, the extra ones will be ignored.\nTo use them, increase the maximum credentials setting.\n",
                            MAX_CREDENTIALS);
                    return credentialArray; // Array is full anyway, stop parsing
                }
            }

            free_str(str_line);
            free_str(hashedPw);
        }

        fclose(file);
        return credentialArray;
    } else {
        fprintf(stderr, "Could not load htpasswd file from '%s'\n Does it even exist?\n", HTPASSWD_PATH);
        return NULL;
    }
}


char checkCredentials(http_credentials *credentials) {
    http_credential_array *validCredentials = loadCredentials(); // TODO Store them globally?
    if (validCredentials == NULL) return 0; // Credentials could not be loaded

    string *passHash = encodeSHA1(credentials->password);
    string *passHash64 = base64_encode_string(passHash);

    char userAuthenticated = 0;

    for (int i = 0; i < validCredentials->credentialCount; i++) {
        http_credentials *currentValid = validCredentials->credential_array[i];
        if (equals_str(currentValid->user, credentials->user) && equals_str(currentValid->password, passHash64)) {
            userAuthenticated = 1;
            break;
        }
    }


    free_str(passHash);
    free_str(passHash64);
    free_httpCredentialArray(validCredentials);

    return userAuthenticated;
}

