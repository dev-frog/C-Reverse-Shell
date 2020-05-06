#include <stdio.h>
#include <sys/types.h>
// #include <sys/socket.h>
#include <winsock2.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock, client_socket;
    char buffer[1024];
    char response[18384];
    struct sockaddr_in server_address, client_address;
    int i = 0, optval = 1;
    socklen_t client_lenght;
    sock = socket(AF_INET, SOCK_STREAM, 0);
}