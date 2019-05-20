#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../include/http_parser.h"
#include "../include/http_error.h"
#include "../include/http_status.h"
#include "../include/http_server.h"
#include "../include/http_fileIO.h"
#include "../include/http_utils.h"


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
    free_str(response->content_encoding);

    if (response->content) {
        free(response->content);
        response->content = NULL;
    }

    free(response);
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
    // Extract Headerline from whole message
    size_t end_headerline;
    for (end_headerline = 0; end_headerline < strRequest->len; end_headerline++) {
        if (strRequest->str[end_headerline] == '\r') {
            break;
        }
    }

    // No valid headerline (not ended by "\r\n")
    if (end_headerline + 1 >= strRequest->len || strRequest->str[end_headerline + 1] != '\n') {
        return NULL;
    }

    http_request *request = new_httpRequest();

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
                // Wrong headerline
                free_str(token);
                free_str(headerline);
                free_httpRequest(request);
                return NULL;
        }
        tokenIndex++;
    }

    free_str(headerline);

    // Check if second linebreak occures
    if (end_headerline + 3 < strRequest->len && strRequest->str[end_headerline + 2] == '\r' &&
        strRequest->str[end_headerline + 3] == '\n') {
        return request;
    }


    // Extract all other headers
    for (size_t i = end_headerline; i < strRequest->len; i++) {
        char current = strRequest->str[i];

        //Jump over any linebreak or whitespace
        if (current == '\r' || current == '\n' || current == ' ') continue;

        //Get header name
        size_t end_headerName;
        for (end_headerName = i; end_headerName < strRequest->len; end_headerName++) {
            current = strRequest->str[end_headerName];
            if (current == ':') {
                break; // Headername found
            } else if (current == '\r' || current == '\n') {
                free_httpRequest(request);
                return NULL;  // No Headername found in this line --> request is bad!
            }
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
            if (current == '\r') {
                break;
            }
        }

        if (current != '\r' || (k + 1 < strRequest->len && strRequest->str[k + 1] != '\n')) {
            free_str(header_name);
            free_httpRequest(request);
            return NULL; // No true linebreak --> BAD Request
        }

        string *header_content = sub_str(strRequest, j, k - j);
        i = k;

        if (header_content == NULL || header_content->len == 0) {
            free_str(header_name);
            free_str(header_content);
            free_httpRequest(request);
            return NULL; // Header has a name, but no content --> BAD Request!!!
        }

        //Fill request fields with content
        string *header_name_cap = toUpper_str(header_name);

        //Find fitting header or ignore
        if (chars_equal_str(header_name_cap, "HOST") && request->host == NULL) {
            request->host = header_content;
        } else if (chars_equal_str(header_name_cap, "USER-AGENT") && request->user_agent == NULL) {
            request->user_agent = header_content;
        } else {
            // No header to store content in, so free it
            free_str(header_content);
        }

        free_str(header_name);
        free_str(header_name_cap);

        // Check if second linebreak occures after header --> headers are over
        if (k + 3 < strRequest->len && strRequest->str[k + 2] == '\r' && strRequest->str[k + 3] == '\n') {
            return request;
        }
    }

    free_httpRequest(request);
    return NULL;
}


http_response *generateStandardResponse(int statusCode) {
    http_response *response = new_httpResponse();

    response->status = getStatusString(statusCode);
    response->http_version = cpy_str(HTTP_VERSION);
    response->server = cpy_str(SERVER_NAME);

    return response;
}


http_response *generateStatusResponse(int statusCode) {
    char *codeBuffer = calloc(5, sizeof(char));
    intToString(statusCode, codeBuffer, 10);

    // Build path from status code
    string *path = cpy_str(STATUS_SITE_PATH);
    string *path2 = cat_str(path, codeBuffer);
    string *fullPath = cat_str(path2, ".html");

    free(codeBuffer);
    free_str(path);
    free_str(path2);

    //Load status page to buffer and see if its found
    void *payload = loadFileToBuffer(fullPath);

    if (payload != NULL) {
        http_response *response = generateStandardResponse(statusCode);
        response->content = payload;
        response->content_length = getFilesize(fullPath);
        response->content_type = getMimeType(fullPath);
        response->content_encoding = getMimeEncoding(fullPath);

        free_str(fullPath);
        return response;
    } else {
        fprintf(stderr, "Status Pages could not be loaded.\nDo they exist on this system?\n");
        free_str(fullPath);
        return generateStandardResponse(statusCode);
    }
}


