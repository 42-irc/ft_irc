#include "List.hpp"

List::List(Client* client) : Command(client, "LIST") {}

List::~List() {}

const std::string List::getMsg(Channel* channel) const {
	return _client->getNickName() + " " + channel->getName() + " " + std::to_string(channel->getClients().size());
}

/*
std::vector<Message> format
- :<server> 322 <nickname> <channel> <# of clients> :<topic>
- :<server> 323 <nickname> :End of LIST
*/
void List::execute() {
	std::vector<int> targetFds;
	std::map<std::string, Channel*> channels = _client->getServer()->getChannels();
	std::map<std::string, Channel*>::const_iterator it = channels.begin();
	std::map<std::string, Channel*>::const_iterator ite = channels.end();

	targetFds.push_back(_client->getFd());
	for (; it != ite; it++)
		_messages.push_back(Message(targetFds, RPL_LIST, getMsg(it->second)));
	_messages.push_back(Message(targetFds, RPL_LISTEND, _client->getNickName()));
	sendMessages();
}
