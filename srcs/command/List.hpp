#ifndef LIST_HPP
# define LIST_HPP

#include "Command.hpp"

class List : public Command {
	public:
		List(Client* client);
		~List();
		const std::string getMsg(Channel* channel) const;

		void execute();
};

#endif
