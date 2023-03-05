#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    const char *message = "hello, server!";
    write(sockfd, message, strlen(message));

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int n = read(sockfd, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        std:: cout << "Message From Server : " << buffer << std:: endl;
    }
    close(sockfd);

}