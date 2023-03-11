#ifndef PING_HPP
# define PING_HPP

#include "Command.hpp"
#include "../Server.hpp"

class Ping : public Command
{
	public:
		Ping(Client* client);
		~Ping();
		std::vector<Message> execute();
};

#endif