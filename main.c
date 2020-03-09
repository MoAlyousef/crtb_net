#include "rtb_server.h"
#include <stdio.h>
#include <string.h>

void hello_handler(const rtb_request *req, rtb_response *resp, void *args);

int main() {
  rtb_server *server = rtb_server_init("127.0.0.1", 8000, ".");
  if (!server)
    return -1;
  // try address 127.0.0.1:8000/hello/anyname
  rtb_server_route(server, "GET", "/hello/{name}", &hello_handler, NULL);
  rtb_server_run(server);
  rtb_server_free(server); // only called if running failed
  return 0;
}

void hello_handler(const rtb_request *req, rtb_response *resp, void *args) {
  rtb_request_placeholder placeholders[1];
  rtb_request_get_placeholders(req, placeholders, 1);
  int index;
  int i;
  for (i = 0; i < 1; i++) {
    if (strcmp(placeholders[i].key, "name") == 0)
      index = i;
  }
  const char *name = placeholders[index].value;
  char res[200];
  snprintf(res, 200,
           "<html>"
           "<head><title>Hello</title></head>"
           "<body><h1>Hello %s</h1></body>"
           "</html>",
           name);
  rtb_response_set_content(resp, res);
}
