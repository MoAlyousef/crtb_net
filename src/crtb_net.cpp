/*
MIT License

Copyright (c) 2019 Mohammed Alyousef

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

#include "crtb_net.h"
#include "rtb_net.hpp"
#include <cstring>
#include <future>
#include <new>

using namespace rtb;

unsigned int rtb_hardware_concurrency(void) {
  return std::thread::hardware_concurrency();
}

// server code

rtb_server *rtb_server_init(const char *host, unsigned int port,
                            const char *docroot, unsigned int threads) {
  return new (std::nothrow) net::HttpServer(host, port, docroot, threads);
}

void rtb_server_free(rtb_server *server) {
  delete static_cast<net::HttpServer *>(server);
  server = NULL;
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

void rtb_server_enable_dir_listing(rtb_server *server, int boolean) {
  static_cast<net::HttpServer *>(server)->enable_dir_listing(boolean);
}

int rtb_server_run(rtb_server *server) {
  try {
    return static_cast<net::HttpServer *>(server)->run().unwrap();
  } catch (...) {
    return -1;
  }
}

// client code

rtb_client *rtb_client_init() { return new (std::nothrow) net::HttpClient(); }

void rtb_client_free(rtb_client *client) {
  delete static_cast<net::HttpClient *>(client);
  client = NULL;
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

void rtb_client_get_async(rtb_client *client, const char *path,
                          rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpClient *>(client)->async_get(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_client_head_async(rtb_client *client, const char *path,
                           rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpClient *>(client)->async_head(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_client_put_async(rtb_client *client, const char *path,
                          rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpClient *>(client)->async_put(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_client_post_async(rtb_client *client, const char *path,
                           enum rtb_post_type type, const char *msg,
                           rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpClient *>(client)->async_post(
        path, static_cast<net::PostContentType>(type), msg,
        [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_client_delete_async(rtb_client *client, const char *path,
                             rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpClient *>(client)->async_delete(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

rtb_future_response *rtb_client_get_future(rtb_client *client,
                                           const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpClient *>(client)->async_get(path,
                                                        asio::use_future));
}

rtb_future_response *rtb_client_head_future(rtb_client *client,
                                            const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpClient *>(client)->async_head(path,
                                                         asio::use_future));
}

rtb_future_response *rtb_client_post_future(rtb_client *client,
                                            const char *path,
                                            enum rtb_post_type type,
                                            const char *msg) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpClient *>(client)->async_post(
          path, static_cast<net::PostContentType>(type), msg,
          asio::use_future));
}

rtb_future_response *rtb_client_put_future(rtb_client *client,
                                           const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpClient *>(client)->async_put(path,
                                                        asio::use_future));
}

rtb_future_response *rtb_client_delete_future(rtb_client *client,
                                              const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpClient *>(client)->async_delete(path,
                                                           asio::use_future));
}

// request code

rtb_request *rtb_request_init() { return new (std::nothrow) net::Request(); }

void rtb_request_free(rtb_request *request) {
  delete static_cast<net::Request *>(request);
  request = NULL;
}

char *rtb_request_headers_to_string(const rtb_request *req) {
  try {
    auto temp = static_cast<const net::Request *>(req)->get_headers();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

char *rtb_request_method(const rtb_request *req) {
  try {
    auto temp = static_cast<const net::Request *>(req)->method;
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

char *rtb_request_uri(const rtb_request *req) {
  try {
    auto temp = static_cast<const net::Request *>(req)->uri;
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

void rtb_request_get_headers(const rtb_request *req, rtb_header *headers,
                             unsigned int sz) {
  try {
    auto hdrs = static_cast<const net::Request *>(req)->headers;
    auto size = hdrs.size();
    if (size > sz)
      size = sz;
    for (auto i = 0; i < size; i++) {
      headers[i].name = (char *)malloc(hdrs[i].name.size() + 1);
      strncpy(headers[i].name, hdrs[i].name.c_str(), hdrs[i].name.size() + 1);
      headers[i].value = (char *)malloc(hdrs[i].value.size() + 1);
      strncpy(headers[i].value, hdrs[i].value.c_str(),
              hdrs[i].value.size() + 1);
    }
  } catch (...) {
    return;
  }
}

void rtb_request_headers_free(rtb_header *headers, unsigned int sz) {
  for (auto i = 0; i < sz; ++i) {
    free(headers[i].name);
    free(headers[i].value);
  }
}

void rtb_request_get_regex_placeholders(const rtb_request *req,
                                        rtb_request_regex_placeholder *arr,
                                        unsigned int sz) {
  try {
    auto ph = static_cast<const net::Request *>(req)->uri_placeholders;
    auto size = ph.size();
    if (size > sz)
      size = sz;
    std::string val;
    for (auto i = 0; i < size; i++) {
      arr[i].key = i;
      val = ph.at(i);
      arr[i].value = (char *)malloc(val.size() + 1);
      strncpy(arr[i].value, val.c_str(), val.size() + 1);
    }
  } catch (...) {
    return;
  }
}

void rtb_request_regex_placeholders_free(
    rtb_request_regex_placeholder *placeholders, unsigned int sz) {
  for (auto i = 0; i < sz; ++i) {
    free(placeholders[i].value);
  }
}

void rtb_request_get_placeholders(const rtb_request *req,
                                  rtb_request_placeholder *arr,
                                  unsigned int sz) {
  try {
    auto ph = static_cast<const net::Request *>(req)->uri_placeholders;
    auto size = ph.size();
    if (size > sz)
      size = sz;
    int i = 0;
    std::string key, val;
    for (auto kv : ph) {
      if (i == size)
        break;
      key = std::get<std::string>(kv.first);
      val = kv.second;
      arr[i].key = (char *)malloc(key.size() + 1);
      arr[i].value = (char *)malloc(val.size() + 1);
      strncpy(arr[i].key, key.c_str(), key.size() + 1);
      strncpy(arr[i].value, val.c_str(), val.size() + 1);
      i++;
    }
  } catch (...) {
    return;
  }
}

void rtb_request_placeholders_free(rtb_request_placeholder *placeholders,
                                   unsigned int sz) {
  for (auto i = 0; i < sz; ++i) {
    free(placeholders[i].key);
    free(placeholders[i].value);
  }
}

char *rtb_request_body(const rtb_request *req) {
  try {
    auto temp = static_cast<const net::Request *>(req)->body();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

char *rtb_request_body_decoded(const rtb_request *req) {
  try {
    auto temp = static_cast<const net::Request *>(req)->body_decoded();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

// response code

rtb_response *rtb_response_init() { return new (std::nothrow) net::Response(); }

rtb_response *rtb_response_await(rtb_future_response *future_resp) {
  return new (std::nothrow) net::Response(
      static_cast<std::future<net::Response> *>(future_resp)->get());
}

void rtb_response_free(rtb_response *response) {
  delete static_cast<net::Response *>(response);
  response = NULL;
}

void rtb_future_response_free(rtb_future_response *future_resp) {
  delete static_cast<std::future<net::Response> *>(future_resp);
  future_resp = NULL;
}

int rtb_response_status(const rtb_response *res) {
  return (int)static_cast<const net::Response *>(res)->status();
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

const rtb_content rtb_response_content(const rtb_response *res) {
  rtb_content content = {0};
  try {
    std::string temp = "";
    unsigned int sz = 0;
    temp = static_cast<const net::Response *>(res)->content();
    sz = temp.size();
    content.value = (char *)malloc(sz + 1);
    content.size = sz;
    std::memcpy(content.value, &temp[0], sz);
    content.value[sz] = '\0';
  } catch (...) {
    //
  }
  return content;
}

void rtb_response_set_content(rtb_response *res, const char *content) {
  static_cast<net::Response *>(res)->set_content(content);
}

int rtb_response_content_length(const rtb_response *res) {
  return static_cast<const net::Response *>(res)->content_length();
}

void rtb_response_set_content_length(rtb_response *res, unsigned int length) {
  static_cast<net::Response *>(res)->set_content_length(length);
}

char *rtb_response_content_type(const rtb_response *res) {
  try {
    auto temp = static_cast<const net::Response *>(res)->content_type();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

void rtb_response_set_content_type(rtb_response *res,
                                   const char *content_type) {
  static_cast<net::Response *>(res)->set_content_type(content_type);
}

char *rtb_response_protocol(const rtb_response *res) {
  try {
    auto temp = static_cast<const net::Response *>(res)->protocol();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

char *rtb_response_location(const rtb_response *res) {
  try {
    auto temp = static_cast<const net::Response *>(res)->location();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

char *rtb_response_headers_to_string(const rtb_response *res) {
  try {
    auto temp = static_cast<const net::Response *>(res)->get_headers();
    char *ret = (char *)malloc(temp.size() + 1);
    strncpy(ret, temp.c_str(), temp.size() + 1);
    return ret;
  } catch (...) {
    return NULL;
  }
}

#ifdef RTB_ENABLE_SSL

rtb_ssl_server *rtb_ssl_server_init(SSL_CTX *ctx, const char *host,
                                    unsigned int port, const char *docroot,
                                    unsigned int threads) {
  asio::ssl::context temp(ctx);
  return new (std::nothrow)
      net::HttpsServer(temp, host, port, docroot, threads);
}

void rtb_ssl_server_free(rtb_ssl_server *server) {
  delete static_cast<net::HttpsServer *>(server);
  server = NULL;
}

void rtb_ssl_server_route(rtb_ssl_server *server, const char *method,
                          const char *path, rtb_request_handler handler,
                          void *args) {
  static_cast<net::HttpsServer *>(server)->route(
      method, path, [=](const net::Request &req2, net::Response &res2) {
        handler(&req2, &res2, args);
      });
}

void rtb_ssl_server_enable_logging(rtb_ssl_server *server, int boolean) {
  static_cast<net::HttpsServer *>(server)->enable_logging(boolean);
}

void rtb_ssl_server_enable_dir_listing(rtb_ssl_server *server, int boolean) {
  static_cast<net::HttpsServer *>(server)->enable_dir_listing(boolean);
}

int rtb_ssl_server_run(rtb_ssl_server *server) {
  try {
    return static_cast<net::HttpsServer *>(server)->run().unwrap();
  } catch (...) {
    return -1;
  }
}

rtb_ssl_client *rtb_ssl_client_init(SSL_CTX *ctx) {
  asio::ssl::context temp(ctx);
  return new (std::nothrow) net::HttpsClient(temp);
}

void rtb_ssl_client_free(rtb_ssl_client *client) {
  delete static_cast<net::HttpsClient *>(client);
  client = NULL;
}

void rtb_ssl_client_set_host(rtb_ssl_client *client, const char *addr,
                             unsigned int port) {
  static_cast<net::HttpsClient *>(client)->set_host(addr, port);
}

void rtb_ssl_client_set_proxy(rtb_ssl_client *client, const char *addr,
                              unsigned int port) {
  static_cast<net::HttpsClient *>(client)->set_proxy_host(addr, port);
}

void rtb_ssl_client_set_auth(rtb_ssl_client *client, const char *user,
                             const char *pass, int is_proxy) {
  static_cast<net::HttpsClient *>(client)->set_auth(user, pass, is_proxy);
}

void rtb_ssl_client_follow_redirects(rtb_ssl_client *client, int boolean) {
  static_cast<net::HttpsClient *>(client)->follow_redirects(boolean);
}

void rtb_ssl_client_expires_at(rtb_ssl_client *client, int seconds) {
  static_cast<net::HttpsClient *>(client)->expires_at(seconds);
}

rtb_response *rtb_ssl_client_get(rtb_ssl_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpsClient *>(client)->Get(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_ssl_client_head(rtb_ssl_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpsClient *>(client)->Head(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_ssl_client_post(rtb_ssl_client *client, const char *path,
                                  enum rtb_post_type type, const char *msg) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpsClient *>(client)
            ->Post(path, static_cast<net::PostContentType>(type), msg)
            .unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_ssl_client_put(rtb_ssl_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpsClient *>(client)->Put(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

rtb_response *rtb_ssl_client_delete(rtb_ssl_client *client, const char *path) {
  net::Response *temp;
  try {
    temp = new (std::nothrow) net::Response(
        static_cast<net::HttpsClient *>(client)->Delete(path).unwrap());
    return temp;
  } catch (...) {
    return NULL;
  }
}

void rtb_ssl_client_get_async(rtb_ssl_client *client, const char *path,
                              rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpsClient *>(client)->async_get(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_ssl_client_head_async(rtb_ssl_client *client, const char *path,
                               rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpsClient *>(client)->async_head(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_ssl_client_put_async(rtb_ssl_client *client, const char *path,
                              rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpsClient *>(client)->async_put(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_ssl_client_post_async(rtb_ssl_client *client, const char *path,
                               enum rtb_post_type type, const char *msg,
                               rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpsClient *>(client)->async_post(
        path, static_cast<net::PostContentType>(type), msg,
        [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

void rtb_ssl_client_delete_async(rtb_ssl_client *client, const char *path,
                                 rtb_client_continuation cb, void *args) {
  try {
    static_cast<net::HttpsClient *>(client)->async_delete(
        path, [=](const net::Response &res) { cb(&res, args); });
  } catch (...) {
    return;
  }
}

rtb_future_response *rtb_ssl_client_get_future(rtb_ssl_client *client,
                                               const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpsClient *>(client)->async_get(path,
                                                         asio::use_future));
}

rtb_future_response *rtb_ssl_client_head_future(rtb_ssl_client *client,
                                                const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpsClient *>(client)->async_head(path,
                                                          asio::use_future));
}

rtb_future_response *rtb_ssl_client_post_future(rtb_ssl_client *client,
                                                const char *path,
                                                enum rtb_post_type type,
                                                const char *msg) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpsClient *>(client)->async_post(
          path, static_cast<net::PostContentType>(type), msg,
          asio::use_future));
}

rtb_future_response *rtb_ssl_client_put_future(rtb_ssl_client *client,
                                               const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpsClient *>(client)->async_put(path,
                                                         asio::use_future));
}

rtb_future_response *rtb_ssl_client_delete_future(rtb_ssl_client *client,
                                                  const char *path) {
  return new (std::nothrow) std::future<net::Response>(
      static_cast<net::HttpsClient *>(client)->async_delete(path,
                                                            asio::use_future));
}

#endif
