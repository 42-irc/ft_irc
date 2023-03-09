#ifndef QUIT_HPP
# define QUIT_HPP

# include "../Server.hpp"
# include "Command.hpp"

class Quit : public Command {
	private:
		std::string _channel;

	public:
		Quit(Client client, std::string channel);
		~Quit();

		std::vector<Message> execute();
};

#endif