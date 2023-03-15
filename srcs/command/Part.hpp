#ifndef PART_HPP
# define PART_HPP

#include "Command.hpp"

class Part : public Command {
	private:
		std::string _channel;
		std::string _reason;

	public:
		Part(Client* client, const std::string& channel, const std::string& reason);
		~Part();

		void execute();
};

#endif
