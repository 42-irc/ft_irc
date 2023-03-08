#include "List.hpp"

List::List(User client) : Command(client, "LIST") { }

List::~List() {}

/*
message format
- :<server> 322 <nickname> <channel> <# of users> :<topic>
- :<server> 323 <nickname> :End of LIST
*/
Message List::execute() {
	std::vector<int> targetFd;
	targetFd.push_back(_client.getFd());
	std::map<std::string, Channel> channels = Server::getChannels();
	Message message(targetFd, 322, _client.getNickName(), channels.begin()->first, std::to_string(channels.begin()->second.getUsers().size()));
	return message;
}