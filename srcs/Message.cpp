#include "../Classes/Message.hpp"

Message:: Message()
{
}

Message:: Message(int socket)
{
    this->socket = socket;
    client = Client();
    this->enter = false;
    this->params = create_vector();
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

int Message:: get_socket(void)
{
    return (this->socket);
}

std:: string Message:: get_command(void)
{
    return (this->command);
}

std:: string Message:: get_message_to_send(void)
{
    return (this->message_to_send);
}

std:: string Message:: get_user_to_send(void)
{
    return (this->user_to_send);
}

std:: string Message:: get_password(void)
{
    return (this->password);
}

std:: string Message:: get_welcome_message(void)
{
    return (this->welcome_message);
}

std:: string Message:: get_host_message(void)
{
    return (this->host_message);
}

std:: string Message:: get_server_message(void)
{
    return (this->server_message);
}

std:: string Message:: get_my_user(void)
{
    return (this->my_user);
}

std:: string Message:: get_notice_private(void)
{
    return (this->notice_private);
}

void Message:: set_message(std:: string message)
{
    this->message = message;
}

int Message:: parse_message(std:: string password, std:: string message)
{
    int check = 0;

    this->message = message;
    if (this->message[0] == ':')
    {
        size_t prefix_end = this->message.find(' ');
        if (prefix_end == std::string::npos)
            return check = 12;
        this->prefix = this->message.substr(1, prefix_end - 1);
        this->message = this->message.substr(prefix_end + 1);
    }
    size_t command_end = this->message.find(' ');
    this->command = this->message.substr(0, command_end);
    this->message = this->message.substr(command_end + 1);
    if (this->message.find(' ') != std:: string:: npos )
        this->message = handle_space(this->message, this->command);
    if (this->message.substr(0, 4) == "QUIT")
        return 11;
    // if (command_end == std::string::npos)
    //     return check = 12;
    check = check_Password(this->params.size(), this->command, this->message, password, message);
    if (check_upper(this->command))
        return check = 12;
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
            message = this->command + " " + this->message;
            this->params.push_back(message);
            break ;
        }
    }
    check = check_my_vector(this->params);
    if (check != 0 && check != 13 && check != 14)
        this->params.erase(this->params.end() - 1);
    std:: cout << "**********************************" << std:: endl;
    for (size_t i = 0; i < this->params.size(); i++)
        std:: cout << this->params[i] << std:: endl;
    std:: cout << "**********************************" << std:: endl;
    return (check);
}

