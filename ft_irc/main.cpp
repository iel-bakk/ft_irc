#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int ac, char **av)
{
    // int i;

    // i = 0;
    // if (ac != 3)
    // {
    //     std:: cout << "Must have 3 args" << std:: endl;
    //     return (0);
    // }
    // while (av[1][i])
    // {
    //     if (!isdigit(av[1][i]))
    //     {
    //         std:: cout << "it most have digit" << std:: endl;
    //         return (0);
    //     }
    //     i++;
    // }
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(sockfd, 1);

    while (true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_lengh = sizeof(client_addr);

        int conf = accept(sockfd, (struct sockaddr *)&client_addr, &client_lengh);

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int n = read(conf, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            std:: cout << "******* we get your message ********" << std:: endl;
            std:: cout << "Your message :" << buffer << std:: endl;

            write(conf, buffer, strlen(buffer));
        }
        close (conf);
    }
    close (sockfd);
    return (0);
}


