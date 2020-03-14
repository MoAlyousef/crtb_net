#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    long port = 0;
    rtb_server *server = NULL;

    if(argc < 3) {
        fprintf(stderr, "Usage: ./main host port");
        exit(EXIT_FAILURE);
    }

    port = atol(argv[2]);
    if(!port) {
        fprintf(stderr, "Please enter a valid port");
        exit(EXIT_FAILURE);
    }

    server = rtb_server_init(argv[1], port, ".", 2);
    if(!server) {
        fprintf(stderr, "Failed to initialize server");
        exit(EXIT_FAILURE);
    }
    return rtb_server_run(server);
}
