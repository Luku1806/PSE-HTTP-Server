#include <stdlib.h>
#include "http_string.h"

#ifndef HTTP_SERVER_09_HTTP_UTILS_H
#define HTTP_SERVER_09_HTTP_UTILS_H


/**
 * Converts a string of hexadecimal digits to a char.
 * Used to convert the two hexadecimal digits behind the % in url encoding to the corresponding character in the ascii table.
 * For example: %20: hex:20 --> dez:32 --> ascii:" " (space).

 * @param hex The string with hexadecimal digits.
 * @return The corresponding character.
 */
char hexStringToChar(string *hex);



/**
 * Removes URL-encoding from a string and returns the decoded string.
 *
 * @param string *url The coded string.
 * @return The new decoded string.
 */

string *decodeURL(string *url);


#endif //HTTP_SERVER_09_HTTP_UTILS_H
