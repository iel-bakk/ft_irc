#include "Server.hpp"

Server:: Server()
{
}
Server:: ~Server()
{
}
Server:: Server(int port, int password): port(port), password(password)
{
}
Server:: Server(std:: string localhost, int port, int password): localhost(localhost), port(port), password(password)
{
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

int Server:: get_Password(void)
{
    return (this->password);
}

int Server:: get_new_socket_fd(void)
{
    return (this.n)
}

