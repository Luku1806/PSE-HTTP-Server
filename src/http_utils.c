#include "../include/http_utils.h"


char hexStringToChar(string *hex) {
    char val = 0;

    for (size_t i = 0; i < hex->len; i++) {
        if (hex->str[i] <= 57) {
            val += (hex->str[i] - 48) * (1 << (4 * (hex->len - 1 - i)));
        }else {
            val += (hex->str[i] - 55) * (1 << (4 * (hex->len - 1 - i)));
        }
    }

    return val;
}


string *decodeURL(string *url) {
    char *decodedChars = calloc(url->len + 1, sizeof(char));
    size_t copyIndex = 0;

    for (size_t i = 0; i < url->len - 2; i++) {

        if (url->str[i] == '%') {
            string *numbers = sub_str(url, i + 1, 2);

            int numbersDecimal = hexStringToChar(numbers);
            decodedChars[copyIndex++] = numbersDecimal;

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