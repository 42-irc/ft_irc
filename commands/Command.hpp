#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>

#include "../Message.hpp"
#include "../Client.hpp"
#include "../srcs/utils.hpp"

class Command {
	protected:
		Client _client;
		std::string _type;

	public:
		Command(Client client, std::string type);
		virtual ~Command();
		virtual std::vector<Message>  execute() = 0;
};

#endif