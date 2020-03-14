#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* handler signature: void (*) (const rtb_request*, rtb_response*, void*) */
void hello_handler(const rtb_request *req, rtb_response *resp, void *args);

int main() {
  /* == nproc, calls std::thread::hardware_concurrency() */
  unsigned int thread_count = rtb_hardware_concurrency();
  /* init signature: (host, port, document_root, thread_count)
     the server would now automatically serve statically from docroot */
  rtb_server *server =
      rtb_server_init("localhost", 8000, "wwwroot", thread_count);
  if (!server)
    return -1;
  /* route signature: (server, verb, uri with optional placeholders, handler,
     captured args) this allows dynamic request handling try address
     127.0.0.1:8000/hello/anyname */
  rtb_server_route(server, "GET", "/hello/{name}", &hello_handler, NULL);
  return rtb_server_run(server);
}

void hello_handler(const rtb_request *req, rtb_response *resp, void *args) {
  int i = 0;
  int index = 0;
  rtb_request_placeholder placeholders[1] = {0};
  char content[200] = {0};

  rtb_request_get_placeholders(req, placeholders, 1);
  for (; i < 1; i++) {
    /* just to show it's queryable by key */
    if (strcmp(placeholders[i].key, "name") == 0)
      index = i;
  }

  (void)sprintf(content,
                "<html>"
                "<head><title>Hello</title></head>"
                "<body><h1>Hello %s</h1></body>"
                "</html>",
                placeholders[index].value);

  /* setting the response status in a handler is optional for OK */
  rtb_response_set_status(resp, 200);
  /* setting content will automatically set content_length */
  rtb_response_set_content(resp, content);

  /* cleanup of placeholder char* members which were allocated in rtb_request_get_placeholders */
  rtb_request_placeholders_free(placeholders, 1);
}
