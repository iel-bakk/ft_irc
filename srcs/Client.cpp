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
}

void Client:: set_user(std:: string message)
{
   this->user_name = message;
}

int Client:: parse_nickname(std:: string vector)
{
   int find_space;
   int find_newline;
   int check;
   std:: string message;

   
   check = 0;
   find_space = vector.find(' ');
   message = vector.substr(find_space + 1);
   if (message.find('\n') != std:: string:: npos)
   {
        find_newline = message.find('\n');
        message = message.substr(0, find_newline - 1);
   }
   if (message.find(' ') != std:: string:: npos)
   {
        find_space = message.find(' ');
        message = message.substr(0, find_space);
   }
    if (this->nick_name == message)
        return check = 432;
    else
       this->nick_name = message;
   return check;
}

int Client:: parse_username(std:: string vector)
{
   int count = 0;
   int check = 0;
   int sentenceCount = 0;
   std:: string sentences[5];
   std:: string sentence;
   size_t lastsentence = -1;
   check = 0;

   for (size_t i = 0; i != vector.size(); i++)
   {
        if (vector[i] ==' ')
        {
            sentence = vector.substr(lastsentence + 1, i - lastsentence);
            sentences[sentenceCount] = sentence;
            sentenceCount++;
            count++;
            lastsentence = i;
        }
   }
   if (count != 4)
       return (check = 461);
    if (lastsentence < vector.size() - 1)
    {
        sentence = vector.substr(lastsentence + 1);
        sentences[sentenceCount] = sentence;
        sentenceCount++;
    }
    if (this->user_name == sentences[1])
        return (check = 462);
    for (size_t i = 0; i != sentences[2].size() - 2; i++)
    {
        if (!isdigit(sentences[2][i]))
            return (10); // ??????????
    }
    this->user_name = sentences[1];
    this->mode = sentences[2];
    this->unused = sentences[3];
    this->realname = sentences[4];
   return (check);
}
