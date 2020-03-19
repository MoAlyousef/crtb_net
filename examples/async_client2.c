#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  rtb_client *client = NULL;
  rtb_future_response *fut_resp1 = NULL, *fut_resp2 = NULL;
  rtb_response *resp1 = NULL, *resp2 = NULL;
  rtb_content content1 = {0}, content2 = {0};

  client = rtb_client_init();
  if (!client)
    return -1;

  rtb_client_set_host(client, "www.example.com", 80);

  fut_resp1 = rtb_client_get_future(client, "/");

  fut_resp2 = rtb_client_get_future(client, "/index.html");

  resp1 = rtb_response_await(fut_resp1);

  resp2 = rtb_response_await(fut_resp2);

  content1 = rtb_response_content(resp1);

  content2 = rtb_response_content(resp2);

  printf("%s\n", content1.value);

  printf("%s\n", content2.value);

  /* cleanup */

  free(content1.value);
  free(content2.value);
  rtb_response_free(resp1);
  rtb_response_free(resp2);
  rtb_future_response_free(fut_resp1);
  rtb_future_response_free(fut_resp2);
  rtb_client_free(client);
}
