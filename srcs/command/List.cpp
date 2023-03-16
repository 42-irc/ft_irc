#include "List.hpp"

List::List(Client* client) : Command(client, "LIST") {}

List::~List() {}

void List::validate() {
	checkAuthClient();
}

/*
std::vector<Message> format
- :<server> 322 <nickname> <channel> <# of clients> :<topic>
- :<server> 323 <nickname> :End of LIST
*/
void List::execute() {
	validate();
	std::map<std::string, Channel*> channels = _client->getServer()->getChannels();
	std::map<std::string, Channel*>::const_iterator it = channels.begin();
	std::map<std::string, Channel*>::const_iterator ite = channels.end();

	for (; it != ite; it++) {
		Message msg(RPL_LIST);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		msg.addParam(it->second->getName());
		msg.addParam(std::to_string(it->second->getClients().size()));

		_messages.push_back(msg);
	}
	Message msg(RPL_LISTEND);

	msg.addTarget(_client->getFd());
	msg.addParam(_client->getNickName());
	_messages.push_back(msg);
	sendMessages();
}
