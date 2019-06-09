#include "../include/http_status.h"


string *getStatusString(int statusCode) {

    switch (statusCode) {
        case HTTP_STATUS_OK:
            return cpy_str("200 OK");
        case HTTP_STATUS_CREATED:
            return cpy_str("201 CREATED");
        case HTTP_STATUS_ACCEPTED:
            return cpy_str("202 ACCEPTED");
        case HTTP_STATUS_NO_CONTENT:
            return cpy_str("204 NO CONTENT:");
        case HTTP_STATUS_MOVED_PERMANENTLY:
            return cpy_str("301 MOVED PERMANENTLY");
        case HTTP_STATUS_MOVED_TEMPORARELY:
            return cpy_str("302 MOVED TEMPORARELY");
        case HTTP_STATUS_NOT_MODIFIED:
            return cpy_str("304 NOT MODIFIED");
        case HTTP_STATUS_BAD_REQUEST:
            return cpy_str("400 BAD_REQUEST");
        case HTTP_STATUS_UNAUTHORIZED:
            return cpy_str("401 UNAUTHORIZED");
        case HTTP_STATUS_FORBIDDEN:
            return cpy_str("403 FORBIDDEN");
        case HTTP_STATUS_NOT_FOUND:
            return cpy_str("404 NOT FOUND");
        case HTTP_STATUS_URI_TOO_LONG:
            return cpy_str("414 URI TOO LONG");
        case HTTP_STATUS_INTERNAL_SERVER_ERROR:
            return cpy_str("500 INTERNAL SERVER ERROR");
        case HTTP_STATUS_NOT_IMPLEMENTED:
            return cpy_str("501 NOT IMPLEMENTED");
        case HTTP_STATUS_BAD_GATEWAY:
            return cpy_str("502 BAD GATEWAY");
        case HTTP_STATUS_SERVICE_UNAVAILABLE:
            return cpy_str("503 SERVICE UNAVAILABLE");
        case HTTP_STATUS_SERVICE_VERSION_NOT_SUPPORTED:
            return cpy_str("505 HTTP VERSION NOT SUPPORTED");
        default:
            return NULL;
    }

};




