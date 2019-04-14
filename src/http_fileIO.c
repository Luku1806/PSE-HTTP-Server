#include "../include/http_fileIO.h"

#include <stdlib.h>
#include <stdio.h>


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


void *loadFileToBuffer(string *filepath) {
    FILE *file = fopen(filepath->str, "rb");

    if (!file) {
        fprintf(stderr,"Could not find file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    void *fcontent = malloc(fsize);
    fread(fcontent, 1, fsize, file);

    fclose(file);

    return fcontent;
}

char isInDocumentRoot(string *filepath){

    if (startsWith_str(filepath, DOCUMENT_ROOT)){

        return 1;

    } else{

        return 0;
    }

}