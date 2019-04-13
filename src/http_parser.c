#include <stdlib.h>
#include <stdio.h>
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


void printRequest(http_request *request) {
    if (request == NULL) return;

    printf("Reqest:\n");

    if (request->method != NULL) {
        printf("Method: ");
        print_string(request->method);
        printf("\n");
    }
    if (request->resource != NULL) {
        printf("Resource: ");
        print_string(request->resource);
        printf("\n");
    }
    if (request->http_version != NULL) {
        printf("Http-version: ");
        print_string(request->http_version);
        printf("\n");
    }
    if (request->host != NULL) {
        printf("Host: ");
        print_string(request->host);
        printf("\n");
    }
    if (request->user_agent != NULL) {
        printf("User-Agent: ");
        print_string(request->user_agent);
        printf("\n");
    }

    fflush(stdout);
}


http_request *parseRequest(string *strRequest) {
    http_request *request = new_httpRequest();

    // Extract Headerline from whole message
    size_t end_headerline;
    for (end_headerline = 0; end_headerline < strRequest->len; end_headerline++) {
        char current = strRequest->str[end_headerline];
        if (current == '\r' || current == '\n') break;
    }

    //TODO Decide if headerline is set or valid

    string *headerline = sub_str(strRequest, 0, end_headerline);

    int tokenIndex = 0;
    for (size_t i = 0; i < headerline->len; i++) {
        //Jump over any leading whitespace
        char current = headerline->str[i];
        if (current == ' ') continue;

        // Search for end of current token
        size_t j;
        for (j = i; j < headerline->len; j++) {
            current = headerline->str[j];
            if (current == ' ') break;
        }

        string *token = sub_str(headerline, i, j - i);
        i = j;

        switch (tokenIndex) {
            case 0:
                request->method = token;
                break;
            case 1:
                request->resource = token;
                break;
            case 2:
                request->http_version = token;
                break;
            default:
                free_str(token);
                break;
        }
        tokenIndex++;
    }

    free_str(headerline);

    // Extract all other headers
    for (size_t i = end_headerline; i < strRequest->len; i++) {
        char current = strRequest->str[i];

        //Jump over any linebreak or whitespace
        if (current == '\r' || current == '\n' || current == ' ') continue;

        //Get header name
        size_t end_headerName;
        for (end_headerName = i; end_headerName < strRequest->len; end_headerName++) {
            current = strRequest->str[end_headerName];
            if (current == ':') break;
        }
        string *header_name = sub_str(strRequest, i, end_headerName - i);

        size_t j, k;

        //Jump over any whitespace after the ':'
        for (j = end_headerName + 1; j < strRequest->len; j++) {
            current = strRequest->str[j];
            if (current != ' ') break;
        }

        // Find index where linebreak comes --> header content is over
        for (k = j; k < strRequest->len; k++) {
            current = strRequest->str[k];
            if (current == '\r' || current == '\n') break;
        }
        string *header_content = sub_str(strRequest, j, k - j);
        i = k;

        //Fill request fields with content
        string *header_name_cap = toUpper_str(header_name);

        //Find fitting header or ignore
        if (chars_equal_str(header_name_cap, "HOST")) {
            request->host = header_content;
        } else if (chars_equal_str(header_name_cap, "USER-AGENT")) {
            request->user_agent = header_content;
        } else {
            // No header to store content in, so free it
            free_str(header_content);
        }

        free_str(header_name);
        free_str(header_name_cap);
    }

    return request;
}