#ifndef JOIN_HPP
# define JOIN_HPP

# include <string>
# include <iostream>
# include "Command.hpp"
# include "User.hpp"

class Join : public Command {
	private:
		std::string _channelName;
		User _user;

	public:
		Join(std::string channelName, User user);
		~Join();
		Message excute();
};

#endif