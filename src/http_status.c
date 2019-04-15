//
// Created by Leon Franke on 14.04.19.
//
#include "../include/http_status.h"

#include "../include/http_string.h"



string *getStatusString(int statusCode){

    switch(statusCode){
        case HTTP_STATUS_OK:
            return cpy_str("200 OK");
            break;
        case HTTP_STATUS_CREATED:
            return cpy_str("201 CREATED");
            break;
        case HTTP_STATUS_ACCEPTED:
            return cpy_str("202 ACCEPTED");
            break;
        case HTTP_STATUS_NO_CONTENT:
            return cpy_str("204 NO CONTENT:");
            break;
        case HTTP_STATUS_MOVED_PERMANENTLY:
            return cpy_str("301 MOVED PERMANENTLY");
            break;
        case HTTP_STATUS_MOVED_TEMPORARELY:
            return cpy_str("302 MOVED TEMPORARELY");
            break;
        case HTTP_STATUS_NOT_MODIFIED:
            return cpy_str("304 NOT MODIFIED");
            break;
        case HTTP_STATUS_BAD_REQUEST:
            return cpy_str("400 BAD_REQUEST");
            break;
        case HTTP_STATUS_UNAUTHORIZED:
            return cpy_str("401 UNAUTHORIZED");
            break;
        case HTTP_STATUS_FORBIDDEN:
            return cpy_str("403 FORBIDDEN");
            break;
        case HTTP_STATUS_NOT_FOUND:
            return cpy_str("404 NOT FOUND");
            break;
        case HTTP_STATUS_INTERNAL_SERVER_ERROR:
            return cpy_str("500 INTERNAL SERVER ERROR");
            break;
        case HTTP_STATUS_NOT_IMPLEMENTED:
            return cpy_str("501 NOT IMPLEMENTED");
            break;
        case HTTP_STATUS_BAD_GATEWAY:
            return cpy_str("502 BAD GATEWAY");
            break;
        case HTTP_STATUS_SERVICE_UNAVAILABLE:
            return cpy_str("503 SERVICE UNAVAILABLE");
            break;
    }


};




