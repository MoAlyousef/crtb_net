#define rtb_ENABLE_SSL
#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>

int main() {
  rtb_response *resp = NULL;
  char *content = NULL;
  
  SSL_CTX* ctx = SSL_CTX_new(TLSv1_2_client_method());
  SSL_CTX_set_mode(ctx, 0);
  SSL_CTX_set_default_verify_paths(ctx);

  rtb_ssl_client *client = rtb_ssl_client_init(ctx);
  if (!client)
    return -1;

  rtb_ssl_client_set_host(client, "example.com", 80);
  rtb_ssl_client_expires_at(client, 30);

  /* runs GET / and returns an rtb_response*, which will need freeing later */
  resp = rtb_ssl_client_get(client, "/");
  if (!resp)
    return -1;

  content = rtb_response_content(resp);
  if (!content)
    return -1;
  printf("%s\n", content);
  free(content);

  /* cleanup */
  rtb_response_free(resp);
  rtb_ssl_client_free(client);
}
