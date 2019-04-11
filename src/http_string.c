#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/http_string.h"
#include "../include/http_error.h"


string *new_string(size_t len) {
    string *str = calloc(sizeof(string), 1);
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
    str = NULL;
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


string *cat_str(string *dest, const char *src) {
    size_t size1 = dest->len;
    size_t size2 = strlen(src);
    size_t newSize = size1 + size2;

    if (newSize != NULL){

        string *newString = new_string(newSize);
        memcpy(newString->str, dest->str, size1);
        memcpy(newString->str + size1, src, size2);

        return newString;

    } else{

        error("cat_str: Strings are empty");
    }

}


string * sub_str(string *str, size_t start, size_t len) {
    if (start + len > str->len) return NULL;

    string *substring = new_string(len);
    for (int i = 0; i < len; i++) {
        substring->str[i] = str->str[start + i];
    }

    return substring;
}