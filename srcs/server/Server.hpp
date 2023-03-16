#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/event.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <map>

#include "Channel.hpp"
#include "Message.hpp"
#include "utils.hpp"

class Client;
class Channel;

class Server {
	private:
		int _port;
		int _kq;
		int _serverSocket;
		std::map<std::string, Channel*> _channels;
		std::map<std::string, Client*> _clients;
		std::map<int, Client*> _clientsFd;
		std::string _password;
		std::string _adminName;
		std::string _adminPassword;
		Client* _bot;

	public:
		Server(int port, int kq, int serverSocket, const std::string& password, const std::string& adminName, const std::string& adminPassword);
		~Server();

		Client* getBot();
		int getPort();
		std::map<std::string, Channel*> getChannels();
		std::map<std::string, Client*> getClients();
		const std::string getPassword();
		const std::string getAdminName();
		const std::string getAdminPassword();

		void setPort(int port);
		void setPassword(const std::string& password);

		Channel* findChannel(Client* client, const std::string& name);
		Client* findClient(Client* client, const std::string& name);
		Client* findClient(int fd);

		void addChannel(Channel* channel);
		void addClient(Client* client);

		void removeChannel(Channel* channel);
		void removeClient(Client* client);

		void execute();
};

#endif