#include "../include/http_fileIO.h"

#include <stdlib.h>


string *toRealPath(string *path) {
    char *pathAsChars = toCString_str(path);
    char *realPath = realpath(pathAsChars, NULL);

    if(realPath == NULL) return new_string(0);

    string *realPathString = cpy_str(realPath);
    return realPathString;
}