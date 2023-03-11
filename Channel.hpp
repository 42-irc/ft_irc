#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <map>
#include <vector>

#include "Client.hpp"
#include "Message.hpp"
#include "srcs/utils.hpp"

class Client;

class Channel {
	private:
		std::map<std::string, Client*> _clients;
		std::string _name;
		Client *_operator;

	public:
		Channel();
		Channel(std::string name, Client *oper);
		~Channel();
		const std::string getName() const;
		std::map<std::string, Client*> getClients() const;
		const std::vector<int> getFds() const;
		const std::vector<int> getFds(Client* client) const;
		Client* findClient(Client* client, std::string name) const;
		bool checkClientExist(std::string name) const;
		Client* getOperator() const;
		void addClient(Client* client);
		void removeClient(Client* client);
};

#endif