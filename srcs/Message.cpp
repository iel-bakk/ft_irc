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

std:: string Message:: get_password(void)
{
    return (this->password);
}

int Message:: parse_message(std:: string password, std:: string message)
{
    int check = 0;
    this->message = message;
    if (this->message[0] == ':')
    {
        size_t prefix_end = this->message.find(' ');
        if (prefix_end == std::string::npos)
        {
            std:: cout << "Invalid Command1" << std:: endl;
            return check;
        }
        this->prefix = this->message.substr(1, prefix_end - 1);
        this->message = this->message.substr(prefix_end + 1);
    }
    size_t command_end = this->message.find(' ');
    this->command = this->message.substr(0, command_end);
    this->message = this->message.substr(command_end + 1);
     if (this->message.substr(0, 4) == "QUIT")
        return 11;
    if (command_end == std::string::npos)
    {
        std:: cout << "Invalid Command" << std:: endl;
        return check;
    }
    if (check_upper(this->command))
    {
        std:: cout << "Invalid Command" << std:: endl;
        return (0);
    }
    check = check_Password(this->params.size(), this->command, this->message, password);
    if (check != 0)
        return check;
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
    std:: cout << "---------------------" << std:: endl;
    std:: vector<std:: string>:: iterator it;
    for (it = this->params.begin(); it != this->params.end() ; it++)
        std:: cout << *it ;
    std:: cout << "---------------------" << std:: endl;
    check = check_command(this->params);
    return (check);
}

int Message:: check_command(std:: vector<std:: string> params)
{
   std:: vector<std:: string>:: iterator it;
   int index;
   int check;

   check = 0;
   for (it = params.begin(); it != params.end(); it++)
   {
        if (it->find("NICK") != std:: string:: npos)
        {
            index = std:: distance(params.begin(), it);
            client.parse_nickname(params[index]);
        }
        else if (it->find("USER") != std:: string:: npos)
        {
            index = std:: distance(params.begin(), it);
            check = client.parse_username(params[index]);
        }
        else if (it->find("JOIN") != std:: string:: npos)
        {
            index = std:: distance(params.begin(), it);
            check = channel.parse_channel(params[index]);
        }
        else if (it->find("QUIT") != std:: string:: npos)
            return check = 11;
   }
   return (check);
}

int Message:: check_Password(int size, std:: string command, std:: string message, std:: string password)
{
    int check;

    check = 0;
    if (size == 0)
    {
        if (command != "PASS")
            return check = 464;
        if (message.find(password))
            return check = 464;
    }
    else
    {
        if (command == "PASS" && message.find(password))
            return check = 464;
        else
            password = password;
    }
    return (check);
}

int Message:: check_upper(std:: string command)
{
    for (size_t i = 0; i < command.size(); i++)
    {
        if (!std::isupper(command[i]))
            return (1);
    }
    return (0);
}