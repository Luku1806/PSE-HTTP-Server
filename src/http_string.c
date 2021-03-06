#include "../include/http_string.h"
#include "../include/http_error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


string *new_string(size_t len) {
    string *str = calloc(1, sizeof(string));
    if (str == NULL) {
        exit(2);
    }
    str->str = calloc(len, sizeof(char));
    if (str->str == NULL) {
        exit(3);
    }
    str->len = len;
    return str;
}


void free_str(string *str) {
    if (str == NULL) return;
    free(str->str);
    free(str);
}


void print_string(string *str) {
    for (int i = 0; i < str->len; i++) {
        putchar(str->str[i]);
    }
}


string *cpy_str(const char *src) {
    size_t newLength = strlen(src);
    string *dest = new_string(newLength);
    memcpy(dest->str, src, newLength);
    return dest;
}


string *clone_str(string *src) {
    string *dest = new_string(src->len);
    memcpy(dest->str, src->str, src->len);
    return dest;
}


string *cat_str(string *dest, const char *src) {

    if ((dest != NULL) && (src != NULL)) {

        size_t size1 = dest->len;
        size_t size2 = strlen(src);
        size_t newSize = size1 + size2;

        string *newString = new_string(newSize);
        memcpy(newString->str, dest->str, size1);
        memcpy(newString->str + size1, src, size2);

        return newString;

    } else {

        return NULL;
    }

}


string *cat_str_len(string *dest, void *src, size_t len) {
    if ((dest != NULL) && (src != NULL)) {
        size_t newSize = dest->len + len;
        string *newString = new_string(newSize);

        memcpy(newString->str, dest->str, dest->len);
        memcpy(newString->str + dest->len, src, len);

        return newString;
    }

    return NULL;
}


string *str_cat_str(string *dest, string *src) {
    if ((dest != NULL) && (src != NULL)) {
        size_t newSize = dest->len + src->len;
        string *newString = new_string(newSize);

        memcpy(newString->str, dest->str, dest->len);
        memcpy(newString->str + dest->len, src->str, src->len);

        return newString;
    }

    return NULL;
}


string *sub_str(string *str, size_t start, int len) {
    if (start + len > str->len && len < 1) return NULL;

    string *substring = new_string(len);
    for (int i = 0; i < len; i++) {
        substring->str[i] = str->str[start + i];
    }

    return substring;
}


char equals_str(string *str1, string *str2) {
    if (str1->len != str2->len) return 0;
    for (int i = 0; i < str1->len; ++i) {
        if (str1->str[i] != str2->str[i]) return 0;
    }
    return 1;
}


char chars_equal_str(string *str, char *chars) {
    if (strlen(chars) != str->len) return 0;
    for (int i = 0; i < str->len; i++) {
        if (str->str[i] != chars[i]) return 0;
    }
    return 1;
}


int find_str(string *str1, string *str2) {
    int len1 = str1->len;
    int len2 = str2->len;

    for (int i = 0; i <= len1 - len2; i++) {
        int j;

        // For current index i, check for pattern match
        for (j = 0; j < len2; j++) {
            if (str1->str[i + j] != str2->str[j]) break;
        }

        if (j == len2) return i;
    }

    return -1;
}


int find_chars(string *str1, char *chars) {
    size_t len1 = str1->len;
    size_t len2 = strlen(chars);

    for (int i = 0; i <= len1 - len2; i++) {
        int j;

        // For current index i, check for pattern match
        for (j = 0; j < len2; j++) {
            if (str1->str[i + j] != chars[j]) break;
        }

        if (j == len2) return i;
    }

    return -1;
}

char *toCString_str(string *str) {
    char *chars = calloc(str->len + 1, 1);
    if (chars == NULL) error("Error allocating memory for char pointer");
    memcpy(chars, str->str, str->len);
    chars[str->len] = '\0';
    return chars;
}

string *toUpper_str(string *str) {
    string *strCapital = new_string(str->len);
    strCapital->len = str->len;

    for (int i = 0; i < str->len; i++) {
        char current = str->str[i];

        if ((current > 96) && (current < 123)) {
            strCapital->str[i] = current - 32;
        } else {
            strCapital->str[i] = current;
        }
    }

    return strCapital;
}

char endsWith_str(string *str, char *ending) {
    size_t ending_length = strlen(ending);
    int strFirstIndex = str->len - ending_length;

    if (str->len < ending_length) return 0;

    for (int i = 0; i < ending_length; i++) {
        if (str->str[strFirstIndex + i] != ending[i]) return 0;
    }

    return 1;
}

char startsWith_str(string *str, char *starting) {
    size_t starting_length = strlen(starting);

    if (str->len < starting_length) return 0;

    for (int i = 0; i < starting_length; i++) {
        if (str->str[i] != starting[i]) return 0;
    }

    return 1;

}

string *removeTrailingChars(string *string, char toRemove) {
    if (string == NULL) return NULL;

    size_t lastNoRemove = 0;
    for (size_t i = 0; i < string->len; i++) {
        char current = string->str[i];

        if (current == toRemove) {
            while (i < string->len && string->str[i] == toRemove) i++; // Jump over any charcter to remove
            if (i < string->len) lastNoRemove = i; // If loop ended, but it was not the last character, set index
        } else {
            lastNoRemove = i;
        }
    }

    return sub_str(string, 0, lastNoRemove + 1);
}
