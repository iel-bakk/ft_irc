#include "../Classes/Channel.hpp"

Channel:: Channel()
{
}

Channel:: ~Channel()
{
}

int Channel:: parse_channel(std:: string channel)
{
    
    std:: string tab;

    tab = channel.substr(channel.find(' ') + 1);
    if (tab.find(' ') != std:: string:: npos)
    {
        this->name = tab.substr(tab.find(' ') + 1);
        return (0);
    }
    else if (tab.find('#') == std:: string:: npos)
    {
        std:: cout << "NO channel" << std:: endl;
        return (0);
    }
    this->name = tab;
    return (0);
}