int Message:: check_my_vector(std:: vector<std:: string> params)
{
   std:: vector<std:: string>:: iterator it;
   int index;
   int check;

   check = 0;
   for (it = params.begin(); it != params.end(); it++)
   {
        if (check_command(this->command))
        {
            if (it->find("NICK") != std:: string:: npos)
            {
                index = std:: distance(params.begin(), it);
                check = client.parse_nickname(params[index]);
                this->my_user = client.get_nick_name();
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
            else if (it->find("PRIVMSG") != std:: string:: npos)
            {
                if (client.get_nick_name().size() != 0 && client.get_user_name().size())
                {
                    index = std:: distance(params.begin(), it);
                    check = parse_private_message(params[index]);
                    this->notice_private = " PRIVMSG ";
                }
                else
                    check = 451;
            }   
            else if (it->find("NOTICE") != std:: string:: npos)
            {
                if (client.get_nick_name().size() != 0 && client.get_user_name().size())
                {
                    index = std:: distance(params.begin(), it);
                    check = parse_private_message(params[index]);
                    this->notice_private = " NOTICE ";
                }
                else
                    check = 451;
            }   
        }
        else
            check = 12;
   }
   check = send_Message_identification(check);
   return (check);
}

int Message:: check_Password(int size, std:: string command, std:: string message, std:: string password, std:: string request)
{
    int check;
    int found_newline;
    std:: string my_password;

    check = 0;
    check = check_Error_Space(this->command, request);
    if (check != 0)
        return check;
    if (message.find('\n') != std:: string:: npos)
    {
        found_newline = message.find('\n');
        my_password = message.substr(0, found_newline - 1);
    }
    if (size == 0)
    {
        if (command != "PASS")
            return check = 464;
        if (my_password != password)
            return check = 464;
    }
    else
    {
        if (command == "PASS" && my_password != password)
            return check = 464;
        else
            this->password = password;
    }
    return (check);
}

int Message:: check_upper(std:: string command)
{
    for (size_t i = 0; i < command.size() - 2; i++)
    {
        if (!std::isupper(command[i]))
            return (1);
    }
    return (0);
}

int Message:: check_Error_Space(std:: string command, std:: string request)
{
    int check;
    int count;

    count = 0;
    check = 0;
    for (size_t i = 0; i != request.size(); i++)
    {
        if (request[i] == ' ')
            ++count;
    }
    if (command == "PASS" && count > 1)
        return check = 464;
    if(request[request.size() - 3] == ' ')
        --count;
    if (count == 0)
    {
        if (command.find("PASS") != std:: string:: npos || command.find("USER") != std:: string:: npos)
            return check = 461;
        else if (command.find("NICK") != std:: string:: npos)
            return check = 431;
    }
    return check;
}

int Message:: send_Message_identification(int check)
{
    std:: string message;
    char hostname[256];
    char time_str[11];
    std:: time_t    now = std::time(NULL);
    std:: tm    *local_time = std:: localtime(&now);

    std::strftime(time_str, sizeof(time_str), "%d/%m/%Y", local_time);
    gethostname(hostname, sizeof(hostname));
    if (client.get_nick_name().size() != 0 && client.get_user_name().size() != 0 && this->enter == false)
    {
        this->welcome_message = ": 001 " + client.get_nick_name() + " Welcome to Internet Chat Relay";
        this->host_message = ": 002 " + client.get_nick_name() + " Your Host is " + std:: string(hostname) + ", running version 1.0";
        this->server_message = ": 003 " + client.get_nick_name() + " Ther server was created on " + std:: string(time_str);
        this->enter = true;
        return (check = 13);
    }
    return (check);
}

std:: string Message:: handle_space(std:: string message, std:: string command)
{
    std:: string str;
    int count = 0;
    size_t size;

    size = message.size();
    if (command == "PASS" && command == "NICK")
    {
        for (size_t i = 0; i != size; i++)
        {
            if (message[i] != ' ')
                str += message[i];
        }
        return (str);
    }
    else
    {
        for (size_t i = 0; i != size; i++)
        {
            if (message[i] == ' ')
                count++;
        }
        if (count == 3)
            return message;
        else
        {
            bool previous_was_space = true;
            for (size_t i = 0; i != size - 2; i++)
            {
                if(std::isspace(message[i]))
                {
                    if (!previous_was_space)
                    {
                        str += ' ';
                        previous_was_space = true;
                    }
                }
                else
                {
                    str += message[i];
                    previous_was_space = false;
                }
            }
        }
    }
    return str;
}

int Message:: parse_private_message(std:: string message)
{
    int check;
    int count;
    std:: string user;
    std:: string _message;

    check = 14;
    count = 0;
    for (size_t i = 0; i != message.size(); i++)
    {
        if (message[i] == ' ')
            ++count;
        if (count == 1)
        {
            if (message[i] != ' ')
            {
                user += message[i];
            }
        }
        else if (count >= 2)
        {
            if (_message.find(":") != std:: string:: npos)
                _message += message[i];
            else
            {
                if (count == 2)
                    _message += message[i];
            }
        }
    }
    if (_message.find(":") != std:: string:: npos)
        _message.erase(0, 2);
    else
        _message.erase(0, 1);
    if (message[message.size() - 1] == ' ')
        --count;
    if (count < 2)
        return check = 412;
    this->user_to_send = user;
    this->message_to_send = _message;
    return check;
}

bool Message:: check_command(std:: string command)
{
    if (command != "PASS" && command != "NICK"  \
    && command != "USER" && command != "PRIVMSG" && command != "NOTICE" && command != "JOIN")
        return false;
    return true;
}

std:: vector<std:: string> Message:: create_vector(void)
{
    return std:: vector<std:: string>();
}