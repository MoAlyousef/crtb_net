#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(void) {
  rtb_client *client = NULL;
  rtb_response *resp = NULL;
  char *headers = NULL;
  rtb_content content = {0};

  client = rtb_client_init();
  if (!client)
    return -1;

  rtb_client_set_host(client, "example.com", 80);
  /* 
  rtb_client_set_proxy(client, "10.140.195.115", 8080);
  rtb_client_set_auth(client, "user", "pass", TRUE);
  rtb_client_follow_redirects(client, FALSE); 
  */
  rtb_client_expires_at(client, 30);

  /* runs GET / and returns an rtb_response*, which will need freeing later */
  resp = rtb_client_get(client, "/");
  if (!resp)
    return -1;

  /* returns an allocated char* which needs freeing with a simple free */
  headers = rtb_response_headers_to_string(resp);
  if (!headers)
    return -1;
  printf("%s\n", headers);
  free(headers);

  content = rtb_response_content(resp);
  printf("%s\n", content.value);

  /* cleanup */
  free(content.value);
  rtb_response_free(resp);
  rtb_client_free(client);
}
