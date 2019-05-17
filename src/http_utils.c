#include "../include/http_utils.h"


char isAscii(char c) {
    return (48 <= c && c <= 57) || (65 <= c && c <= 70) || (97 <= c && c <= 102);
}


char hexStringToChar(string *hex) {
    char val = 0;

    for (size_t i = 0; i < hex->len; i++) {
        if (!isAscii(hex->str[i])) {
            return -1;
        } else if (hex->str[i] <= 57) {
            val += (hex->str[i] - 48) * (1 << (4 * (hex->len - 1 - i)));
        } else {
            val += (hex->str[i] - 55) * (1 << (4 * (hex->len - 1 - i)));
        }
    }

    return val;
}


string *decodeURL(string *url) {
    char *decodedChars = calloc(url->len + 1, sizeof(char));
    size_t copyIndex = 0;

    for (size_t i = 0; i < url->len; i++) {

        if (url->str[i] == '%' && i < url->len - 2) {
            string *numbers = sub_str(url, i + 1, 2);

            if (!(isAscii(numbers->str[0]) && isAscii(numbers->str[1]))) {
                free(decodedChars);
                free_str(numbers);
                return NULL; // Digits after the percent are not hex --> INVALID
            }

            int numbersDecimal = hexStringToChar(numbers);
            decodedChars[copyIndex++] = numbersDecimal;

            free_str(numbers);
            i += 2;
            continue;
        } else if (url->str[i] == '%') {
            free(decodedChars);
            return NULL; // Percent in one of the last two characters --> INVALID
        }

        decodedChars[copyIndex++] = url->str[i];
    }

    decodedChars[copyIndex] = '\0';

    string *decoded = cpy_str(decodedChars);
    free(decodedChars);
    return decoded;
}