#include <stdlib.h>
#include "http_string.h"

#ifndef HTTP_SERVER_09_HTTP_UTILS_H
#define HTTP_SERVER_09_HTTP_UTILS_H


/**
 *
 * @brief Here we put all the functions that don't fit into the other files. (Extra functions)
 */


/**
 * Returns if an ascii character is a valid hexadecimal digit, so if is 0-9, a-f or A-F.
 *
 * @param c The character to check.
 * @return 1 if its a hex-digit, 0 if not.
 */
char isAscii(char c);


/**
 * Converts a string of hexadecimal digits to a char.
 * Used to convert the two hexadecimal digits behind the % in url encoding to the corresponding character in the ascii table.
 * For example: %20: hex:20 --> dez:32 --> ascii:" " (space).
 *
 * Returns -1 if the string contains digits, that do not belong to the hexadezimal alphabet.
 *
 * @param hex The string with hexadecimal digits.
 * @return The corresponding character. -1 if its not a valid hex string.
 */
char hexStringToChar(string *hex);


/**
 * Removes URL-encoding from a string and returns the decoded string.
 * Return NULL if encoding is invalid.
 *
 * @param string *url The coded string.
 * @return The new decoded string. NULL if encoding is invalid.
 */

string *decodeURL(string *url);


#endif //HTTP_SERVER_09_HTTP_UTILS_H
