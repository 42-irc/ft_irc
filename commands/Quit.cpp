# include "Quit.hpp"

Quit::Quit(Client client) : Command(client, "QUIT") {}

Quit::~Quit() {}

std::vector<Message> Quit::execute() {
	Server::removeClient(_client);
	
	return std::vector<Message>();
}

