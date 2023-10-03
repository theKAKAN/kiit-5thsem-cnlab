#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        printf("Client 1: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send the message to the server
        send(client_socket, buffer, strlen(buffer), 0);
        // Expect to receive a reply
        recv(client_socket, buffer, sizeof(buffer), 0);
        printf("Client 2: %s\n", buffer);

        // Exit if the user types "exit"
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
