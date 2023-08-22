/*
** A datagram "client" demo
*/
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4952 // the port users will be connecting to

int main() {
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    // struct hostent *he;
    int numbytes;
    char arg[30];
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(SERVER_PORT);
    // Connect to server
    their_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    printf("Enter a message: ");
    scanf("%[^\n]s", arg);
    numbytes = sendto(sockfd, 
                        arg,
                        strlen(arg),
                        0, 
                        (struct sockaddr *)&their_addr,
                        sizeof their_addr
                );
    if (numbytes == -1) {
        perror("sendto");
        exit(1);
    }
    printf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
    close(sockfd);
    return 0;
}