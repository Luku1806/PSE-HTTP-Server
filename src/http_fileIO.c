#include "../include/http_fileIO.h"

#include <stdlib.h>
#include <stdio.h>
#include <magic.h>
#include <string.h>


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

size_t getFilesize(string *filepath) {
    FILE *file = fopen(filepath->str, "rb");

    if (!file) {
        fprintf(stderr,"Could not find file\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fclose(file);
    return fsize;
}


/**
 * Function to get general MIME information for a given file.
 * Should only be used to simplify getMimeType and getMimeEncoding
 *
 * @param path The Path to look at.
 * @param flag The information to look for.
 * @return A c-string containing the information found. NULL if nothing was found or an error occured.
 */
char *getMimeInformation(string *path, int flag) {
    magic_t magic = magic_open(flag);

    if (magic == NULL) {
        error("unable to initialize magic library\n");
    }

    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "cannot load magic database - %s\n", magic_error(magic));
        magic_close(magic);
        return NULL;
    }

    char *pathAsChars = toCString_str(path);
    char *mimeAsChars = (char *) magic_file(magic, pathAsChars);

    // Copy string, because magic frees returned values
    char *information;
    strcpy(information, mimeAsChars);

    free(pathAsChars);
    magic_close(magic);

    return information;
}


string *getMimeType(string *path) {
    char *type = getMimeInformation(path, MAGIC_MIME_TYPE);

    if (type == NULL) {
        fprintf(stderr, "Could not get MIME-Type information for file\n");
        return new_string(0);
    }

    return cpy_str(type);
}


string *getMimeEncoding(string *path) {
    char *encoding = getMimeInformation(path, MAGIC_MIME_ENCODING);

    if (encoding == NULL) {
        fprintf(stderr, "Could not get MIME-Encoding information for file\n");
        return new_string(0);
    }

    return cpy_str(encoding);
}