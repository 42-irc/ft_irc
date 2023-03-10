#include "Nick.hpp"

Nick::Nick(Client client, std::string nick) : Command(client, "NICK"), _nick(nick) {}

Nick::~Nick() {}

std::vector<Message> Nick::execute() {
	std::vector<Message> messages;
	std::map<std::string, Client> clients;
	std::map<std::string, Client>::const_iterator it = clients.find(_nick);
	std::map<std::string, Client>::const_iterator end = clients.end();
	if (it != end) {
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		messages.push_back(Message(targetFd, ERR_NICKNAMEINUSE, _client.getNickName()));
	}
	else{
		Server::removeClient(_client);
		_client.setNickName(_nick);
		Server::addClient(_client);
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		messages.push_back(Message(targetFd, _client.getNickName(), _type + ": " + _nick));
	}
	return(messages);
}