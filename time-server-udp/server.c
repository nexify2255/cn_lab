#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <time.h>

#define PORT 9000

int main(){
    int sockfd;

    char buffer[1024];
    struct sockaddr_in server_addr,client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    printf("UDP Time Server Started...\n");
    printf("Running on port %d...\n", PORT);


    while(1){
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client,&len);

        time_t current_time;
        time(&current_time);
        char *time_str = ctime(&current_time);

        sendto(sockfd,time_str,strlen(time_str),0,(struct sockaddr *)&client,len);
        printf("Time request served.\n");

    }
    
    close(sockfd);

    return 0;
}
