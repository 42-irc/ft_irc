#ifndef USER_HPP
# define USER_HPP

#include "Command.hpp"

class User : public Command {
	private:
		std::string _userName;

	public:
		User(Client* client, const std::string& userName);
		~User();

		void validate();
		void execute();
};

#endif
