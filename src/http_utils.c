#include "../include/http_utils.h"


string *decodeURL(string *url) {
    char *decodedChars = calloc(url->len + 1, sizeof(char));
    size_t copyIndex = 0;

    for (size_t i = 0; i < url->len; i++) {

        if (url->str[i] == '%') {
            string *numbers = sub_str(url, i + 1, 2);

            if (chars_equal_str(numbers, "20")) {
                decodedChars[copyIndex++] = ' ';
            }else{
                decodedChars[copyIndex++] = '?';
            }

            free_str(numbers);
            i += 2;
            continue;
        }

        decodedChars[copyIndex++] = url->str[i];
    }
    decodedChars[copyIndex] = '\0';

    string *decoded = cpy_str(decodedChars);
    free(decodedChars);
    return decoded;
}