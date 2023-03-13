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
		Client* _operator;

	public:
		Channel();
		Channel(const std::string& name, Client* oper);
		~Channel();

		const Client* getOperator() const;
		const std::string getName() const;
		const std::vector<int> getFds() const;
		const std::vector<int> getFdsExceptClient(Client* client) const;
		const std::map<std::string, Client*> getClients() const;

		Client* findClient(Client* client, const std::string& name) const;
		void addClient(Client* client);
		void removeClient(Client* client);
		bool checkClientExist(const std::string& name) const;
};

#endif