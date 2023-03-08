#include "srcs/utils.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "commands/Command.hpp"
#include "commands/Quit.hpp"
// #include “commands/PrivMsg.hpp”
#include <iostream>

int main()
{
//      Server(int port, std::string password, std::string adminName, std::string adminPassword);
    Server server(6667, "password", "admin", "admin");
	Client client( 0, "name", "nickName");
    Channel channel("#Quit", client);
    Server::addChannel(channel);
    Server::addClient(client);

    Quit quit(client, channel.getName());
    std::cout << quit.execute().getMessage() << std::endl;
    // Join join(“new”, user);
    // Message mssag = jin.excut();
    // PrivMsg privMg(usr, "#name", “hello”);
    // Message message = privMsg.execute();
    // std::cout << message.getMessage() << std::endl;
    return (0);
}