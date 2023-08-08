#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 12345

int main() {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        printf("Socket creation failed");
        return -1;
    }

    // Bind socket
    struct sockaddr_in server_address;

    // Set all to 0
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        printf("Binding failed");
        //close(server_socket);
        return -1;
    }

    printf("Server socket created and bound successfully!\n");

    // Other server logic...

    //close(server_socket);
    return 0;
}
