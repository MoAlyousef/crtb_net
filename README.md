# crtb_net
C89 wrapper around rtb_net client and server (multithreaded async using ASIO).

Build using cmake or modify the build.sh script (if on a posix system):

```
git clone https://github.com/moalyousef/crtb_net
cd crtb_net
git submodule update --init
cmake -B bin -DCRTB_BUILD_EXAMPLES=ON
camke --build bin
```
or (for older cmake):
```
git clone https://github.com/moalyousef/crtb_net
cd crtb_net
git submodule update --init
mkdir bin && cd bin
cmake .. -DCRTB_BUILD_EXAMPLES=ON
make
```

To build the ssl_client, pass the -DCRTB_ENABLE_SSL=ON to cmake. 

The server example should listen on 127.0.0.1:8000 and should serve the pages in the docroot statically. Also any request to 127.0.0.1:8000/hello/{name} with the name placeholder accepting any string since it has an explicit handler.

```c
void hello_handler(const rtb_request *req, rtb_response *resp, void *args) {
  char content[200];
  rtb_request_placeholder placeholders[1];
  rtb_request_get_placeholders(req, placeholders, 1);
  snprintf(content, 200,
           "<html>"
           "<head><title>Hello</title></head>"
           "<body><h1>Hello %s</h1></body>"
           "</html>",
           placeholders[0].value);
  rtb_response_set_content(resp, content);
}

int main() {
  rtb_server *server = rtb_server_init("127.0.0.1", 8000, "wwwroot", 2);
  rtb_server_route(server, "GET", "/hello/{name}", &hello_handler, NULL);
  return rtb_server_run(server);
}
```
A minimal static server:
```c
int main() {
  rtb_server *server = rtb_server_init("127.0.0.1", 8000, "wwwroot", 2);
  return rtb_server_run(server);
}
```


The client example should get and print the index page of www.example.com, the client supports proxy and authentication.
```c
int main() {
  rtb_client *client = rtb_client_init();
  rtb_client_set_host(client, "www.example.com", 80);
  rtb_response *resp = rtb_client_get(client, "/");
  char *content = rtb_response_content(resp);
  printf("%s\n", content);
  free(content);
  rtb_response_free(resp);
  rtb_client_free(client);
}
```

Notice that every function returning a char* needs to be cleaned using free(). crtb_net types, since they wrap opaque pointers, need a special free function like rtb_client_free().
