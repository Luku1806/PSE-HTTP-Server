#include <stdlib.h>
#include "http_string.h"

#ifndef HTTP_SERVER_09_HTTP_UTILS_H
#define HTTP_SERVER_09_HTTP_UTILS_H


/**
 * @file http_utils.h
 *
 * @brief This file provides all functions that are needed for utility.
 */



/**
 * @brief Converts an integer value to a null-terminated string using the specified base and stores the result in the char pointer given by buf parameter.
 *
 * Returns null if buffer would overflow
 *
 * Because buf is the same as the return value, either buf or the returned pointer have to be freed, when the string is no longer needed, by calling free.
 *
 * @param value The integer value to convert to string
 * @param buf The buffer to store the resulting string in.
 * @param bufsize The size of the buffer
 * @return A pointer to the resulting null-terminated string, same as parameter str.
 */
char *intToString(int value, char *buf, size_t bufsize);


/**
 * @brief Returns if an ascii character is a valid hexadecimal digit, so if is 0-9, a-f or A-F.
 *
 * @param c The character to check.
 * @return 1 if its a hex-digit, 0 if not.
 */
char isAscii(char c);


/**
 * @brief Converts a string of hexadecimal digits to a char.
 *
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
 * @brief Removes URL-encoding from a string and returns the decoded string.
 *
 * Return NULL if encoding is invalid.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param string *url The coded string.
 * @return The new decoded string. NULL if encoding is invalid.
 */

string *decodeURL(string *url);


#endif //HTTP_SERVER_09_HTTP_UTILS_H
