#include "srcs/utils.hpp"
// #include "Server.hpp"
// #include "commands/Join.hpp"
#include "commands/PrivMsg.hpp"
#include <iostream>

int main()
{
//		Server(int port, std::string password, std::string adminName, std::string adminPassword);
	Server server(6667, "password", "admin", "admin");
	User user("name", "nickName");
	Channel channel("#name", user);
	Server::addChannel(channel);
	Server::addUser(user);

	// Join join("new", user);
	// Message message = join.excute();
	PrivMsg privMsg(user, "#name", "hello");
	Message message = privMsg.execute();
	std::cout << message.getMessage() << std::endl;
	return (0);
}