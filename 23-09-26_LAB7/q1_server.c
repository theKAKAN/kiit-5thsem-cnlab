// Write a program where client sends 2 numbers to the server, the server finds
// out their sum and replies the information back to the client using TCP


// Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[1024];

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

    addr_size = sizeof(new_addr);
    new_socket = accept(server_socket, (struct sockaddr*)&new_addr, &addr_size); // Accept connection

    // Read data from the client
    recv(new_socket, buffer, sizeof(buffer), 0);
    double num1, num2;
    sscanf(buffer, "%lf %lf", &num1, &num2);

    // Add the numbers
    double sum = num1+num2;

    // Print
    printf("Request received: %lf and %lf.\n", num1, num2);

    // Prepare the response
    char response[1024];
    snprintf(response, sizeof(response), "Sum: %.2lf\n", sum);

    // Send response back to the client
    send(new_socket, response, strlen(response), 0);

    // Print
    printf("Response sent: %s", response);

    close(new_socket);
    close(server_socket);

    return 0;
}
