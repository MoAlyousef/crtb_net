#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Example: ./downloader i.4cdn.org /v/1584293569989.jpg image.jpg
*/

int main(int argc, char **argv) {
  FILE* out = NULL;
  int retval = 0;
  if (argc != 4) {
    fprintf(stderr, "Usage: ./downloader address url output_file\n");
    return -1;
  }

  rtb_response *resp = NULL;
  char *content = NULL;

  rtb_client *client = rtb_client_init();
  if (!client)
    return -1;

  rtb_client_set_host(client, argv[1], 80);
  rtb_client_expires_at(client, 30);
  resp = rtb_client_get(client, argv[2]);
  if (!resp)
    return -1;

  content = rtb_response_content(resp);
  if (!content)
    return -1;

  out = fopen(argv[3], "wb");
  if(!out) {
    fprintf(stderr, "Failed to create file!\n");
    return -1;
  }

  retval = fputs(content, out);

  /* cleanup */
  fclose(out);
  free(content);
  rtb_response_free(resp);
  rtb_client_free(client);

  return retval;
}