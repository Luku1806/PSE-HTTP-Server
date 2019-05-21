#include "../include/http_base64.h"
#include "../include/http_string.h"

#include <stdint.h>
#include <stdlib.h>


static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};


void build_decoding_table() {
    decoding_table = malloc(256);

    for (int i = 0; i < 64; i++) {
        decoding_table[(unsigned char) encoding_table[i]] = i;
    }
}


void base64_cleanup() {
    free(decoding_table);
    decoding_table = NULL;
}

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(*output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++) {
        encoded_data[*output_length - 1 - i] = '=';
    }
    encoded_data[*output_length] = '\0';

    return encoded_data;
}

string *base64_encode_string(string *toEncode) {
    size_t newLen;
    char *encodedChars = base64_encode(toEncode->str, toEncode->len, &newLen);

    string *encoded = cpy_str(encodedChars);
    free(encodedChars);

    return encoded;
}

string *base64_decode_string(string *toDecode) {
    size_t newLen;
    char *decodedChars = (char *) base64_decode(toDecode->str, toDecode->len, &newLen);

    if(decodedChars == NULL) return NULL; // String is not base64

    string *decoded = cpy_str(decodedChars);
    free(decodedChars);

    return decoded;
}
