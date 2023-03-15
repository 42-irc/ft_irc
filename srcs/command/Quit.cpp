#include "Quit.hpp"

Quit::Quit(Client* client) : Command(client, "QUIT") {}

Quit::~Quit() {}

/*
:<nick>!<user>@<host> QUIT [<Quit message>]
*/
void Quit::execute() {
	std::set<std::string> channels = _client->getJoinedChannels();
	std::set<std::string>::const_iterator it = channels.begin();
	std::set<std::string>::const_iterator ite = channels.end();

	for (; it != ite; it++) {
		Channel* channel = _client->getServer()->findChannel(_client, *it);
		Message msg(getPrefix(), _type);

		msg.addTargets(channel->getFdsExceptClient(_client));
		msg.addParam(*it);
		_messages.push_back(msg);
	}
	_client->leaveServer();
	sendMessages();
}
