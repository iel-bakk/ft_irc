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
        if (tab.find('&'))
            return 461;
        this->name = tab.substr(0, tab.find(' '));
        this->password = tab.substr(tab.find(' ') + 1);
        return (0);
    }
    else if (!tab.find('#'))
    {
        this->name = tab;
        return (0);
    }
    return (461);
}
