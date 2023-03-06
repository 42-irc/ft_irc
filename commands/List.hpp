#ifndef LIST_HPP
# define LIST_HPP

# include <string>
# include "Command.hpp"

class List : public Command
{
	public:
		List();
		~List();
		Message	execute();
};

#endif