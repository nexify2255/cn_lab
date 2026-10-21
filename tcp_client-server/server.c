#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *message = "Helo from server...";

    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd < 0){
        perror("Socker failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    if(bind(server_fd,(struct sockaddr *)&address,addrlen) < 0 ){
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,3) < 0){
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is Listening....");

    new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t*)&addrlen);
    if(new_socket < 0){
        perror("Accept");
        exit(EXIT_FAILURE);
    }

    read(new_socket,buffer,1024);
    printf("Client: %s\n",buffer);

    send(new_socket,message,strlen(message),0);
    printf("Message send to client\n");

    close(new_socket);
    close(server_fd);

    return 0;

}