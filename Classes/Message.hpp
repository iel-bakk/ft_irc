#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include "../Classes/Client.hpp"
#include "../Classes/Channel.hpp"

class Message
{
private:
    std:: string message;
    std:: string prefix;
    std:: string command;
    std:: vector<std:: string> params;
    std:: string password;
    Client client;
    Channel channel;
public:
    Message();
    Message(std:: string message);
    ~Message();

    std:: string get_message(void);
    std:: string get_command(void);
    size_t get_size_vector(void);
    std:: string get_password(void);
    void set_message(std:: string message);
    int parse_message(std:: string password, std:: string message);
    int check_command(std:: vector<std:: string> params);
    int check_upper(std:: string command);
    int check_Password(int size, std:: string command, std:: string message, std:: string password);
};

#endif