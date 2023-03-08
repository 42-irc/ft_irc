#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <string>

# include "../Message.hpp"
# include "../Client.hpp"

class Command {
	protected:
		Client _client;
		std::string _type;

	public:
		Command(Client client, std::string type);
		virtual ~Command();
		virtual Message execute() = 0;
};

#endif