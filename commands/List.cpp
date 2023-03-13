#include "List.hpp"

List::List(Client* client) : Command(client, "LIST") {}

List::~List() {}

/*
std::vector<Message> format
- :<server> 322 <nickname> <channel> <# of clients> :<topic>
- :<server> 323 <nickname> :End of LIST
*/
void List::execute() {
	std::vector<int> targetFd;
	std::map<std::string, Channel*> channels = _client->getServer()->getChannels();
	std::map<std::string, Channel*>::const_iterator it = channels.begin();
	std::map<std::string, Channel*>::const_iterator ite = channels.end();
	std::vector<Message> messages;

	targetFd.push_back(_client->getFd());
	for (; it != ite; it++)
		messages.push_back(Message(targetFd, RPL_LIST, _client->getNickName() + " " + it->second->getName() + " " + std::to_string(it->second->getClients().size())));
	messages.push_back(Message(targetFd, RPL_LISTEND, _client->getNickName()));
	sendMessages(messages);
}
