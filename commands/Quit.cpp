# include "Quit.hpp"

Quit::Quit(Client* client) : Command(client, "QUIT") {}

Quit::~Quit() {}

/*
:<nick>!<user>@<host> QUIT [<Quit message>]
*/
std::vector<Message> Quit::execute() {
	std::vector<Message> messages;
	std::set<std::string> channels = _client->getJoinedChannels();
	std::set<std::string>::iterator it = channels.begin();
	std::set<std::string>::iterator ite = channels.end();

	for (; it != ite; it++) {
		Channel* channel = Server::findChannel(_client, *it);
		messages.push_back(Message(channel->getFdsExceptClient(_client), getPrefix(), _type));
	}
	Server::removeClient(_client);
	return messages;
}

