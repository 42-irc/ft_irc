#ifndef PART_HPP
# define PART_HPP

# include "Command.hpp"
# include "../Server.hpp"

class Part : public Command {
	private:
		std::string _channel;

	public:
		Part(Client client, std::string channel);
		~Part();
		std::vector<Message> execute();
};

#endif