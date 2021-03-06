#include <stddef.h>

#ifndef HTTP_SERVER_09_HTTP_STRING_H
#define HTTP_SERVER_09_HTTP_STRING_H

/**
 * @file http_string.h
 * @brief This file contains all string functions that are currently needed and may need later.
 */


/**
 * @struct string
 * @brief Used to store char buffer together with their length, to get have a string like struct that is not null terminated.
 */
typedef struct string {
    size_t len;   /**< @brief The length in bytes of the string. This is without a null terminator, because we dont use one!!!*/
    char *str;    /**< @brief The actual bytes/characters of the string.*/
} string;


/**
 * @brief Allocates a new string pointer and returns it.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param len The length of the string.
 * @return The pointer to the nwe allocated string.
 */
string *new_string(size_t len);


/**
 * @brief Frees the allocated memory of a string.
 *
 * @param str The string pointer to free.
 */
void free_str(string *str);


/**
 * @brief Prints a string to the console.
 *
 * @param str The string to print.
 */
void print_string(string *str);


/**
 * @brief Copies a C-string into a new string struct and returns this.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param src The C-string to copy into the struct.
 * @return The string struct pointer with the C-string in it
 */
string *cpy_str(const char *src);


/**
 * @brief Clones everything stored in src, to a new string pointer.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param src The string to clone.
 * @return The new string pointer, containing all information of src.
 */
string *clone_str(string *src);


/**
 * @brief Returns a null terminated char pointer (c-string) version of a string.
 *
 * Allocates memory for the returned char pointer. This has to be freed by calling free!
 *
 * @param str The string to return as c-string.
 * @return The string as char pointer.
 */
char *toCString_str(string *str);


/**
 * @brief Combines a string and a c-string to a new string
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param dest String 1 to combine
 * @param src char-pointer to combine
 * @return Either Returns a new String or NULL depending on whether the condition is met or not.
 */
string *cat_str(string *dest, const char *src);


/**
 * @brief Combines a string and a generic pointer with a given length
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param dest String 1 to combine
 * @param src pointer to combine
 * @param len lenth of the pointer to concat
 * @return Either Returns a new String or NULL depending on whether the condition is met or not.
 */
string *cat_str_len(string *dest, void *src, size_t len);


/**
 * @brief Combines two strings to a new string
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param dest String 1 to combine
 * @param src String 2 to combine
 * @return Either Returns a new String or NULL depending on whether the condition is met or not.
 */
string *str_cat_str(string *dest, string *src);


/**
 * @brief Determines if 2 strings are equal.
 *
 * @param str1 String 1 to compare.
 * @param str2 String 2 to compare.
 * @return Returns 0 if the strings are different, 1 if they are equal.
 */
char equals_str(string *str1, string *str2);


/**
 * @brief Determines if a strings is equal to a char pointer (c-string).
 *
 * @param str String to compare to the chars.
 * @param chars Chars to compare to the string.
 * @return Returns 0 if the strings are different, 1 if they are equal.
 */
char chars_equal_str(string *str, char *chars);


/**
 * @brief Return a substring with the length len of str starting at start.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param str String to get substring of.
 * @param start Index to start the substring.
 * @param len The length of the substring.
 * @return The substring of str. If start + length is greater than the string, NULL is returned.
 */
string *sub_str(string *str, size_t start, int len);


/**
 * @brief Finds the first occurence of str2 in str1
 *
 * @param str1 The string to look if it contains str2.
 * @param str2 The string to find in str1
 * @return The index of the first occurence of str2 in str1. Returns -1 if not found.
 */
int find_str(string *str1, string *str2);


/**
 * @brief Finds the first occurence of chars in str
 *
 * @param str The string to look if it contains chars.
 * @param str2 The chars(C-String) to find in str
 * @return The index of the first occurence of chars in str. Returns -1 if not found.
 */
int find_chars(string *str1, char *chars);


/**
 * @brief Returns if a string ends with a set of chars(c-string).
 *
 * @param str The string to see if it ends with the chars.
 * @param ending The chars to see if the string ends with them.
 * @return 1 if the string ends with the chars. 0 if not.
 */
char endsWith_str(string *str, char *ending);


/**
 * @brief Returns if a string starts with a set of chars(c-string).
 *
 * @param str The string to see if it start with the chars.
 * @param starting The chars to see if the string start with them.
 * @return 1 if the string starts with the chars. 0 if not.
 */
char startsWith_str(string *str, char *starting);


/**
 * @brief Returns a string, converted to capital letters only.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param str The string to convert to capital letters.
 * @return A pointer to the string converted to capital letters only.
 */
string *toUpper_str(string *str);


/**
 * @brief Removes all trailing charcters.
 *
 * For example if toRemove is a, "12345aaa" becomes "12345"
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param string The string to remove the trailing characters from.
 * @param toRemove The trailing characters.
 * @return The trimmed string.
 */
string *removeTrailingChars(string *string, char toRemove);


#endif //HTTP_SERVER_09_HTTP_STRING_H
