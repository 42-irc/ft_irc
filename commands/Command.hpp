#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>
# include <iostream>
# include "Message.hpp"

class Command{
	public:
		Command();
		virtual ~Command();
		virtual Message excute() = 0;
};

#endif