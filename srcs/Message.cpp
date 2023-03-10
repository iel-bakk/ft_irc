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

int Message:: parse_message(std:: string password, std:: string message)
{
    int check = 0;
    this->message = message;
    if (this->message[0] == ':')
    {
        size_t prefix_end = this->message.find(' ');
        if (prefix_end == std::string::npos)
        {
            std:: cout << "Error: no space after prefix" << std:: endl;
            return check;
        }
        this->prefix = this->message.substr(1, prefix_end - 1);
        this->message = this->message.substr(prefix_end + 1);
    }
    size_t command_end = this->message.find(' ');
    if (command_end == std::string::npos)
    {
        std:: cout << "Error: no space after command" << std:: endl;
        return check;
    }
    this->command = this->message.substr(0, command_end);
    this->message = this->message.substr(command_end + 1);
    if (this->params.size() == 0)
    {
        if (this->command != "PASS")
        {
            std:: cout << "Invalid Command" << std:: endl;
            return check;
        }
        if (this->message.find(password))
            return check = 461;
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
        // if (it->find("PASS") != std:: string:: npos)
        // {
        //     index = std:: distance(params.begin(), it);
        
        //     if (index != 1)
        //     {
        //         std:: cout << "Invalid command" << std:: endl;
        //         return (0);
        //     }
        // }    
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
   }
   return (check);
}