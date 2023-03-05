#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server
{
    private:
        int sockfd;
        int client_lenght;
        int num_bytes;
        int port;
        int localhost;
        int password;
        int new_socket_fd;
        struct sockaddr_in socker_addr;
    public:
        Server();
        Server(int port, int password);
        Server(std:: string localhost, int port, int password);
        ~Server();
        int get_sockfd();
        int get_client_length();
        int get_Port();
        int get_Password();
        int get_new_socket_fd();
        int create_socket();
        int accept_socket();
        int read_socket();
        int write_socket();
        void bind_socket();
        void listen_socket();
};