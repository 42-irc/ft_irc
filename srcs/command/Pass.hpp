#ifndef PASS_HPP
# define PASS_HPP

#include "Command.hpp"

class Pass : public Command {
	private:
		std::string _password;

	public:
		Pass(Client* client, const std::string& password);
		~Pass();

		void validate();
		void execute();
};

#endif
