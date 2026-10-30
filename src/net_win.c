#include "net.h"
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")   /* or link via Makefile */

int net_init(void) {
    WSADATA w;
    return WSAStartup(MAKEWORD(2,2), &w);
}

void net_cleanup(void) { WSACleanup(); }

int net_connect(sock_t *out, const char *host, const char *port) {
    struct addrinfo hints = {0}, *res, *p;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port, &hints, &res) != 0) return -1;

    for (p = res; p; p = p->ai_next) {
        SOCKET s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (s == INVALID_SOCKET) continue;
        if (connect(s, p->ai_addr, (int)p->ai_addrlen) == 0) {
            *out = s;
            freeaddrinfo(res);
            return 0;
        }
        closesocket(s);
    }
    freeaddrinfo(res);
    return -1;
}

int net_send_all(sock_t s, const void *buf, size_t len) {
    const char *p = buf;
    while (len) {
        int n = send(s, p, (int)len, 0);
        if (n <= 0) return -1;
        p += n; len -= n;
    }
    return 0;
}

int net_recv_all(sock_t s, void *buf, size_t len) {
    char *p = buf;
    while (len) {
        int n = recv(s, p, (int)len, 0);
        if (n <= 0) return -1;
        p += n; len -= n;
    }
    return 0;
}

void net_close(sock_t s) { closesocket(s); }