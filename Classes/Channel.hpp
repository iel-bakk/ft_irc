#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>

class Channel
{
private:
    std:: string name;
public:
    Channel();
    ~Channel();
    int parse_channel(std:: string channel);
};

#endif