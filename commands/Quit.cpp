# include "Quit.hpp"

Quit::Quit(Client client, std::string channel) : Command(client, "QUIT"), _channel(channel){
}

Quit::~Quit(){
}

Message Quit::execute(){
	Server::removeClient(_client);
	return Message();
}
