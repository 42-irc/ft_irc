#ifndef PASS_HPP
# define PASS_HPP

#include "Command.hpp"
#include "../Server.hpp"

class Pass : public Command {
	private:
		std::string _password;

	public:
		Pass(Client* client, std::string password);
		~Pass();

		std::vector<Message> execute();
};

#endif
