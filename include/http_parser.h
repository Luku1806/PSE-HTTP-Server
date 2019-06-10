#ifndef HTTP_SERVER_09_HTTP_PARSER_H
#define HTTP_SERVER_09_HTTP_PARSER_H


#include "http_string.h"

/**
 * @file http_parser.h
 *
 * @brief This file provides all functions for processing the incoming requests, from reading everything into a struct, to generating an answer.
 *
 * In general this should be used like:
 *
 * 1. Process raw message by calling parseRequest to save all informations in a request_struct
 * 2. Put the struct into generateResponse to build a response struct
 * 3. Put the response_struct into httpResponseToString to get the response as string
 * 4. This string can then be converted to bytes, and be sent over the network socket.
 */

/**
 * @struct http_request
 *
 * @brief Used to bundle all information about a request.
 *
 * Contains all header fields, used by the program and can be expanded to the needs.
 * None of this fields has to be set, it depends on the information, the client sent.
 */
typedef struct http_request {
    string *method;            /**< @brief The HTTP Method. For example "GET".*/
    string *resource;          /**< @brief The requested ressource.*/
    string *http_version;      /**< @brief The HTTP version, the client says it speaks.*/
    string *host;              /**< @brief The host, the client tries to reach.*/
    string *user_agent;        /**< @brief The textual description, the client gives us about itself.*/
    string *authentication;    /**< @brief The authentication information the client gives us.*/
    size_t content_length;     /**< @brief The length of the content/payload, the client sent us.*/
    void *content;             /**< @brief The content/payload that the client sent.*/
} http_request;


/**
 * @struct http_response
 *
 * @brief Used to bundle all information about a response.
 *
 * Contains all header fields, used by the program and can be expanded to the needs.
 */
typedef struct http_response {
    string *http_version;        /**< @brief The HTTP version, that the response has. In general it will always be HTTP/1.1.*/
    string *status;              /**< @brief The HTTP status code, wit a textual description. For example "200 OK".*/
    string *server;              /**< @brief A textual description of the server itself. This can be anything.*/
    string *content_type;        /**< @brief The MIME-Type of the content that is sent.*/
    string *content_encoding;    /**< @brief The encoding format of the content.*/
    size_t content_length;       /**< @brief The length of the sent content in bytes.*/
    char auth_required;          /**< @brief This is a flag to set if the client has to authorize. If it is not set to 0, the response string will contain the information for the client that it has to authenticate.*/
    void *content;               /**< @brief The actual content that should be sent. Can contain anything casted to a void pointer.*/
} http_response;


/**
 * @brief Creates (allocates) a new httpRequest and returns a pointer to it.
 *
 * The returned allocated memory has to be freed, when its no longer needed by calling free_httpRequest()!
 *
 * @return The pointer to the allocated httpRequest.
 */
http_request *new_httpRequest();

/**
 * @brief Frees the memory allocated for the httpRequest pointer.
 * @param request The request pointer to free.
 */
void free_httpRequest(http_request *request);


/**
 * @brief Creates (allocates) a new httpResponse and returns a pointer to it.
 *
 * The returned allocated memory has to be freed, when its no longer needed by calling free_httpResponse()!
 *
 * @return The pointer to the allocated httpResponse.
 */
http_response *new_httpResponse();


/**
 * @brief Frees the memory allocated for the httpResponse pointer.
 * @param response The response pointer to free.
 */
void free_httpResponse(http_response *response);


/**
 * @brief Prints a request formatted to the console.
 * @param request The request to print.
 */
void printRequest(http_request *request);


/**
 * @brief Parses the raw string that came over the network.
 *
 * Creates and returns a new http_request struct pointer, containing all information needed to respond.
 * Returns NULL if something is bad about the message.
 *
 * The returned request has to be freed, when its no longer needed by calling free_httpRequest()!
 *
 * @param strRequest The raw string(message) received from the client.
 * @return A parseRequest pointer containing all information send in the message. NULL if message is bad.
 */
http_request *parseRequest(string *strRequest);


/**
 * @brief Returns a pointer to a response with servername, http-version, and status already set.
 *
 * The returned response has to be freed, when its no longer needed by calling free_httpResponse()!
 *
 * @param statusCode The status code for the request.
 * @return The generated and pre-initialized http-response.
 */
http_response *generateStandardResponse(int statusCode);


/**
 * @brief Returns a pointer to a response with servername, http-version, status, and the corresponding html-site already set.
 *
 * The returned response has to be freed, when its no longer needed by calling free_httpResponse()!
 *
 * @param statusCode The status code for the request.
 * @return The generated and pre-initialized http-response.
 */
http_response *generateStatusResponse(int statusCode);


/**
 * @brief Creates a response with an HTML site containing the information contained in the request.
 *
 * This is used for debug an can be called by requesting /debug as path.
 *
 * The returned response has to be freed, when its no longer needed by calling free_httpResponse()!
 *
 * @param request The request to show.
 * @return The debug response to the given request.
 */
http_response *generateDebugResponse(http_request *request);


/**
 * @brief Creates a response for the given request.
 *
 * The returned response has to be freed, when its no longer needed by calling free_httpResponse()!
 *
 * @param request The request to respond to.
 * @return The response to the given request.
 */
http_response *generateResponse(http_request *request);


/**
 * @brief Generates a string representing the gven response to be sent to the client.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param response The response to be converted to the string.
 * @return The pointer to the string to be sent.
 */
string *httpResponseToString(http_response *response);


/**
 * @brief Returns the string containing the content/mime type of the resource.
 *
 * Allocates memory for the returned string. This has to be freed by calling free_str!
 *
 * @param path The path to the resource.
 * @return A string containing the MIME-Type of the resource.
 */
string *getMimeType(string *path);

#endif //HTTP_SERVER_09_HTTP_PARSER_H
