#ifndef HTTP_SERVER_09_HTTP_FILEIO_H
#define HTTP_SERVER_09_HTTP_FILEIO_H

#include "http_string.h"

#include <stddef.h>

#define DOCUMENT_ROOT "/var/www/"


/**
 * Converts a path with /../ etc to an absolute path.
 *
 * @param path The path to convert.
 * @return The converted, absolute path.
 */
string *toRealPath(string *path);


/**
 * Checks if a path lays in the document root.
 *
 * @param filepath The path to check if it lays in the document root.
 * @return 0 if the path is not in the document root, 1 if it is in document root.
 */
char isInDocumentRoot(string *filepath);


/**
 * Returns the size of a file.
 *
 * @param filepath The path, the file lays in.
 * @return The size of the file at the given path. 0 if file is empty or not available.
 */
size_t getFilesize(string *filepath);


/**
 * Loads a file at a given path into a buffer and returns it.
 *
 * @param filepath The path of the file to be loaded.
 * @return The file in a buffer. NULL if file was not found.
 */
void *loadFileToBuffer(string *filepath);


#endif //HTTP_SERVER_09_HTTP_FILEIO_H
