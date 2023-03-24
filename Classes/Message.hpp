#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include "../Classes/Client.hpp"
#include "../Classes/Channel.hpp"

class Message
{
private:
    int socket;
    bool enter;
    std:: string message;
    std:: string welcome_message;
    std:: string host_message;
    std:: string server_message;
    std:: string prefix;
    std:: string command;
    std:: string password;
    std:: string my_user;
    std:: string user_to_send;
    std:: string message_to_send;
    std:: string notice_private;
    std:: vector<std:: string> params;
    Client client;
    Channel channel;
public:
    Message();
    Message(int socket);
    Message(std:: string message);
    ~Message();

    std:: string get_message(void);
    std:: string get_welcome_message(void);
    std:: string get_host_message(void);
    std:: string get_server_message(void);
    std:: string get_command(void);
    std:: string get_my_user(void);
    std:: string get_user_to_send(void);
    std:: string get_message_to_send(void);
    std:: string get_password(void);
    std:: string get_notice_private(void);
    int get_socket(void);
    void set_message(std:: string message);
    std:: string handle_space(std:: string message, std:: string command);
    int parse_message(std:: string password, std:: string message);
    int check_upper(std:: string command);
    int check_my_vector(std:: vector<std:: string> params);
    int check_Error_Space(std:: string command);
    int send_Message_identification(int check);
    int check_Password_Space(int size, std:: string command, std:: string message, std:: string password);
    int parse_private_message(std:: string message);
    std:: vector<std:: string> create_vector(void);
    bool check_command(std:: string command);
};

#endif