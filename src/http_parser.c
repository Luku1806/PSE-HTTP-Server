#include <stdlib.h>
#include "../include/http_parser.h"
#include "../include/http_error.h"


http_request *new_httpRequest() {
    http_request *request = calloc(1, sizeof(http_request));
    if (request == NULL) error("Error allocating memory for HTTP request");
    return request;
}


void free_httpRequest(http_request *request) {
    if (request == NULL) return;

    free_str(request->method);
    free_str(request->resource);
    free_str(request->http_version);
    free_str(request->host);
    free_str(request->user_agent);

    if (request->content) {
        free(request->content);
    }

    free(request);
    request = NULL;
}


http_response *new_httpResponse() {
    http_response *response = calloc(1, sizeof(http_response));
    if (response == NULL) error("Error allocating memory for HTTP response");
    return response;
}


void free_httpResponse(http_response *response) {
    if (response == NULL) return;

    free_str(response->http_version);
    free_str(response->status);
    free_str(response->server);
    free_str(response->content_type);

    if (response->content) {
        free(response->content);
        response->content = NULL;
    }

    free(response);
    response = NULL;
}