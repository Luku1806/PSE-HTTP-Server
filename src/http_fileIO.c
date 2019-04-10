#include "../include/http_fileIO.h"

#include <stdlib.h>


string *toRealPath(string *path) {
    char *pathAsChars = toCString_str(path);
    char *realPath = realpath(pathAsChars, NULL);
    string *realPathString;

    if(realPath == NULL){
        realPathString = new_string(0);
    }else{
        realPathString = cpy_str(realPath);
    }

    free(pathAsChars);
    free(realPath);

    return realPathString;
}