#ifndef PONG_HPP
# define PONG_HPP

#include "Command.hpp"
#include "../Server.hpp"

class Pong : public Command {
	public:
		Pong(Client* client);
		~Pong();

		std::vector<Message> execute();
};

#endif