#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void rtb_request;

typedef void rtb_response;

typedef void rtb_server;

typedef struct {
  const char *name;
  const char *value;
} rtb_header;

typedef struct {
  int key;
  const char *value;
} rtb_request_regex_placeholder;

typedef struct {
  const char *key;
  const char *value;
} rtb_request_placeholder;

typedef void (*rtb_request_handler)(const rtb_request *req, rtb_response *resp,
                                    void *args);

rtb_server *rtb_server_init(const char *host, unsigned int port,
                            const char *docroot);

void rtb_server_route(rtb_server *, const char *method, const char *path,
                      rtb_request_handler handler, void *args);

void rtb_server_enable_logging(rtb_server *, int boolean);

void rtb_server_run(rtb_server *server);

void rtb_server_free(rtb_server *server);

const char *rtb_request_headers_to_string(const rtb_request *req);

const char *rtb_request_method(const rtb_request *req);

const char *rtb_request_uri(const rtb_request *req);

void rtb_request_get_headers(const rtb_request *req, rtb_header *headers, int sz);

void rtb_request_get_regex_placeholders(const rtb_request *req,
                                    rtb_request_regex_placeholder *arr, int sz);

void rtb_request_get_placeholders(const rtb_request *req,
                              rtb_request_placeholder *arr, int sz);

const char *rtb_request_body(const rtb_request *req);

const char *rtb_request_body_decoded(const rtb_request *req);

int rtb_response_status(rtb_response *res);

void rtb_response_set_status(rtb_response *res, int);

void rtb_response_add_header(rtb_response *res, const char *name,
                             const char *value);

void rtb_response_connection_alive(rtb_response *res, int boolean);

const char *rtb_response_content(rtb_response *res);

void rtb_response_set_content(rtb_response *res, const char *content);

int rtb_response_content_length(rtb_response *res);

void rtb_response_set_content_length(rtb_response *res);

const char *rtb_response_content_type(rtb_response *res);

void rtb_response_set_content_type(rtb_response *res, const char *content_type);

const char *rtb_response_protocol(rtb_response *res);

const char *rtb_response_location(rtb_response *res);

const char *rtb_response_headers_to_string(rtb_response *res);

#ifdef __cplusplus
}
#endif
