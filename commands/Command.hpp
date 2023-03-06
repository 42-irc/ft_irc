#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <iostream>
# include "Message.hpp"
# include "User.hpp"

class Command{
	protected:
		User _client;

	public:
		Command();
		virtual ~Command();
		virtual Message excute() = 0;
};

#endif