http_response *generateDebugResponse(http_request *request) {
    http_response *response = generateStandardResponse(HTTP_STATUS_OK);

    string *htmlSite = cpy_str("<html>\n<body>\n<h1>Willkommen im externen Bereich!</h1>\n<pre>\n");

    if (request->method) {
        string *htmlMethod1 = cpy_str("HTTP-Methode: ");
        string *htmlMethod2 = str_cat_str(htmlMethod1, request->method);
        string *htmlMethodFull = cat_str(htmlMethod2, "\n");

        string *newSite = str_cat_str(htmlSite, htmlMethodFull);
        free_str(htmlSite);
        htmlSite = newSite;

        free_str(htmlMethod1);
        free_str(htmlMethod2);
        free_str(htmlMethodFull);
    }

    if (request->http_version) {
        string *htmlVersion1 = cpy_str("HTTP-Version: ");
        string *htmlVersion2 = str_cat_str(htmlVersion1, request->http_version);
        string *htmlVersionFull = cat_str(htmlVersion2, "\n");

        string *newSite = str_cat_str(htmlSite, htmlVersionFull);
        free_str(htmlSite);
        htmlSite = newSite;

        free_str(htmlVersion1);
        free_str(htmlVersion2);
        free_str(htmlVersionFull);
    }

    if (request->resource) {
        string *htmlResource1 = cpy_str("HTTP-Resource: ");
        string *htmlResource2 = str_cat_str(htmlResource1, request->resource);
        string *htmlResourceFull = cat_str(htmlResource2, "\n");

        string *newSite = str_cat_str(htmlSite, htmlResourceFull);
        free_str(htmlSite);
        htmlSite = newSite;

        free_str(htmlResource1);
        free_str(htmlResource2);
        free_str(htmlResourceFull);
    }

    if (request->user_agent) {
        string *htmlAgent1 = cpy_str("HTTP-User-Agent: ");
        string *htmlAgent2 = str_cat_str(htmlAgent1, request->user_agent);
        string *htmlAgentFull = cat_str(htmlAgent2, "\n");

        string *newSite = str_cat_str(htmlSite, htmlAgentFull);
        free_str(htmlSite);
        htmlSite = newSite;

        free_str(htmlAgent1);
        free_str(htmlAgent2);
        free_str(htmlAgentFull);
    }

    if (request->host) {
        string *htmlHost1 = cpy_str("HTTP-Host: ");
        string *htmlHost2 = str_cat_str(htmlHost1, request->host);
        string *htmlHostFull = cat_str(htmlHost2, "\n");

        string *newSite = str_cat_str(htmlSite, htmlHostFull);
        free_str(htmlSite);
        htmlSite = newSite;

        free_str(htmlHost1);
        free_str(htmlHost2);
        free_str(htmlHostFull);
    }


    string *htmlSiteFull = cat_str(htmlSite, "</pre>\n</body>\n</html>");
    free_str(htmlSite);

    response->content = toCString_str(htmlSiteFull);
    response->content_length = htmlSiteFull->len;
    response->content_type = cpy_str("text/html");
    response->content_encoding = cpy_str("us-ascii");

    free_str(htmlSiteFull);

    return response;
}


