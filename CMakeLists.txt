cmake_minimum_required(VERSION 3.13)
project(HTTP_Server_09 C)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})

add_executable(HTTP_Server_09 src/http_server.c include/http_server.h src/http_string.c include/http_string.h src/http_error.c include/http_error.h src/http_parser.c include/http_parser.h src/http_utils.c include/http_utils.h src/http_status.c include/http_status.h src/http_fileIO.c include/http_fileIO.h include/http_security.h src/http_security.c src/http_base64.c include/http_base64.h)

target_link_libraries(HTTP_Server_09 magic)
target_link_libraries(HTTP_Server_09 crypto)