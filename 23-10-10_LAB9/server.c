// Write a program where two clients send a number each, server checks whether
// its prime, and returns the result to 2nd client. 2nd client's number is
// checked if its perfect and result is returned to 1st client.


// Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int isPerfect( int num ){
    int sum = 0;
    for( int i = 1; i < num; i++ )
        if( num % i == 0 )
            sum += i;
    
    return sum == num;
}

int isPrime( int num ){
    for( int i = 2; i < num/2; i++ )
        if( num % i == 0 )
            return 0;
    
    return 1;
}

int main() {
    int server_socket, client1, client2;
    struct sockaddr_in server_addr, client1_addr, client2_addr;
    socklen_t addr_size, addr_size2;
    char buffer[1024], buffer2[1024];

    // Create the socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == 0) {
        printf("Listening on port %d...\n", PORT);
    } else {
        perror("Error in listening");
        exit(1);
    }

    addr_size = sizeof(client1_addr);
    client1 = accept(server_socket, (struct sockaddr*)&client1_addr, &addr_size); // Accept connection
    printf("Client 1 connected\n");
    addr_size2 = sizeof(client2_addr);
    client2 = accept( server_socket, (struct sockaddr*)&client2_addr, &addr_size2);
    printf("Client 2 connected\n");

    int num1 = 0, num2 = 0;
    // Read data from the client1
    recv(client1, buffer, sizeof(buffer), 0);
    sscanf(buffer, "%d", &num1);
    // Read data from the client2
    recv(client2, buffer, sizeof(buffer), 0);
    sscanf(buffer, "%d", &num2);

    // Print
    printf("Request received: %d for prime and %d for perfect.\n", num1, num2);

    // Prepare the response
    char response[1024];
    snprintf(response, sizeof(response), "Is Prime?: %s\n", isPrime(num1) ? "Yes" : "No");

    // Send response back to the client2
    send(client2, response, strlen(response), 0);
    // Print
    printf("Response sent: %s", response);

    // Prepare 2nd response
    memset( response, 0, sizeof(response));
    snprintf(response, sizeof(response), "Is Perfect?: %s\n", isPerfect(num2) ? "Yes" : "No");
    // Send response back to the client1
    send(client1, response, strlen(response), 0);
    // Print
    printf("Response sent: %s", response);

    close(client1);
    close(client2);
    close(server_socket);

    return 0;
}
