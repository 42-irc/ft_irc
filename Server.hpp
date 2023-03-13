#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>
#include <vector>

#include "Channel.hpp"
#include "Message.hpp"
#include "srcs/utils.hpp"

class Client;
class Channel;

class Server {
	private:
		int _port;
		std::map<std::string, Channel*> _channels;
		std::map<std::string, Client*> _clients;
		std::map<int, Client*> _clientsFd;
		std::string _password;
		std::string _adminName;
		std::string _adminPassword;

	public:
		Server(int port, std::string password, std::string adminName, std::string adminPassword);
		~Server();
		int getPort();
		std::map<std::string, Channel*> getChannels();
		std::map<std::string, Client*> getClients();
		const std::string getPassword();
		const std::string getAdminName();
		const std::string getAdminPassword();

		void setPort(int port);
		void setPassword(std::string password);

		Channel* findChannel(Client* client, std::string name);
		Client* findClient(Client* client, std::string name);
		Client* findClient(int fd);

		void addChannel(Channel* channel);
		void addClient(Client* client);

		void removeChannel(Channel* channel);
		void removeClient(Client* client);
};

#endif