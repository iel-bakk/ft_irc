#include "../Classes/Server.hpp"

Server:: Server()
{
}
Server:: ~Server()
{
}
Server:: Server(int port, std:: string password): port(port), password(password)
{
}
Server:: Server(std:: string localhost, int port, std:: string password)
{
    this->localhost  = localhost;
    this->port = port;
    this->password = password;
}

int Server:: get_sockfd(void)
{
    return (this->sockfd);
}

int Server:: get_client_length(void)
{
    return (this->client_lenght);
}

int Server:: get_Port(void)
{
    return (this->port);
}

std:: string Server:: get_Password(void)
{
    return (this->password);
}

int Server:: get_new_socket_fd(void)
{
    return (this->new_socket_fd);
}

void Server:: create_socket(void)
{
    int reuseport = 1;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd == -1)
    {
        std:: cout << "Error: socket not created" << std:: endl;
    }
    setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEPORT, &reuseport, sizeof(reuseport));
}

void Server:: bind_socket(void)
{
    memset((char*)&this->socker_addr, 0, sizeof(this->socker_addr));
    this->socker_addr.sin_family = AF_INET;
    this->socker_addr.sin_port = htons(this->port);
    this->socker_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(this->sockfd, (struct sockaddr *)&this->socker_addr, sizeof(this->socker_addr)) < 0)
    {
        std:: cout << "Failed to listen on socket." << std:: endl;
        close (this->sockfd);
    }
}

void Server:: listen_socket(void)
{
    if (listen(this->sockfd, 5) < 0)
    {
        std:: cout << "Error: Failed to listen on socket." << std:: endl;
        close (this->sockfd);
    }
}

void Server:: accept_socket(void)
{
    size_t size;
    int num_fds;
    int sock;

    size = sizeof(this->socker_addr);
    memset(this->fds, 0, max_num_fds * sizeof(struct pollfd));
    this->fds[0].fd = this->sockfd;
    this->fds[0].events = POLLIN;
    num_fds = 1;
    while (true)
    {
        int ret = poll(this->fds, num_fds, -1);
        if (ret < 0)
        {
            std:: cout << "Error: Poll not Created" << std:: endl;
            exit (-1);
        }
        for (int i = 0; i < num_fds; i++)
        {
            if (this->fds[i].revents & POLLIN)
            {
                if (this->fds[i].fd == this->sockfd)
                {
                    this->new_socket_fd = accept(this->sockfd, (struct sockaddr *)&this->socker_addr, (socklen_t *)&size);
                    if (this->new_socket_fd < 0)
                    {
                        std:: cout << "Failed to accept incoming connection\n" << std:: endl;
                        close (this->sockfd);
                        exit(0);
                    }
                    if (num_fds >= max_num_fds)
                        close (this->new_socket_fd);
                    else
                    {
                        std:: cout << "connection accepted" << std:: endl;
                        this->fds[num_fds].fd = this->new_socket_fd;
                        this->fds[num_fds].events = POLLIN;
                        num_fds++;
                    }
                }
                else
                {
                    sock = this->fds[i].fd;
                    read_write_socket(sock, &num_fds);
                }
            }
        }
    }
}

void Server:: read_write_socket(int sockfd, int *num_fds)
{
    int n;
    int check;
    char buffer[256];

    memset(buffer, 0, sizeof(buffer));
    n = read(sockfd, buffer, 255);
    check = 0;
    if (n < 0)
    {
        std:: cout << "Error: Reading From Socket" << std:: endl;
        exit(1);
    }
    if (n == 0 || !strcmp(buffer, "QUIT Leaving...\r\n"))
    {
        (*num_fds)--;
        return ;
    }
    check = my_message.parse_message(this->password, buffer);
    n = HandleError(check, sockfd);
    if (n < 0)
    {
        std:: cout << "Error: Writing From Socket" << std:: endl;
        exit(1);
    }
}

void Server:: send_socket(void)
{
    if (send(this->new_socket_fd, this->message, strlen(this->message), 0) < 0)
    {
        std:: cout << "Error: Message don't send" << std:: endl;
    }
}

int Server:: HandleError(int error_replies, int sockfd)
{
    int num = 0;

    switch (error_replies)
    {
        case 464:
            num = write(sockfd, "464 ERR_PASSWDMISMATCH:Password incorrect\r\n", 43);
            break;
        case 461:
            num = write(sockfd, "461 ERR_NEEDMOREPARAMS USER :Not enough parameters\r\n", 52);
            break;
        case 11:
            close_socket(this->new_socket_fd);
        default:
            break;
    }
    return (num);
}

void Server:: close_socket(int socket)
{
    std:: cout << "Client is DISCONNECTED." << std:: endl;
    close(socket);
}
