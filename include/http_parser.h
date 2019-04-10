#ifndef HTTP_SERVER_09_HTTP_PARSER_H
#define HTTP_SERVER_09_HTTP_PARSER_H


#include "http_string.h"

typedef struct http_request {
    string *method;
    string *resource;
    string *http_version;
    string *host;
    string *user_agent;
    size_t content_length;
    void *content;
} http_request;

typedef struct http_response {
    string *http_version;
    string *status;
    string *server;
    string *content_type;
    size_t content_length;
    void *content;
} http_response;


/**
 * Creates (allocates) a new httpRequest and returns a pointer to it.
 * @return The pointer to the allocated httpRequest.
 */
http_request *new_httpRequest();

/**
 * Frees the memory allocated for the httpRequest pointer.
 * @param request The request pointer to free.
 */
void free_httpRequest(http_request *request);


/**
 * Creates (allocates) a new httpResponse and returns a pointer to it.
 * @return The pointer to the allocated httpResponse.
 */
http_response *new_httpResponse();


/**
 * Frees the memory allocated for the httpResponse pointer.
 * @param response The response pointer to free.
 */
void free_httpResponse(http_response *response);


/**
 * Prints a request formatted to the console.
 * @param request The request to print.
 */
void printRequest(http_request *request);


/**
 * Parses the raw string that came over the network.
 * Creates and returns a new http_request struct pointer, containing all information needed to respond.
 *
 * @param strRequest The raw string(message) received from the client.
 * @return A parseRequest pointer containing all information send in the message.
 */
http_request *parseRequest(string *strRequest);


/**
 * Returns a pointer to a response with servername, http-version, and status already set.
 *
 * @param statusCode The status code for the request.
 * @return The generated and pre-initialized http-response.
 */
http_response *generateStandardResponse(int statusCode);


/**
 * Creates a response for the given request.
 *
 * @param request The request to respond to.
 * @return The response to the given request.
 */
http_response *generateResponse(http_request *request);


/**
 * Returns the string containing the content/mime type of the resource.
 *
 * @param path The path to the resource.
 * @return A string containing the MIME-Type of the resource.
 */
string *getMimeType(string *path);


/**
 * Generates a string representing the gven response to be sent to the client.
 *
 * @param response The response to be converted to the string.
 * @return The pointer to the string to be sent.
 */
string *httpResponseToString(http_response *response);


#endif //HTTP_SERVER_09_HTTP_PARSER_H
