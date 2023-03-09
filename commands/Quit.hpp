#ifndef QUIT_HPP
# define QUIT_HPP

# include "../Server.hpp"
# include "Command.hpp"
# include <unistd.h>

class Quit : public Command {
	public:
		Quit(Client client);
		~Quit();

		std::vector<Message> execute();
};

#endif