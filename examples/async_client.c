#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

void async_get_cb(const rtb_response *resp, void *args) {
  rtb_content *content = (rtb_content *)args;
  *content = rtb_response_content(resp);
}

int main(void) {
  rtb_content content1 = {0};
  rtb_content content2 = {0};

  rtb_client *client = rtb_client_init();
  if (!client)
    return -1;

  rtb_client_set_host(client, "www.example.com", 80);

  rtb_client_async_get(client, "/", &async_get_cb, &content1);

  rtb_client_async_get(client, "/index.html", &async_get_cb, &content2);

  printf("%s\n", content1.value);

  printf("%s\n", content2.value);

  /* cleanup */

  free(content1.value);
  free(content2.value);
  rtb_client_free(client);
}
