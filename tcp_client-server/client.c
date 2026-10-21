#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 12345

int main(){
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from Client";
    char buffer[1024] = {0};

    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        printf("\nConnection Failed\n");
        return -1;
    }

    send(sock,message,strlen(message),0);
    printf("Message sent to server\n");

    read(sock,buffer,1024);
    printf("Server: %s\n",buffer);

    close(sock);

    
}