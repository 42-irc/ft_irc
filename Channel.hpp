#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <map>
#include <vector>
#include "Client.hpp"
#include "Message.hpp"

class Channel {
	private:
		std::map<std::string, Client> _clients;
		std::string _name;
		Client _operator;

	public:
		Channel();
		Channel(std::string name, Client oper);
		~Channel();
		const std::string getName() const;
		const std::map<std::string, Client> getClients() const;
		const std::vector<int> getFds() const;
		const Client findClient(Client client, std::string name) const;
		const Client getOperator() const;
		void addClient(Client client);
		void removeClient(Client client);
};

#endif