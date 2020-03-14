#include "crtb_net.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    long port = 0;
    rtb_server *server = NULL;

    if(argc < 3) {
        fprintf(stderr, "Usage: ./"main host port");
        return -1;
    }

    port = atol(argv[2]);
    if(!port) {
        fprintf(stderr, "Please enter a valid port");
        return -1;
    }

    server = rtb_server_init(argv[1], port, ".", 2);
    if(!server) {
        fprint(stderr, "Failed to initialize server");
        return -1;
    }
    return rtb_server_run(server);
}
