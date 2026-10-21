#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t len;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char *message = "Hello from UDP Client";
    sendto(sockfd,message,strlen(message),0,(struct sockaddr *)&server_addr,sizeof(server_addr));

    len = sizeof(server_addr);
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&server_addr,&len);

    printf("Server: %s\n", buffer);

    close(sockfd);
    return 0;

}
