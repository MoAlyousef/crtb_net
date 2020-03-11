#include "crtb_net.h"
#include "rtb_net.hpp"
#include <cstring>
#include <new>

using namespace rtb;

unsigned int rtb_hardware_concurrency(void) {
  return std::thread::hardware_concurrency();
}

// server code

rtb_server *rtb_server_init(const char *host, unsigned int port,
                            const char *docroot, unsigned int threads) {
  return new (std::nothrow)
      net::HttpServer(net::HttpServer::init(host, port, docroot, threads));
}

void rtb_server_free(rtb_server *server) {
  delete static_cast<net::HttpServer *>(server);
}

void rtb_server_route(rtb_server *server, const char *method, const char *path,
                      rtb_request_handler handler, void *args) {
  static_cast<net::HttpServer *>(server)->route(
      method, path, [=](const net::Request &req2, net::Response &res2) {
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

// client code

rtb_client *rtb_client_init() {
  return new (std::nothrow) net::HttpClient(net::HttpClient::init());
}

void rtb_client_free(rtb_client *client) {
  delete static_cast<net::HttpClient *>(client);
}

void rtb_client_set_host(rtb_client *client, const char *addr,
                         unsigned int port) {
  static_cast<net::HttpClient *>(client)->set_host(addr, port);
}

void rtb_client_set_proxy(rtb_client *client, const char *addr,
                          unsigned int port) {
  static_cast<net::HttpClient *>(client)->set_proxy_host(addr, port);
}

void rtb_client_set_auth(rtb_client *client, const char *user, const char *pass,
                         int is_proxy) {
  static_cast<net::HttpClient *>(client)->set_auth(user, pass, is_proxy);
}

void rtb_client_follow_redirects(rtb_client *client, int boolean) {
  static_cast<net::HttpClient *>(client)->follow_redirects(boolean);
}

void rtb_client_expires_at(rtb_client *client, int seconds) {
  static_cast<net::HttpClient *>(client)->expires_at(seconds);
}

rtb_response *rtb_client_get(rtb_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpClient *>(client)->Get(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_client_head(rtb_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpClient *>(client)->Head(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_client_post(rtb_client *client, const char *path,
                              enum rtb_post_type type, const char *msg) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpClient *>(client)
            ->Post(path, static_cast<net::PostContentType>(type), msg)
            .unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_client_put(rtb_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpClient *>(client)->Put(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_client_delete(rtb_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpClient *>(client)->Delete(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

// request code

rtb_request *rtb_request_init() { return new (std::nothrow) net::Request(); }

void rtb_request_free(rtb_request *request) {
  delete static_cast<net::Request *>(request);
}

char *rtb_request_headers_to_string(const rtb_request *req) {
  auto temp = static_cast<const net::Request *>(req)->get_headers();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

char *rtb_request_method(const rtb_request *req) {
  auto temp = static_cast<const net::Request *>(req)->method;
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

char *rtb_request_uri(const rtb_request *req) {
  auto temp = static_cast<const net::Request *>(req)->uri;
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

void rtb_request_get_headers(const rtb_request *req, rtb_header *headers,
                             int sz) {
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
    if (i == size)
      break;
    arr[i].key = std::get<std::string>(kv.first).c_str();
    arr[i].value = kv.second.c_str();
    i++;
  }
}

char *rtb_request_body(const rtb_request *req) {
  auto temp = static_cast<const net::Request *>(req)->body();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

char *rtb_request_body_decoded(const rtb_request *req) {
  auto temp = static_cast<const net::Request *>(req)->body_decoded();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

// response code

rtb_response *rtb_response_init() { return new (std::nothrow) net::Response(); }

void rtb_response_free(rtb_response *response) {
  delete static_cast<net::Response *>(response);
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

char *rtb_response_content(rtb_response *res) {
  auto temp = static_cast<net::Response *>(res)->content();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
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

char *rtb_response_content_type(rtb_response *res) {
  auto temp = static_cast<net::Response *>(res)->content_type();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

void rtb_response_set_content_type(rtb_response *res,
                                   const char *content_type) {
  static_cast<net::Response *>(res)->set_content_type(content_type);
}

char *rtb_response_protocol(rtb_response *res) {
    auto temp = static_cast<net::Response *>(res)->protocol();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

char *rtb_response_location(rtb_response *res) {
  auto temp = static_cast<net::Response *>(res)->location();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

char *rtb_response_headers_to_string(rtb_response *res) {
  auto temp = static_cast<net::Response *>(res)->get_headers();
  char *ret = (char*)malloc(temp.size() + 1);
  strncpy(ret, temp.c_str(), temp.size() + 1);
  return ret;
}

#if 0

#endif
