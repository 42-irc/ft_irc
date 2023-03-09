#include "List.hpp"

List::List(Client client) : Command(client, "LIST") {}

List::~List() {}

/*
message format
- :<server> 322 <nickname> <channel> <# of clients> :<topic>
- :<server> 323 <nickname> :End of LIST
*/
Message List::execute() {
	std::vector<int> targetFd;
	targetFd.push_back(_client.getFd());
	std::map<std::string, Channel> channels = Server::getChannels();
	std::map<std::string, Channel>::iterator it = channels.begin();
	std::map<std::string, Channel>::iterator ite = channels.end();
	for (; it != ite; it++) {
		Message message(targetFd, RPL_LIST, it->second.getName());
		return message;
	}
}