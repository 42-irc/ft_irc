#ifndef NOTICE_HPP
# define NOTICE_HPP

#include "Command.hpp"

class Notice : public Command {
	private:
		std::string _target;
		std::string _msg;

	public:
		Notice(Client* client, const std::string& target, const std::string& msg);
		~Notice();

		void validate();
		void execute();
};

#endif