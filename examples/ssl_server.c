#include "crtb_net.h"
#include <openssl/ssl.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char **argv) {
  SSL_CTX *ctx = NULL;
  long port = 0;
  rtb_ssl_server *server = NULL;

  ctx = SSL_CTX_new(TLSv1_2_server_method());
  if (!ctx)
    return -1;

  if (argc < 4) {
    fprintf(stderr, "Usage: ./main host port docroot\n");
    return -1;
  }

  port = atol(argv[2]);
  if (!port) {
    fprintf(stderr, "Please enter a valid port\n");
    return -1;
  }

  server = rtb_ssl_server_init(ctx, argv[1], port, argv[3], 2);
  if (!server) {
    fprintf(stderr, "Failed to initialize server\n");
    return -1;
  }

  rtb_ssl_server_enable_dir_listing(server, FALSE);

  return rtb_ssl_server_run(server);
}
