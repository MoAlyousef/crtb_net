#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Example: ./downloader http://i.4cdn.org /v/1584293569989.jpg image.jpg
*/

int main(int argc, char **argv) {
  rtb_client *client = NULL;
  FILE* out = NULL;
  unsigned int retval = 0;
  rtb_response *resp = NULL;
  rtb_content content;
  
  if (argc != 4) {
    fprintf(stderr, "Usage: ./downloader address url output_file\n");
    return -1;
  }

  client = rtb_client_init();
  if (!client)
    return -1;

  rtb_client_set_host(client, argv[1], 80);
  rtb_client_expires_at(client, 30);
  resp = rtb_client_get(client, argv[2]);
  if (!resp)
    return -1;

  content = rtb_response_content(resp);

  out = fopen(argv[3], "wb");
  if(!out) {
    fprintf(stderr, "Failed to create file!\n");
    return -1;
  }

  /* Binary write */
  retval = fwrite(content.value, 1, content.size, out);
  
  /* cleanup */
  fclose(out);
  free(content.value);
  rtb_response_free(resp);
  rtb_client_free(client);

  if(retval != content.size)
    return -1;

  return 0;
}
