#include "crtb_net.h"
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  rtb_response *resp = NULL;
  rtb_content content;
  SSL_CTX *ctx;

  ctx = SSL_CTX_new(TLSv1_2_client_method());
  if (!ctx)
    return -1;

  SSL_CTX_set_mode(ctx, 0);
  SSL_CTX_set_default_verify_paths(ctx);

  rtb_ssl_client *client = rtb_ssl_client_init(ctx);
  if (!client)
    return -1;

  rtb_ssl_client_set_host(client, "www.example.com", 443);

  rtb_ssl_client_expires_at(client, 30);

  /* runs GET / and returns an rtb_response*, which will need freeing later */
  resp = rtb_ssl_client_get(client, "/");
  if (!resp)
    return -1;

  content = rtb_response_content(resp);
  printf("%s\n", content.value);

  /* cleanup */
  free(content.value);
  rtb_response_free(resp);
  rtb_ssl_client_free(client);
}
