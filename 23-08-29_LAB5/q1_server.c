// WAP where the client will send a number and the server will check whether its armstrong number or not
// gcc -lm q1_server.c && ./a.out

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define SERVER_PORT 4952 // the port users will be connecting to
#define MAXBUFLEN 200

int isArmstrong(int number) {
    int originalNumber = number;
    int numDigits = 0;
    
    // Count the number of digits in the number
    while (number != 0) {
        number /= 10;
        numDigits++;
    }
    
    number = originalNumber;
    int sum = 0;
    
    // Calculate the sum of digits raised to the power of numDigits
    while (number != 0) {
        int digit = number % 10;
        sum += pow(digit, numDigits);
        number /= 10;
    }
    
    return sum == originalNumber;
}

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
    int num = atoi(buf);
    if( !isArmstrong(num) )
        printf("Not ");
    printf("Armstrong number: %d", num);

    close(sockfd);
    return 0;
}