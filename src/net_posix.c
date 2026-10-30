#include "net.h"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int net_init(void) { return 0; }
void net_cleanup(void) { }

int net_connect(sock_t *out, const char *host, const char *port) {
    struct addrinfo hints = {0}, *res, *p;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port, &hints, &res) != 0) return -1;

    for (p = res; p; p = p->ai_next) {
        int fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) {
            *out = fd;
            freeaddrinfo(res);
            return 0;
        }
        close(fd);
    }
    freeaddrinfo(res);
    return -1;
}

int net_send_all(sock_t s, const void *buf, size_t len) {
    const char *p = buf;
    while (len) {
        ssize_t n = send(s, p, len, 0);
        if (n <= 0) return -1;
        p += n; len -= n;
    }
    return 0;
}

int net_recv_all(sock_t s, void *buf, size_t len) {
    char *p = buf;
    while (len) {
        ssize_t n = recv(s, p, len, 0);
        if (n <= 0) return -1;
        p += n; len -= n;
    }
    return 0;
}

void net_close(sock_t s) { close(s); }