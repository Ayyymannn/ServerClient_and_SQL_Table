#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 5000
#define BUFFER_SIZE 1024

// receive message from server
void *receive_messages(void *sock) {
    int server_socket = *(int *)sock;
    char buffer[BUFFER_SIZE];
    
    while(1){
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(server_socket, buffer, sizeof(buffer));
        if (valread > 0){
        printf("%s\n", buffer);
        }
    }

}

int main(){

    int sock = 0;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    pthread_t client_thread;

    // Create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }


    printf("Connected to weather server.\n");

    pthread_create(&client_thread, NULL, receive_messages, &sock);


    while(1){
        // Send data to the server
        memset(buffer, 0, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }
    

    close(sock);
    return 0;
}
