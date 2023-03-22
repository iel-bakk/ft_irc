#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/poll.h>
#include <stdlib.h>
#include <map>
#include "../Classes/Message.hpp"

# define max_num_fds 10

class Server
{
    private:
        int sockfd;
        int client_lenght;
        int num_bytes;
        int port;
        int my_place;
        const char *message;
        int new_socket_fd;
        std:: string localhost;
        std:: string password;
        struct sockaddr_in socker_addr;
        struct pollfd fds[max_num_fds];
        std:: map<int, Message> file_vectors;
    public:
        Server();
        Server(int port, std:: string password);
        Server(std:: string localhost, int port, std:: string password);
        ~Server();
        int get_sockfd();
        int get_client_length();
        int get_Port();
        std:: string get_Password();
        int get_new_socket_fd();
        void create_socket();
        void accept_socket();
        int read_socket();
        int write_socket();
        void bind_socket();
        void listen_socket();
        void read_write_socket(int sockfd, int *num_fds, Message *new_user);
        void send_socket(void);
        void close_socket(int socket);
        int HandleError(int error_replies, int sockfd);
        void add_User(int fd, std:: vector<std:: string> new_user);
        int write_long_message(int sockfd);
        int display_message(int sockfd, std:: string message);
        int display_error(void);
        int send_private_message(void);
};