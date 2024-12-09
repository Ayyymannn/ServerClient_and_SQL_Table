#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 2
#define WEATHER_DATA_SIZE 4
int client_sockets[MAX_CLIENTS];

typedef struct {
    char city[100];
    char temp[100];
    char humidity[100];
    char info[100];
} weather;

weather weather_data[WEATHER_DATA_SIZE] = {
    {"victoria", "15°C", "70%", "Cloudy"},
    {"vancouver", "10°C", "80%", "Rainy"},
    {"toronto", "5°C", "65%", "Sunny"},
    {"calgary", "-2°C", "50%", "Snowy"}
};

// Thread function to handle client communication
void *handle_client(void *client_socket) {
    int socket = *(int *)client_socket;
    char buffer[BUFFER_SIZE] = {0};
    int valread;
    int found = 0;

    while(1){
        // clear buffer
        memset(buffer, 0, BUFFER_SIZE);
        // Receive data from the client
        valread = read(socket, buffer, BUFFER_SIZE);
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        if (valread > 0) {
            for(int i = 0; i < WEATHER_DATA_SIZE; i++){  
             
                if(strcmp(buffer, weather_data[i].city) == 0){  
                    // Send message to client 
                    send(socket, weather_data[i].temp, strlen(weather_data[i].temp), 0);
                    sleep(1);
                    send(socket, weather_data[i].humidity, strlen(weather_data[i].humidity), 0);
                    sleep(1);
                    send(socket, weather_data[i].info, strlen(weather_data[i].info), 0);
                    found = 1;
                } 
            }
            if (found == 0){
                char* message = "City not found";
                send(socket, message, strlen(message), 0);
            }
            found = 0;
        }

        // Handle client disconnection
        if (valread == 0) {
            printf("Client disconnected\n");
            close(socket);
            return NULL;
        } 
    
    }

    // Close the client socket
    close(socket); 
    return NULL;
}   


int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t client_threads[MAX_CLIENTS];
    int client_count = 0;
    
    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM,0)) == 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified IP and port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Set the socket to listen for incoming connections
    listen(server_fd, MAX_CLIENTS);
    printf("Chat server started. Waiting for clients...\n");
    while (client_count < MAX_CLIENTS) {
        new_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
        printf("New client connected: Client %d\n", client_count + 1);
        client_sockets[client_count] = new_socket;
        
        // Handle the client in a new thread
        if (pthread_create(&client_threads[client_count], NULL, handle_client, (void *)&new_socket) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    
    client_count++;
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_CLIENTS; i++) {
    pthread_join(client_threads[i], NULL);
    }

    // Close the server socket
    close(server_fd);
    printf("Server shut down.\n");
    return 0;
}
