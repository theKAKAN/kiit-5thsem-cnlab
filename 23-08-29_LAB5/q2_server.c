// Write a program to send any two numbers from client and perform all arithmetic operations on them in server.

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 4952 // the port users will be connecting to
#define MAXBUFLEN 200

int main() {
    int sockfd;
    struct sockaddr_in my_addr;    // my address information
    struct sockaddr_in their_addr; // connector's address information
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFLEN];
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("Socket creation failed");
        exit(1);
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVER_PORT);
    // Accept connections from any IP
    my_addr.sin_addr.s_addr = INADDR_ANY;
    // memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) == -1) {
        printf("Socket binding failed");
        exit(1);
    }
    addr_len = sizeof their_addr;
    numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,
                             (struct sockaddr *)&their_addr, &addr_len);
    if (numbytes == -1) {
        printf("Recieving from failed");
        exit(1);
    }
    printf("got packet from %s\n", inet_ntoa(their_addr.sin_addr));
    printf("packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    int num1, num2;
    sscanf(buf, "%d %d", &num1, &num2);

    printf("ADD: %d\n", num1+num2);
    printf("MUL: %d\n", num1*num2);
    printf("SUB: %d\n", num1-num2);
    printf("DIV: %.2f\n", num1*1.0/num2);
    printf("MOD: %d\n", num1%num2);

    close(sockfd);
    return 0;
}