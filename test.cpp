#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Create array of pollfd structures to monitor multiple sockets
    struct pollfd fds[2];
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    fds[1].fd = 0; // Standard input
    fds[1].events = POLLIN;

    printf("Waiting for incoming connections...\n");

    while (1) {
        // Wait for events on the monitored sockets
        int ready = poll(fds, 2, -1);
        if (ready < 0) {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        // Check for incoming connections on the server socket
        if (fds[0].revents & POLLIN) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                     (socklen_t*)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("New connection from %s:%d\n", inet_ntoa(address.sin_addr),
                   ntohs(address.sin_port));
            fds[2].fd = new_socket;
            fds[2].events = POLLIN;
        }

        // Check for incoming data on the client sockets
        for (int i = 2; i < 3; i++) {
            if (fds[i].revents & POLLIN) {
                valread = read(fds[i].fd, buffer, 1024);
                if (valread == 0) {
                    printf("Client disconnected\n");
                    close(fds[i].fd);
                } else {
                    printf("Received message: %s\n", buffer);
                    send(fds[i].fd, buffer, strlen(buffer), 0);
                }
            }
        }

        // Check for input from standard input
        if (fds[1].revents & POLLIN) {
            fgets(buffer, 1024, stdin);
            send(new_socket, buffer, strlen(buffer), 0);
        }
    }

    return 0;
}