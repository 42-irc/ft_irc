# include "Quit.hpp"

Quit::Quit(Client client) : Command(client, "QUIT") {
}

Quit::~Quit(){
}

Message Quit::execute(){
	Server::removeClient(_client);//remove client from server
	return Message();
}

