#ifndef LIST_HPP
# define LIST_HPP

# include "Command.hpp"
# include "Server.hpp"

class List : public Command
{
	public:
		List(User client);
		~List();
		Message	execute();
};

#endif