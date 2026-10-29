#ifndef SHELL_H
#define SHELL_H

#ifdef _WIN32
  #include <winsock2.h>
  typedef SOCKET shell_sock_t;
#else
  typedef int shell_sock_t;
#endif

/* Bind the socket to stdin/stdout/stderr of a shell process */
int shell_spawn(shell_sock_t s);
int shell_wait(void);

#endif