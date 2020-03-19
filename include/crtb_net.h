
/*
MIT License

Copyright (c) 2020 Mohammed Alyousef

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#ifdef RTB_ENABLE_SSL
#include <openssl/ssl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
  Definitions
*/

typedef void rtb_request;

typedef void rtb_response;

typedef void rtb_future_response;

typedef void rtb_server;

typedef void rtb_client;

typedef void rtb_ssl_server;

typedef void rtb_ssl_client;

typedef void asio_io_context;

typedef struct {
  char *name;
  char *value;
} rtb_header;

typedef struct {
  int key;
  char *value;
} rtb_request_regex_placeholder;

typedef struct {
  char *key;
  char *value;
} rtb_request_placeholder;

/* required for binary content */
typedef struct {
  unsigned int size;
  char *value;
} rtb_content;

enum rtb_post_type { Json, Plain, WWWform };

/*
  General
*/

unsigned int rtb_hardware_concurrency(void);

typedef void (*rtb_request_handler)(const rtb_request *req, rtb_response *resp,
                                    void *args);

typedef void (*rtb_client_continuation)(const rtb_response *resp, void *args);

/*
  Server code
*/

rtb_server *rtb_server_init(const char *host, unsigned int port,
                            const char *docroot, unsigned int threads);

void rtb_server_free(rtb_server *server);

void rtb_server_route(rtb_server *, const char *method, const char *path,
                      rtb_request_handler handler, void *args);

void rtb_server_enable_logging(rtb_server *, int boolean);

void rtb_server_enable_dir_listing(rtb_server *, int boolean);

int rtb_server_run(rtb_server *server);

/*
  Client code
*/

rtb_client *rtb_client_init(void);

void rtb_client_free(rtb_client *client);

void rtb_client_set_host(rtb_client *client, const char *addr,
                         unsigned int port);

void rtb_client_set_proxy(rtb_client *client, const char *addr,
                          unsigned int port);

void rtb_client_set_auth(rtb_client *client, const char *user, const char *pass,
                         int is_proxy);

void rtb_client_follow_redirects(rtb_client *client, int boolean);

void rtb_client_expires_at(rtb_client *client, int seconds);

rtb_response *rtb_client_get(rtb_client *client, const char *path);

rtb_response *rtb_client_head(rtb_client *client, const char *path);

rtb_response *rtb_client_post(rtb_client *client, const char *path,
                              enum rtb_post_type type, const char *msg);

rtb_response *rtb_client_put(rtb_client *client, const char *path);

rtb_response *rtb_client_delete(rtb_client *client, const char *path);

void rtb_client_get_async(rtb_client *client, const char *path,
                          rtb_client_continuation cb, void *args);

void rtb_client_head_async(rtb_client *client, const char *path,
                           rtb_client_continuation cb, void *args);

void rtb_client_post_async(rtb_client *client, const char *path,
                           enum rtb_post_type type, const char *msg,
                           rtb_client_continuation cb, void *args);

void rtb_client_put_async(rtb_client *client, const char *path,
                          rtb_client_continuation cb, void *args);

void rtb_client_delete_async(rtb_client *client, const char *path,
                             rtb_client_continuation cb, void *args);

rtb_future_response *rtb_client_get_future(rtb_client *client,
                                           const char *path);

rtb_future_response *rtb_client_head_future(rtb_client *client,
                                            const char *path);

rtb_future_response *rtb_client_post_future(rtb_client *client,
                                            const char *path,
                                            enum rtb_post_type type,
                                            const char *msg);

rtb_future_response *rtb_client_put_future(rtb_client *client,
                                           const char *path);

rtb_future_response *rtb_client_delete_future(rtb_client *client,
                                              const char *path);

/*
  Request code
*/

rtb_request *rtb_request_init(void);

void rtb_request_free(rtb_request *request);

char *rtb_request_headers_to_string(const rtb_request *req);

char *rtb_request_method(const rtb_request *req);

char *rtb_request_uri(const rtb_request *req);

void rtb_request_get_headers(const rtb_request *req, rtb_header *headers,
                             unsigned int sz);

void rtb_request_headers_free(rtb_header *headers, unsigned int sz);

void rtb_request_get_regex_placeholders(const rtb_request *req,
                                        rtb_request_regex_placeholder *arr,
                                        unsigned int sz);

void rtb_request_regex_placeholders_free(
    rtb_request_regex_placeholder *placeholders, unsigned int sz);

void rtb_request_get_placeholders(const rtb_request *req,
                                  rtb_request_placeholder *arr,
                                  unsigned int sz);

