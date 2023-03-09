#include "../Classes/Message.hpp"

Message:: Message()
{

}

Message:: Message(std:: string message, bool found): message(message), found(found)
{
}

Message:: ~Message()
{
}

std:: string Message:: get_message(void)
{
    return (this-> message);
}

bool Message:: get_found(void)
{
    return (this->found);
}

std:: string Message:: get_command(void)
{
    return (this->command);
}

void Message:: set_message(std:: string message)
{
    this->message = message;
}

size_t Message:: get_size_vector(void)
{
    return (this->params.size());
}

void Message:: parse_message(std:: string password, std:: string message)
{
    this->found = true;
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
    if (this->params.size() == 0)
    {
        if (this->command != "PASS")
        {
            std:: cout << "Invalid Command" << std:: endl;
            return ;
        }
        if (this->message.find(password))
        {
            this->found = false;
            return ;
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
    check_command(this->command);
}

void Message:: check_command(std:: string command)
{
    if (command == "NICK")
        client.set_nick(this->message);
    if (command == "USER")
        client.set_nick(this->message);
}