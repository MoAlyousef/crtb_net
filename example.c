#include "crtb_net.h"
#include <stdio.h>
#include <string.h>

// handler signature: void (*) (const rtb_request*, rtb_response*, void*);
void hello_handler(const rtb_request *req, rtb_response *resp, void *args);

int main() {
  unsigned int thread_count = rtb_hardware_concurrency();
  // init signature: (host, port, document_root, thread_count)
  // the server would now automatically serve statically from docroot
  rtb_server *server = rtb_server_init("127.0.0.1", 8000, "wwwroot", thread_count);
  if (!server)
    return -1;
  // route signature: (server, verb, uri, handler, args or context)
  // this allows dynamic request handling
  // try address 127.0.0.1:8000/hello/anyname
  rtb_server_route(server, "GET", "/hello/{name}", &hello_handler, NULL);
  rtb_server_run(server);
  // only called if running failed
  rtb_server_free(server);
  return 0;
}

void hello_handler(const rtb_request *req, rtb_response *resp, void *args) {
  int index;
  int i;
  rtb_request_placeholder placeholders[1];
  rtb_request_get_placeholders(req, placeholders, 1);
  for (i = 0; i < 1; i++) {
    if (strcmp(placeholders[i].key, "name") == 0) // just to show it's queryable by key
      index = i;
  }
  const char *name = placeholders[index].value;
  char content[200];
  (void)snprintf(content, 200,
           "<html>"
           "<head><title>Hello</title></head>"
           "<body><h1>Hello %s</h1></body>"
           "</html>",
           name);
  // setting the response status in a handler is optional for OK
  rtb_response_set_status(resp, 200);
  // setting content will automatically set content_length
  rtb_response_set_content(resp, content);
}
