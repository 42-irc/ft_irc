#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>

#include "Command.hpp"
#include "Message.hpp"
#include "Client.hpp"
#include "utils.hpp"

class Command {
	protected:
		Client* _client;
		std::string _type;
		std::vector<Message> _messages;
		const std::string getPrefix() const;
		void checkAuthClient();

	public:
		Command(Client* client, std::string type);
		virtual ~Command();

		void sendMessages();
		virtual void validate() = 0;
		virtual void execute() = 0;
};

#endif
