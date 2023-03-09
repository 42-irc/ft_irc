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
		int _port;
		static std::map<std::string, Channel> _channels;
		static std::map<std::string, Client> _clients;
		std::string _password;
		std::string _adminName;
		std::string _adminPassword;

	public:
		Server(int port, std::string password, std::string adminName, std::string adminPassword);
		~Server();
		int getPort() const;
		static const std::map<std::string, Channel> getChannels();
		static const Channel findChannel(Client client, std::string name);
		static const std::map<std::string, Client> getClients();
		static const Client findClient(Client client, std::string name);
		const std::string getPassword() const;
		const std::string getAdminName() const;
		const std::string getAdminPassword() const;
		static void addChannel(Channel channel);
		static void removeChannel(Channel channel);
		static void addClient(Client client);
		static void removeClient(Client client);
		static void addClientToChannel(Client client, Channel channel);
		static void removeClientFromChannel(Client client, Channel channel);
};

#endif