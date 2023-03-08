#ifndef PART_HPP
# define PART_HPP

# include "Command.hpp"
# include <vector>

class Part : public Command
{
	private:
		std::vector<std::string> _channelNames;
		Client _client;

	public:
		Part(std::vector<std::string> channelNames, Client client);
		~Part();
		Message	execute();
};

#endif