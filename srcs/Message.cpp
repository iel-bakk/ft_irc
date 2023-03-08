#include "../Classes/Message.hpp"

Message:: Message()
{

}

Message:: Message(std:: string message): message(message)
{
}

Message:: ~Message()
{
}

std:: string Message:: get_message(void)
{
    return (this-> message);
}

void Message:: set_message(std:: string message)
{
    this->message = message;
}

void Message:: parse_message(int *num_fd, std:: string message, std:: string password)
{
    
    this->message = message;
    if (this->message[0] == ':')
    {
        size_t prefix_end = this->message.find(' ');
        if (prefix_end == std::string::npos)
        {
            std:: cout << "Error: no space after prefix" << std:: endl;
            return ;
        }
        this->prefix = this->message.substr(1, prefix_end - 1);
        this->message = this->message.substr(prefix_end + 1);
    }
    size_t command_end = this->message.find(' ');
    if (command_end == std::string::npos)
    {
        std:: cout << "Error: no space after command" << std:: endl;
        return ;
    }
    this->command = this->message.substr(0, command_end);
    this->message = this->message.substr(command_end + 1);
    if (*num_fd == 2)
    {
        if (this->command != "PASS")
        {
            std:: cout << "Invalid Command" << std:: endl;
        }
        else
        {
            if (this->command != password)
            {
                std:: cout << "Error : not same password" << std:: endl;
                return ;
            }
        }
    }
    while (!this->message.empty())
    {
        if (message[0] == ':')
        {
            this->params.push_back(this->message.substr(1));
            break ;
        }
        else
        {
            size_t space_pos = this->message.find(' ');
            if (space_pos == std:: string:: npos)
            {
                this->params.push_back(message);
                break ;
            }
            else
            {
                this->params.push_back(this->message.substr(0, space_pos));
                this->message = this->message.substr(space_pos + 1);
            }
        }
    }
}