#ifndef HTTP_SERVER_09_HTTP_BASE64_H
#define HTTP_SERVER_09_HTTP_BASE64_H

#include <stddef.h>
#include "http_string.h"

void build_decoding_table();

void base64_cleanup();

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);

unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);

string *base64_encode_string(string *toEncode);

string *base64_decode_string(string *toDecode);

#endif //HTTP_SERVER_09_HTTP_BASE64_H