http_response *generateResponse(http_request *request) {

    // Missing required information or something is pretty bad about the request
    if (request == NULL || request->method == NULL || request->resource == NULL || request->http_version == NULL) {
        return generateStatusResponse(HTTP_STATUS_BAD_REQUEST);
    }

    // Wrong/unsupported method
    if (!chars_equal_str(request->method, "GET")) {
        return generateStatusResponse(HTTP_STATUS_NOT_IMPLEMENTED);
    }

    // Wrong/unsupported http version
    if ((!chars_equal_str(request->http_version, "HTTP/1.0")) &&
        (!chars_equal_str(request->http_version, "HTTP/1.1"))) {
        return generateStatusResponse(HTTP_STATUS_SERVICE_VERSION_NOT_SUPPORTED);
    }

    // Check which host (document root) to use in order to implement VIRTUAL HOSTING
    string *documentRoot = NULL;

    if (request->host != NULL && request->host->len != 0) {
        int portBegin = find_chars(request->host, ":");
        string *host;

        // Filter port out
        if (portBegin != -1) {
            host = sub_str(request->host, 0, portBegin);
        } else {
            host = clone_str(request->host);
        }

        // VIRTUAL HOSTING: Look what host and corresponding document root to serve
        if (chars_equal_str(host, "extern")) {
            documentRoot = cpy_str(EXTERN_DOCUMENT_ROOT);
        } else if (chars_equal_str(host, "intern")) {
            free_str((host));
            return generateStatusResponse(HTTP_STATUS_UNAUTHORIZED);
        } else {
            documentRoot = cpy_str(DEFAULT_DOCUMENT_ROOT);
        }

        free_str((host));
    } else {
        documentRoot = cpy_str(DEFAULT_DOCUMENT_ROOT);
    }


    //Create absolute path (document-root + relative path)
    string *absolutePath;

    if (chars_equal_str(request->resource, "/")) {
        absolutePath = cat_str(documentRoot, "index.html");
    } else {
        string *relative = sub_str(request->resource, 1,
                                   request->resource->len - 1); // Copy everything but the the leading /
        absolutePath = str_cat_str(documentRoot, relative);
        free_str(relative);
    }

    string *decodedURL = decodeURL(absolutePath);
    free_str(absolutePath);

    // URL encoding is invalid --> bad request
    if (decodedURL == NULL) {
        free_str(documentRoot);
        return generateStatusResponse(HTTP_STATUS_BAD_REQUEST);
    }

    string *realPath = toRealPath(decodedURL);

    // If file doesn't exist, decide if it lays in document root to prevent information leak
    if (realPath == NULL) {
        char *test = toCString_str(decodedURL);
        char *old = calloc(1, PATH_MAX);

        free_str(decodedURL);

        realpath(test, old);

        if (strncmp(documentRoot->str, old, documentRoot->len) == 0) {
            free(test);
            free(old);
            free_str(documentRoot);
            return generateStatusResponse(HTTP_STATUS_NOT_FOUND);
        } else {
            free(test);
            free(old);
            free_str(documentRoot);
            return generateStatusResponse(HTTP_STATUS_FORBIDDEN);
        }
    }

    free_str(decodedURL);

    // Check if path access is forbidden (out of the document root)
    if (!isInDocumentRoot(realPath, documentRoot)) {
        free_str(documentRoot);
        free_str(realPath);
        return generateStatusResponse(HTTP_STATUS_FORBIDDEN);
    }

    free_str(documentRoot);

    void *payload = loadFileToBuffer(realPath);

    if (payload != NULL) {
        http_response *response = generateStandardResponse(HTTP_STATUS_OK);

        response->content = payload;
        response->content_length = getFilesize(realPath);
        response->content_type = getMimeType(realPath);
        response->content_encoding = getMimeEncoding(realPath);

        free_str(realPath);
        return response;
    } else {
        free_str(realPath);
        return generateStatusResponse(HTTP_STATUS_FORBIDDEN);
    }
}


string *httpResponseToString(http_response *response) {
    // Headerline
    string *version = cpy_str(HTTP_VERSION);
    string *header1 = cat_str(version, " ");
    string *header2 = str_cat_str(header1, response->status);
    string *fullHeader = cat_str(header2, "\r\n");

    free_str(version);
    free_str(header1);
    free_str(header2);

    // Servername
    string *server1 = cat_str(fullHeader, "Server: ");
    string *server2 = cat_str(server1, SERVER_NAME);
    string *fullServer = cat_str(server2, "\r\n");

    free_str(fullHeader);
    free_str(server1);
    free_str(server2);

    if (response->content != NULL) {
        // Content-Type
        string *type1 = cat_str(fullServer, "Content-Type: ");
        string *type2 = str_cat_str(type1, response->content_type);
        string *fullType = cat_str(type2, "\r\n");

        free_str(fullServer);
        free_str(type1);
        free_str(type2);

        // Content-Encoding
        string *encoding1 = cat_str(fullType, "Content-Encoding: ");
        string *encoding2 = str_cat_str(encoding1, response->content_encoding);
        string *fullEncoding = cat_str(encoding2, "\r\n");

        free_str(fullType);
        free_str(encoding1);
        free_str(encoding2);

        // Content-Length
        char *lengthBuffer = calloc(256, sizeof(char));
        intToString(response->content_length, lengthBuffer, 10);

        string *length1 = cat_str(fullEncoding, "Content-Length: ");
        string *length2 = cat_str(length1, lengthBuffer);
        string *fullLength = cat_str(length2, "\r\n");

        free(lengthBuffer);
        free_str(fullEncoding);
        free_str(length1);
        free_str(length2);

        //Content
        string *content1 = cat_str(fullLength, "\r\n");
        string *fullContent = cat_str_len(content1, response->content, response->content_length);

        free_str(fullLength);
        free_str(content1);

        return fullContent;
    } else {
        string *endedResponse = cat_str(fullServer, "\r\n");
        free_str(fullServer);
        return endedResponse;
    }
}
