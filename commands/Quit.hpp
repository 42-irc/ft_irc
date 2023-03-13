#ifndef QUIT_HPP
# define QUIT_HPP

#include "../Server.hpp"
#include "Command.hpp"

class Quit : public Command {
	public:
		Quit(Client* client);
		~Quit();

		std::vector<Message> execute();
};

#endif
