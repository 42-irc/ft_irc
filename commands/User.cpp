#include "User.hpp"

User::User(Client client, std::string name, std::string nickName, std::string hostName) : Command(client, "USER"), _name(name), _nickName(nickName), _hostName(hostName) {
}

User::~User() { }

Message User::execute() {
	std::vector<int> targetFd;
	targetFd.push_back(_client.getFd());
	Message message(targetFd, RPL_WELCOME, _client.getNickName(), ft::get_code_messages(RPL_WELCOME), "");
	return message;
}