void rtb_request_placeholders_free(rtb_request_placeholder *placeholders,
                                   unsigned int sz);

char *rtb_request_body(const rtb_request *req);

char *rtb_request_body_decoded(const rtb_request *req);

/*
  Response code
*/

rtb_response *rtb_response_init(void);

rtb_response *rtb_response_await(rtb_future_response *future_resp);

void rtb_response_free(rtb_response *response);

void rtb_future_response_free(rtb_future_response *future_resp);

int rtb_response_status(const rtb_response *res);

void rtb_response_set_status(rtb_response *res, int status);

void rtb_response_add_header(rtb_response *res, const char *name,
                             const char *value);

void rtb_response_connection_alive(rtb_response *res, int boolean);

const rtb_content rtb_response_content(const rtb_response *res);

void rtb_response_set_content(rtb_response *res, const char *content);

int rtb_response_content_length(const rtb_response *res);

void rtb_response_set_content_length(rtb_response *res, unsigned int length);

char *rtb_response_content_type(const rtb_response *res);

void rtb_response_set_content_type(rtb_response *res, const char *content_type);

char *rtb_response_protocol(const rtb_response *res);

char *rtb_response_location(const rtb_response *res);

char *rtb_response_headers_to_string(const rtb_response *res);

#ifdef RTB_ENABLE_SSL

/*
  ssl server
*/

rtb_ssl_server *rtb_ssl_server_init(SSL_CTX *ctx, const char *host,
                                    unsigned int port, const char *docroot,
                                    unsigned int threads);

void rtb_ssl_server_free(rtb_ssl_server *server);

void rtb_ssl_server_route(rtb_ssl_server *, const char *method,
                          const char *path, rtb_request_handler handler,
                          void *args);

void rtb_ssl_server_enable_logging(rtb_ssl_server *, int boolean);

void rtb_ssl_server_enable_dir_listing(rtb_ssl_server *, int boolean);

int rtb_ssl_server_run(rtb_ssl_server *server);

/*
  ssl client
*/

rtb_ssl_client *rtb_ssl_client_init(SSL_CTX *ctx);

void rtb_ssl_client_free(rtb_ssl_client *client);

void rtb_ssl_client_set_host(rtb_ssl_client *client, const char *addr,
                             unsigned int port);

void rtb_ssl_client_set_proxy(rtb_ssl_client *client, const char *addr,
                              unsigned int port);

void rtb_ssl_client_set_auth(rtb_ssl_client *client, const char *user,
                             const char *pass, int is_proxy);

void rtb_ssl_client_follow_redirects(rtb_ssl_client *client, int boolean);

void rtb_ssl_client_expires_at(rtb_ssl_client *client, int seconds);

rtb_response *rtb_ssl_client_get(rtb_ssl_client *client, const char *path);

rtb_response *rtb_ssl_client_head(rtb_ssl_client *client, const char *path);

rtb_response *rtb_ssl_client_post(rtb_ssl_client *client, const char *path,
                                  enum rtb_post_type type, const char *msg);

rtb_response *rtb_ssl_client_put(rtb_ssl_client *client, const char *path);

rtb_response *rtb_ssl_client_delete(rtb_ssl_client *client, const char *path);

void rtb_ssl_client_get_async(rtb_ssl_client *client, const char *path,
                              rtb_client_continuation cb, void *args);

void rtb_ssl_client_head_async(rtb_ssl_client *client, const char *path,
                               rtb_client_continuation cb, void *args);

void rtb_ssl_client_post_async(rtb_ssl_client *client, const char *path,
                               enum rtb_post_type type, const char *msg,
                               rtb_client_continuation cb, void *args);

void rtb_ssl_client_put_async(rtb_ssl_client *client, const char *path,
                              rtb_client_continuation cb, void *args);

void rtb_ssl_client_delete_async(rtb_ssl_client *client, const char *path,
                                 rtb_client_continuation cb, void *args);

rtb_future_response *rtb_ssl_client_get_future(rtb_ssl_client *client,
                                               const char *path);

rtb_future_response *rtb_ssl_client_head_future(rtb_ssl_client *client,
                                                const char *path);

rtb_future_response *rtb_ssl_client_post_future(rtb_ssl_client *client,
                                                const char *path,
                                                enum rtb_post_type type,
                                                const char *msg);

rtb_future_response *rtb_ssl_client_put_future(rtb_ssl_client *client,
                                               const char *path);

rtb_future_response *rtb_ssl_client_delete_future(rtb_ssl_client *client,
                                                  const char *path);

#endif

#ifdef __cplusplus
}
#endif
