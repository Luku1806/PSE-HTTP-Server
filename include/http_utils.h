#include <stdlib.h>
#include "http_string.h"

#ifndef HTTP_SERVER_09_HTTP_UTILS_H
#define HTTP_SERVER_09_HTTP_UTILS_H

/*
 *
 *
 * For everything we need for utility.
 *
 *
 */


/**
 * Decodes the link to normal characters.
 *
 * @param string *url The coded string.
 * @return The new decoded string.
 */

string *decodeURL(string *url);

#endif //HTTP_SERVER_09_HTTP_UTILS_H
