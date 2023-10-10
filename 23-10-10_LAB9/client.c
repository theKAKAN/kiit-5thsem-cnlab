#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Set buffer to 0 at first
    memset( buffer, 0, sizeof(buffer) );

    // Create the socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }

    // Input text
    printf("Enter the text: ");
    scanf("%[^\n]s", buffer);

    // Send the numbers to the server
    // snprintf(buffer, sizeof(buffer), "%.2lf %.2lf", num1, num2);
    send(client_socket, buffer, strlen(buffer), 0);

    // Receive and display the response from the server
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Response received:\n\t%s\n", buffer);

    close(client_socket);

    return 0;
}
