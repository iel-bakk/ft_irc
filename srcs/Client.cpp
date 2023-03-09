#include "../Classes/Client.hpp"

Client:: Client()
{
}

Client:: ~Client()
{
}

std:: string Client:: get_nick_name(void)
{
    return (this->nick_name);
}

std:: string Client:: get_user_name(void)
{
    return (this->user_name);
}

void Client:: set_nick(std:: string message)
{
   this->nick_name = message;
   std:: cout << "NICK : " << this->nick_name << std:: endl;
}

void Client:: set_user(std:: string message)
{
   this->user_name = message;
   std:: cout << "USER : " << this->user_name << std:: endl;
}