/**
 * @file http_base64.h
 *
 * @brief This file provides functions to encode and decode c-strings/char pointers from and to base64 encoded text.
 */

#ifndef HTTP_SERVER_09_HTTP_BASE64_H
#define HTTP_SERVER_09_HTTP_BASE64_H

#include <stddef.h>
#include "http_string.h"


/**
 * Builds up the internal decoding table.
 * Is called by base64_decode.
 * Anywhere in the program base64_cleanup has to be called to free the memory allocated for the table.
 */
void build_decoding_table();


/**
 * Frees the memory allocated for the decoding table.
 * Has to be called anywhere after base64_decode to prevent memory leaks.
 */
void base64_cleanup();


/**
 * Encodes a normal c-string into base64 encoded text.
 *
 * @param data The c-string to encode to base64.
 * @param input_length The length if the c-string to encode.
 * @param output_length The lenght of the returned encoded char* (c-string).
 * @return The char* (c-string) containing the encoded text. It has the length *output_length.
 */
char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);


/**
 * Decodes a base64 encoded c-string into normal decoded text.
 *
 * @param data The c-string to decode from base64.
 * @param input_length The length if the c-string to decode.
 * @param output_length The lenght of the returned decoded char* (c-string).
 * @return The char* (c-string) containing the decoded text. It has the length *output_length.
 */
unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);


/**
 * Encodes a normal string into base64 encoded text.
 *
 * @param toEncode The string to encode to base64.
 * @return The string containing the encoded text.
 */
string *base64_encode_string(string *toEncode);


/**
 * Decodes a base64 encoded c-string into normal decoded text.
 * Returns NULL if string toDecode is not base64.
 *
 * @param toDecode The string to decode from base64.
 * @return The string containing the decoded text. NULL if toDecode is not base64.
*/
string *base64_decode_string(string *toDecode);


#endif //HTTP_SERVER_09_HTTP_BASE64_H