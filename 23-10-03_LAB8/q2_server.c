// Write a program where two clients chat with each other through the server
// using TCP
// Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

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

    int from = 0;
    while(1){
        if( from == 0 ){
            recv(client1, buffer, sizeof(buffer), 0);
            printf("Client 1 sent: %s\n", buffer);
            send(client2, buffer, sizeof(buffer), 0);
            from = 1;
        }
        else if( from == 1 ){
            recv(client2, buffer, sizeof(buffer), 0);
            printf("Client 1 sent: %s\n", buffer);
            send(client1, buffer, sizeof(buffer), 0);
            from = 0;
        }
    }

    close(client1);
    close(client2);
    close(server_socket);

    return 0;
}
