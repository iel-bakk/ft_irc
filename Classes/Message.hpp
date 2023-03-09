#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include "../Classes/Client.hpp"

class Message
{
private:
    std:: string message;
    std:: string prefix;
    std:: string command;
    std:: vector<std:: string> params;
    bool found;
    Client client;
public:
    Message();
    Message(std:: string message, bool found);
    ~Message();

    std:: string get_message(void);
    std:: string get_command(void);
    bool get_found(void);
    void set_message(std:: string message);
    size_t get_size_vector(void);
    void parse_message(std:: string password, std:: string message);
    void check_command(std:: string command);
};

#endif