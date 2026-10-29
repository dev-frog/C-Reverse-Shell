#ifndef NET_H
#define NET_H

#include <stddef.h>

/* Portable socket handle */
#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  typedef SOCKET sock_t;
  #define SOCK_INVALID INVALID_SOCKET
#else
  typedef int sock_t;
  #define SOCK_INVALID (-1)
#endif

/* Lifecycle */
int  net_init(void);        /* WSAStartup on Win, no-op on Linux */
void net_cleanup(void);     /* WSACleanup on Win */

/* Core ops — all return 0 on success, -1 on error */
int  net_connect(sock_t *out, const char *host, const char *port);
int  net_send_all(sock_t s, const void *buf, size_t len);
int  net_recv_all(sock_t s, void *buf, size_t len);   /* exact bytes */
void net_close(sock_t s);

#endif