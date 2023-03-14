# include "Quit.hpp"

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

		_messages.push_back(Message(channel->getFdsExceptClient(_client), getPrefix(), _type));
	}
	_client->leaveServer();
	sendMessages();
}
