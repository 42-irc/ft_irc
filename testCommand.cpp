#include "srcs/utils.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "commands/Command.hpp"
#include "commands/Quit.hpp"
#include "commands/Join.hpp"
#include "commands/PrivMsg.hpp"
#include "commands/Oper.hpp"
#include <iostream>

int main()
{
//      Server(int port, std::string password, std::string adminName, std::string adminPassword);
    Server server(6667, "password", "admin", "admin");
	Client client( 0, "name", "nickName");
    Client client2( 1, "name2", "nickName2");
    Client client3( 2, "name3", "nickName3");
    Client client4( 3, "name4", "nickName4");
    Client client5( 4, "name5", "nickName5");
    Client client6( 5, "name6", "nickName6");

    Channel channel("#Quit", client);
    Server::addChannel(channel);
    Server::addClient(client);
    Quit quit(client, channel.getName());
    std::cout << quit.execute().getMessage() << std::endl;
    std::cout << "------------------Join test------------------" << std::endl;
    Join join(client, "#new");
    Join join2(client2, "#new");
    Join join3(client3, "#new");
    Join join4(client4, "#new");
    Join join5(client5, "#new2");
    Join join6(client6, "#new2");
    try {
        Message mssag = join.execute();
        std::cout << mssag.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Message mssag = join2.execute();
        std::cout << mssag.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Message mssag = join3.execute();
        std::cout << mssag.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Message mssag = join4.execute();
        std::cout << mssag.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Message mssag = join5.execute();
        std::cout << mssag.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Message mssag = join6.execute();
        std::cout << mssag.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    std::cout << "------------------findChannel test------------------" << std::endl;
    try {
        Channel newChannel = Server::findChannel(client, "#new");
        std::cout << newChannel.getName() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Channel newChannel2 = Server::findChannel(client, "#new2");
        std::cout << newChannel2.getName() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    try {
        Channel newChannel3 = Server::findChannel(client, "#new3");
        std::cout << newChannel3.getName() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    std::cout << "------------------findClient test------------------" << std::endl;
    std::map<std::string, Client> clients = Server::findChannel(client, "#new").getClients();
    std::map<std::string, Client>::iterator it = clients.begin();
    for (; it != clients.end(); it++)
        std::cout << it->second.getNickName() << std::endl;
    std::cout << "------------------PrivMsg test------------------" << std::endl;
    PrivMsg privMg(client, "#new11", "hello");
    try {
        Message message = privMg.execute();
        std::cout << message.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    std::cout << "------------------Oper success------------------" << std::endl;
    Oper oper(client, "admin", "admin");
    try {
        Message message = oper.execute();
        std::cout << message.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    std::cout << "------------------Oper fail------------------" << std::endl;
    Oper oper2(client2, "admin1", "admin");
    try {
        Message message = oper2.execute();
        std::cout << message.getMessage() << std::endl;
    } catch (Message &e) {
        std::cout << e.getMessage() << std::endl;
    }
    return (0);
}