#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <map>
# include <vector>
# include "Channel.hpp"
# include "Message.hpp"
# include "srcs/utils.hpp"

class Server{
	private:
		static int _port;
		static std::map<std::string, Channel> _channels;
		static std::map<std::string, Client> _clients;
		static std::map<int, Client> _clientsFd;
		static std::string _password;
		static std::string _adminName;
		static std::string _adminPassword;

	public:
		Server();
		~Server();
		static int getPort();
		static const std::map<std::string, Channel> getChannels();
		static const Channel findChannel(Client client, std::string name);
		static const std::map<std::string, Client> getClients();
		static const Client findClient(Client client, std::string name);
		static const Client findClient(int fd);
		static const std::string getPassword();
		static const std::string getAdminName();
		static const std::string getAdminPassword();
		static void setPort(int port);
		static void setPassword(std::string password);
		static void addChannel(Channel channel);
		static void removeChannel(Channel channel);
		static void addClient(Client client);
		static void removeClient(Client client);
		static void addClientToChannel(Client client, Channel channel);
		static void removeClientFromChannel(Client client, Channel channel);
};

#endif