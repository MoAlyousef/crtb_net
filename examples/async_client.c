#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

void async_get1(rtb_response **resp, rtb_client *client, void *args) {
  *resp = rtb_client_get(client, "/");
}

void async_get2(rtb_response **resp, rtb_client *client, void *args) {
  *resp = rtb_client_get(client, "/index.html");
}

int main() {
  rtb_response *resp1 = NULL;
  rtb_response *resp2 = NULL;
  char *content1 = NULL;
  char *content2 = NULL;

  asio_io_context *io_context = asio_io_context_init(4);

  rtb_client *client = rtb_client_init();
  if (!client)
    return -1;

  rtb_client_set_host(client, "www.example.com", 80);

  asio_post(io_context, &async_get1, &resp1, client, NULL);

  asio_post(io_context, &async_get2, &resp2, client, NULL);

  asio_run(io_context);
  
  if (!resp1 || !resp2) return -1;

  content1 = rtb_response_content(resp1);
  if (!content1)
    return -1;
  printf("%s\n", content1);
  free(content1);

  content2 = rtb_response_content(resp2);
  if (!content2)
    return -1;
  printf("%s\n", content2);
  free(content2);

  /* cleanup */
  rtb_response_free(resp1);
  rtb_response_free(resp2);
  rtb_client_free(client);
  asio_io_context_free(io_context);
}