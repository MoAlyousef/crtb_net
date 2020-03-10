#include "crtb_net.h"
#include "rtb_net.hpp"

using namespace rtb;

rtb_server *rtb_server_init(const char *host, unsigned int port,
                            const char *docroot, unsigned int threads) {
  return new (std::nothrow)
      net::HttpServer(net::HttpServer::init(host, port, docroot, threads));
}

void rtb_server_route(rtb_server *server, const char *method, const char *path,
                      rtb_request_handler handler, void *args) {
  static_cast<net::HttpServer *>(server)->route(
      method, path, [&](const net::Request &req2, net::Response &res2) {
        handler(&req2, &res2, args);
      });
}

void rtb_server_enable_logging(rtb_server *server, int boolean) {
  static_cast<net::HttpServer *>(server)->enable_logging(boolean);
}

void rtb_server_run(rtb_server *server) {
  auto retval = static_cast<net::HttpServer *>(server)->run();
  if (retval.is_err())
    server = NULL;
}

void rtb_server_free(rtb_server *server) {
  delete static_cast<net::HttpServer *>(server);
}

const char *rtb_request_headers_to_string(const rtb_request *req) {
  return static_cast<const net::Request *>(req)->get_headers().c_str();
}

const char *rtb_request_method(const rtb_request *req) {
  return static_cast<const net::Request *>(req)->method.c_str();
}

const char *rtb_request_uri(const rtb_request *req) {
  return static_cast<const net::Request *>(req)->uri.c_str();
}

void rtb_request_get_headers(const rtb_request *req, rtb_header *headers, int sz) {
  auto hdrs = static_cast<const net::Request *>(req)->headers;
  auto size = hdrs.size();
  if (size > sz)
    size = sz;
  for (auto i = 0; i < size; i++) {
    headers[i].name = hdrs[i].name.c_str();
    headers[i].value = hdrs[i].value.c_str();
  }
}

void rtb_request_get_regex_placeholders(const rtb_request *req,
                                    rtb_request_regex_placeholder *arr,
                                    int sz) {
  auto ph = static_cast<const net::Request *>(req)->uri_placeholders;
  auto size = ph.size();
  if (size > sz)
    size = sz;
  for (auto i = 0; i < size; i++) {
    arr[i].key = i;
    arr[i].value = ph.at(i).c_str();
  }
}

void rtb_request_get_placeholders(const rtb_request *req,
                              rtb_request_placeholder *arr, int sz) {
  auto ph = static_cast<const net::Request *>(req)->uri_placeholders;
  auto size = ph.size();
  if (size > sz)
    size = sz;
  int i = 0;
  for (auto kv : ph) {
    if (i == size) break;
    arr[i].key = std::get<std::string>(kv.first).c_str();
    arr[i].value = kv.second.c_str();
    i++;
  }
}

const char *rtb_request_body(const rtb_request *req) {
  return static_cast<const net::Request *>(req)->body().c_str();
}

const char *rtb_request_body_decoded(const rtb_request *req) {
  return static_cast<const net::Request *>(req)->body_decoded().c_str();
}

int rtb_response_status(rtb_response *res) {
  return (int)static_cast<net::Response *>(res)->status();
}

void rtb_response_set_status(rtb_response *res, int status) {
  static_cast<net::Response *>(res)->set_status(status);
}

void rtb_response_add_header(rtb_response *res, const char *name,
                             const char *value) {
  static_cast<net::Response *>(res)->add_header(name, value);
}

void rtb_response_connection_alive(rtb_response *res, int boolean) {
  static_cast<net::Response *>(res)->connection_alive(boolean);
}

const char *rtb_response_content(rtb_response *res) {
  return static_cast<net::Response *>(res)->content().c_str();
}

void rtb_response_set_content(rtb_response *res, const char *content) {
  static_cast<net::Response *>(res)->set_content(content);
}

int rtb_response_content_length(rtb_response *res) {
  return static_cast<net::Response *>(res)->content_length();
}

void rtb_response_set_content_length(rtb_response *res) {
  static_cast<net::Response *>(res)->set_content_length();
}

const char *rtb_response_content_type(rtb_response *res) {
  return static_cast<net::Response *>(res)->content_type().c_str();
}

void rtb_response_set_content_type(rtb_response *res,
                                   const char *content_type) {
  static_cast<net::Response *>(res)->set_content_type(content_type);
}

const char *rtb_response_protocol(rtb_response *res) {
  return static_cast<net::Response *>(res)->protocol().c_str();
}

const char *rtb_response_location(rtb_response *res) {
  return static_cast<net::Response *>(res)->location().c_str();
}

const char *rtb_response_headers_to_string(rtb_response *res) {
  return static_cast<net::Response *>(res)->get_headers().c_str();
}
