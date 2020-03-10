# crtb_net
C wrapper around rtb_net

Build using cmake:

```
cmake -B bin
camke --build bin
./server
```

The example server should listen on 127.0.0.1:8000 and should serve the pages in the docroot statically. Also any request to 127.0.0.1:8000/hello/{name} with the name placeholder accepting any string since it has an explicit handler.

```
void hello_handler(const rtb_request *req, rtb_response *resp, void *args) {
  rtb_request_placeholder placeholders[1];
  rtb_request_get_placeholders(req, placeholders, 1);
  const char *name = placeholders[0].value;
  char content[200];
  snprintf(content, 200,
           "<html>"
           "<head><title>Hello</title></head>"
           "<body><h1>Hello %s</h1></body>"
           "</html>",
           name);
  rtb_response_set_content(resp, content);
}

int main() {
  rtb_server *server = rtb_server_init("127.0.0.1", 8000, ".");
  if (!server) return -1;
  rtb_server_route(server, "GET", "/hello/{name}", &hello_handler, NULL);
  rtb_server_run(server);
}
```
