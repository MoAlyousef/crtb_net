#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * Creates a server which serves static pages from a directory
 * And allows directory listing
 */

int main(int argc, char **argv) {
    long port = 0;
    rtb_server *server = NULL;

    if(argc < 4) {
        fprintf(stderr, "Usage: ./main host port docroot\n");
        exit(EXIT_FAILURE);
    }

    port = atol(argv[2]);
    if(!port) {
        fprintf(stderr, "Please enter a valid port\n");
        exit(EXIT_FAILURE);
    }

    server = rtb_server_init(argv[1], port, argv[3], 2);
    if(!server) {
        fprintf(stderr, "Failed to initialize server\n");
        exit(EXIT_FAILURE);
    }

    rtb_server_enable_dir_listing(server, 1);

    return rtb_server_run(server);
}
