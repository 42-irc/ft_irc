#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <string>

# include "../Message.hpp"
# include "../User.hpp"

class Command {
	protected:
		User _client;
		std::string _type;

	public:
		Command(User client, std::string type);
		virtual ~Command();
		virtual Message excute() = 0;
};

#endif