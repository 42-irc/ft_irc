#include "srcs/utils.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Quit.hpp"
#include "Join.hpp"
#include "PrivMsg.hpp"
#include "Oper.hpp"
#include "Kick.hpp"
#include "User.hpp"
#include "Part.hpp"
#include "List.hpp"
#include "Nick.hpp"
#include <iostream>

void printChannels()
{
    std::cout << "------------------exist channels------------------" << std::endl;
    std::map<std::string, Channel*> channels = Server::getChannels();
    std::map<std::string, Channel*>::const_iterator it = channels.begin();
    std::map<std::string, Channel*>::const_iterator ite = channels.end();
    for (; it != ite; it++) {
        std::cout << "Channel name: " << it->second->getName() << std::endl;
        // std::cout << "Channel operator: " << it->second->getOperator()->getNickName() << std::endl;
        std::cout << "Channel clients: " << std::endl;
        std::map<std::string, Client*> clients = it->second->getClients();
        std::map<std::string, Client*>::const_iterator it2 = clients.begin();
        std::map<std::string, Client*>::const_iterator ite2 = clients.end();
        for (; it2 != ite2; it2++) {
            std::cout << "\tClient name: " << it2->second->getNickName() << std::endl;
        }
    }
    std::cout << std::endl;
}

void printClients()
{
    std::cout << "------------------exist clients------------------" << std::endl;
    std::map<std::string, Client*> clients = Server::getClients();
    std::map<std::string, Client*>::const_iterator it = clients.begin();
    std::map<std::string, Client*>::const_iterator ite = clients.end();
    for (; it != ite; it++) {
        std::cout << "Client name: " << it->second->getNickName() << std::endl;
        std::cout << "Client fd: " << it->second->getFd() << std::endl;
        std::cout << "Client channels: " << std::endl;
        std::set<std::string> channels = it->second->getJoinedChannels();
        std::set<std::string>::const_iterator it2 = channels.begin();
        std::set<std::string>::const_iterator ite2 = channels.end();
        for (; it2 != ite2; it2++) {
            std::cout << "\tChannel name: " << *it2 << std::endl;
        }
    }
}

void printMessages(std::vector<Message> messages)
{
    std::vector<Message>::const_iterator it = messages.begin();
    std::vector<Message>::const_iterator ite = messages.end();
    for (; it != ite; it++) {
        std::cout << "Message: " << it->getMessage() << std::endl;
    }
}

int main()
{
//      Server(int port, std::string password, std::string adminName, std::string adminPassword);
	Client* client = new Client(0);
    client->setNickName("nickName");
    Client* client2 = new Client(1);
    client2->setNickName("nickName2");
    Client* client3 = new Client(2);
    client3->setNickName("nickName3");
    Client* client4 = new Client(3);
    client4->setNickName("nickName4");
    Client* client5 = new Client(4);
    client5->setNickName("nickName5");
    Client* client6 = new Client(5);
    client6->setNickName("nickName6");

    Server::addClient(client);
    Server::addClient(client2);
    Server::addClient(client3);
    Server::addClient(client4);
    Server::addClient(client5);
    Server::addClient(client6);
    std::cout << "------------------Join test------------------" << std::endl;
    {
        Join join(client, "#new");
        printMessages(join.execute());
    }
    {
        Join join(client2, "#new");
        printMessages(join.execute());
    }
    {
        Join join(client3, "#new");
        printMessages(join.execute());
    }
    {
        Join join(client4, "#new");
        printMessages(join.execute());
    }
    {
        Join join(client5, "#new");
        printMessages(join.execute());
    }
    {
        Join join(client6, "#new");
        printMessages(join.execute());
    }
    std::cout << "------------------Multi Join test------------------" << std::endl;
    {
        Join join(client, "#new4,#new5,#new6,5,6,7,#new7");
        printMessages(join.execute());
    }
    printClients();
    printChannels();
    std::cout << "------------------Join again------------------" << std::endl;
    {
        Join join(client, "#new");
        printMessages(join.execute());
    }
    std::cout << "------------------PrivMsg test(to channel)------------------" << std::endl;
    {
        PrivMsg privMg(client, "#new", "hello");
        printMessages(privMg.execute());
    }
    std::cout << "------------------PrivMsg test(to client)------------------" << std::endl;
    {
        PrivMsg privMg(client, client2->getNickName(), "hello");
        printMessages(privMg.execute());
    }
    std::cout << "------------------Multi PrivMsg test------------------" << std::endl;
    {
        PrivMsg privMg(client, client2->getNickName() + ",#new,#5,#hi", "hello");
        printMessages(privMg.execute());
    }
    std::cout << "------------------PrivMsg test(no channel)------------------" << std::endl;
    {
        PrivMsg privMg(client, "#new11", "hello");
        printMessages(privMg.execute());
    }
    std::cout << "------------------Oper success------------------" << std::endl;
    {
        Oper oper(client, "admin", "admin");
        printMessages(oper.execute());
    }
    std::cout << "------------------Oper fail------------------" << std::endl;
    {
        Oper oper(client2, "admin1", "admin");
        printMessages(oper.execute());
    }
    std::cout << "------------------User test------------------" << std::endl;
    {
        User user(client, "name");
        printMessages(user.execute());
    }
    std::cout << "------------------Part test------------------" << std::endl;
    {
        Join join(client, "#Part");
        Join join2(client2, "#Part");
        std::cout << "------------------Join before Part------------------" << std::endl;
        printMessages(join.execute());
        printMessages(join2.execute());
        Part part(client, "#Part");
        printMessages(part.execute());
    }
    std::cout << "------------------Multi Part test------------------" << std::endl;
    {
        Join join(client, "#Part,#Part2,#Part3");
        Join join2(client2, "#Part");
        printMessages(join.execute());
        printMessages(join2.execute());
        Part part(client, "#Part,#Part2,#Part3,#Part4");
        printMessages(part.execute());
    }
    std::cout << "------------------Part remainder------------------" << std::endl;
    {
        Part part(client2, "#Part");
        printMessages(part.execute());
    }
    printChannels();
    std::cout << "------------------List test------------------" << std::endl;
    {
        std::cout << "------------------Join before List------------------" << std::endl;
        Join join(client, "#List");
        Join join2(client2, "#List2");
        printMessages(join.execute());
        printMessages(join2.execute());
        List list(client);
        printMessages(list.execute());
    }
    //nick test
    std::cout << "------------------Nick test------------------" << std::endl;
    {
        Nick nick(client4, "newNick");
        printMessages(nick.execute());
    }
    std::cout << "------------------Nick test(new user)------------------" << std::endl;
    {
        Client* client5 = new Client(5);
        Nick nick(client5, "newNick5");
        printMessages(nick.execute());
    }
    client = Server::findClient(0);
    std::cout << "------------------Kick test------------------" << std::endl;
    {
        Kick kick(client, "#List", client->getNickName(), "kick");
        printMessages(kick.execute());
    }
    std::cout << "------------------Quit test------------------" << std::endl;
    {
        Quit quit(client);
        printMessages(quit.execute());
    }
    printChannels();
    printClients();
    std::cout << "------------------Quit test 2------------------" << std::endl;
    {
        Quit quit(client2);
        printMessages(quit.execute());
    }
    printChannels();
    printClients();
    // system("leaks -q ircserv");
    return (0);
}