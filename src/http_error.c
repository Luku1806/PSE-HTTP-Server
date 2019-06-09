#include "../include/http_error.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


void error(char *msg) {
    fprintf(stderr, "%s", msg);
    if (errno) {
        fprintf(stderr, ", errno: %s", strerror(errno));
    }
    fprintf(stderr, "\n");
    exit(1);
}