#include "srcs/utils.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "commands/Command.hpp"
#include "commands/Quit.hpp"
#include "commands/Join.hpp"
#include "commands/PrivMsg.hpp"
#include "commands/Oper.hpp"
#include "commands/Kick.hpp"
#include "commands/User.hpp"
#include "commands/Part.hpp"
#include "commands/List.hpp"
#include <iostream>

int main()
{
//      Server(int port, std::string password, std::string adminName, std::string adminPassword);
    Server server(6667, "password", "admin", "admin");
	Client client(0);
    client.setNickName("nickName");
    Client client2(1);
    client2.setNickName("nickName2");
    Client client3(2);
    client3.setNickName("nickName3");
    Client client4(3);
    client4.setNickName("nickName4");
    Client client5(4);
    client5.setNickName("nickName5");
    Client client6(5);
    client6.setNickName("nickName6");

    Channel channel("#Quit", client);
    Server::addChannel(channel);
    Server::addClient(client);
    Server::addClient(client2);
    Server::addClient(client3);
    Server::addClient(client4);
    Server::addClient(client5);
    Server::addClient(client6);
    Quit quit(client);
    std::cout << "------------------Join test------------------" << std::endl;
    Join join(client, "#new");
    Join join2(client2, "#new");
    Join join3(client3, "#new");
    Join join4(client4, "#new");
    Join join5(client5, "#new2");
    Join join6(client6, "#new2");
    try {
        std::vector<Message> mssag = join.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        std::vector<Message> mssag = join2.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        std::vector<Message> mssag = join3.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        std::vector<Message> mssag = join4.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        std::vector<Message> mssag = join5.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        std::vector<Message> mssag = join6.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------findChannel test------------------" << std::endl;
    try {
        Channel newChannel = Server::findChannel(client, "#new");
        std::cout << newChannel.getName() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        Channel newChannel2 = Server::findChannel(client, "#new2");
        std::cout << newChannel2.getName() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        Channel newChannel3 = Server::findChannel(client, "#new3");
        std::cout << newChannel3.getName() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------findClient test------------------" << std::endl;
    std::map<std::string, Client> clients = Server::findChannel(client, "#new").getClients();
    std::map<std::string, Client>::iterator it = clients.begin();
    for (; it != clients.end(); it++)
        std::cout << it->second.getNickName() << std::endl;
    std::cout << "------------------PrivMsg test(to channel)------------------" << std::endl;
    try {
        PrivMsg privMg(client, "#new", "hello");
        std::vector<Message> mssag = privMg.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------PrivMsg test(to client)------------------" << std::endl;
    try {
        PrivMsg privMg(client, client2.getNickName(), "hello");
        std::vector<Message> mssag = privMg.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------PrivMsg test(no channel)------------------" << std::endl;
    try {
        PrivMsg privMg(client, "#new11", "hello");
        std::vector<Message> mssag = privMg.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Oper success------------------" << std::endl;
    Oper oper(client, "admin", "admin");
    try {
        std::vector<Message> mssag = oper.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Oper fail------------------" << std::endl;
    Oper oper2(client2, "admin1", "admin");
    try {
        std::vector<Message> mssag = oper2.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------User test------------------" << std::endl;
    User user(client, "name");
    try {
        std::vector<Message> mssag = user.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Part test------------------" << std::endl;
    try{
        Join join(client, "#Part");
        Join join2(client2, "#Part");
        join.execute();
        join2.execute();
        Part part(client, "#Part");
        std::vector<Message> mssag = part.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    }catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Multi Part test------------------" << std::endl;
    try{
        Join join(client, "#Part,#Part2,#Part3");
        Join join2(client2, "#Part");
        join.execute();
        join2.execute();
        Part part(client, "#Part,#Part2,#Part3,#Part4");
        std::vector<Message> mssag = part.execute();
        for (unsigned int i = 0; i < mssag.size(); i++)
            std::cout << mssag[i].getMessage() << std::endl;
    }catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Part remainder------------------" << std::endl;
    try{
        Part part2(client2, "#Part");
        std::vector<Message> mssag = part2.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    }catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Check Channel Remainder------------------" << std::endl;
    try{
        Server::findChannel(client, "#Part");
    }catch (std::vector<Message> &e){
        std::cout <<e[0].getMessage() << std::endl;
    }
    std::cout << "------------------List test------------------" << std::endl;
    try{
        Join join(client, "#List");
        join.execute();
        join = Join(client2, "#List2");
        join.execute();
        List list(client);
        std::vector<Message> mssag = list.execute();
        for (unsigned int i = 0; i < mssag.size(); i++)
            std::cout << mssag[i].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    std::cout << "------------------Kick test------------------" << std::endl;
    try {
        Kick kick(client, "#List", client.getNickName(), "kick");
        std::vector<Message> mssag = kick.execute();
        std::cout << mssag[0].getMessage() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    try {
        Channel newChannel = Server::findChannel(client, "#List");
        std::cout << newChannel.getName() << std::endl;
    } catch (std::vector<Message> &e) {
        std::cout << e[0].getMessage() << std::endl;
    }
    return (0);
}