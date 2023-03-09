# include "Quit.hpp"

Quit::Quit(Client client, std::string channel) : Command(client, "QUIT"), _channel(channel){
}

Quit::~Quit(){
}

std::vector<Message> Quit::execute(){
	Server::removeClient(_client);
	return std::vector<Message>();
}
