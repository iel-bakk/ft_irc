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

void Client:: parse_nickname(std:: string vector)
{
   int find_space;

   find_space = vector.find(' ');
   this->user_name = vector.substr(find_space + 1);
}

int Client:: parse_username(std:: string vector)
{
   int count = 0;
   int check = 0;
   int sentenceCount = 0;
   std:: string sentences[5];
   size_t lastsentence = -1;
   check = 0;

   for (size_t i = 0; i != vector.size(); i++)
   {
        if (vector[i] == ' ')
        {
            std:: string sentence = vector.substr(lastsentence + 1, i - lastsentence);
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
        std:: string sentence = vector.substr(lastsentence + 1);
        sentences[sentenceCount] = sentence;
        sentenceCount++;
    }
    if (this->user_name == sentences[1])
        return (check = 462);
    for (size_t i = 0; i != sentences[2].size() - 1; i++)
    {
        if (!isdigit(sentences[2][i]))
        {
            std:: cout << "Not Numeric" << std:: endl;
            return (0); // ??????????
        }
    }
    this->user_name = sentences[1];
    this->mode = sentences[2];
    this->unused = sentences[3];
    this->realname = sentences[4];
   return (check);
}

