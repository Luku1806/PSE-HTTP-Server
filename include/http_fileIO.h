#ifndef HTTP_SERVER_09_HTTP_FILEIO_H
#define HTTP_SERVER_09_HTTP_FILEIO_H

#include "http_string.h"

#include <stddef.h>

/**
 * @file http_fileIO.h
 * @brief All file functions required for reading, writing, etc. are accommodated here.
 */


/**
 * @brief Converts a path with /../ etc to an absolute path.
 *
 * If file is not found, an empty string is returned (Length = 0).
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param path The path to convert.
 * @return The converted, absolute path. Returns an empty string if path is not found.
 */
string *toRealPath(string *path);


/**
 * @brief Checks if a path lays in the document root.
 *
 * @param filepath The path to check if it lays in the document root.
 * @param root The document path root to check.
 * @return 0 if the path is not in the document root, 1 if it is in document root.
 */
char isInDocumentRoot(string *filepath, string *root);


/**
 * @brief Returns the size of a file.
 *
 * @param filepath The path, the file lays in.
 * @return The size of the file at the given path. 0 if file is empty or not available.
 */
size_t getFilesize(string *filepath);


/**
 * @brief Loads a file at a given path into a buffer and returns it.
 *
 * Allocates memory for the returned void * buffer. This has to be freed!
 *
 * @param filepath The path of the file to be loaded.
 * @return The file in a buffer. NULL if file was not found.
 */
void *loadFileToBuffer(string *filepath);


/**
 * @brief Returns the string containing the content/mime type of the resource.
 *
 * Returns an empty string with lenth 0, if information could not be found.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param path The path to the resource.
 * @return A string containing the MIME-Type of the resource. Empty string if information was not found.
 */
string *getMimeType(string *path);


/**
 * @brief Returns the string containing the content/mime encoding of the resource.
 *
 * Returns an empty string with lenth 0, if information could not be found.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param path The path to the resource.
 * @return A string containing the MIME-Encoding of the resource. Empty string if information was not found.
 */
string *getMimeEncoding(string *path);


#endif //HTTP_SERVER_09_HTTP_FILEIO_H
