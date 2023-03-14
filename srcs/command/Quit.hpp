#ifndef QUIT_HPP
# define QUIT_HPP

#include "Command.hpp"

class Quit : public Command {
	public:
		Quit(Client* client);
		~Quit();

		void execute();
};

#endif
