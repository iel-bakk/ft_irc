#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>

class Message
{
private:
    std:: string message;
    std:: string prefix;
    std:: string command;
    std:: vector<std:: string> params;
public:
    Message();
    Message(std:: string message);
    ~Message();

    std:: string get_message(void);
    void set_message(std:: string message);

    void parse_message(int *num_fd, std:: string message, std:: string password);
};

#endif