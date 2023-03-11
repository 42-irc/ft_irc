#include "List.hpp"

List::List(Client* client) : Command(client, "LIST") {}

List::~List() {}

/*
std::vector<Message> format
- :<server> 322 <nickname> <channel> <# of clients> :<topic>
- :<server> 323 <nickname> :End of LIST
*/
std::vector<Message> List::execute() {
	std::vector<int> targetFd;
	targetFd.push_back(_client->getFd());
	std::map<std::string, Channel*> channels = Server::getChannels();
	std::map<std::string, Channel*>::iterator it = channels.begin();
	std::map<std::string, Channel*>::iterator ite = channels.end();
	std::vector<Message> messages;
	for (; it != ite; it++) {
		messages.push_back(Message(targetFd, RPL_LIST, _client->getNickName() + " " + it->second->getName() + " " + std::to_string(it->second->getClients().size())));
	}
	messages.push_back(Message(targetFd, RPL_LISTEND, _client->getNickName()));
	return (messages);
}