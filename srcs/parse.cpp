#include "parse.hpp"

namespace ft
{

	Command* parse(Client* client, std::string str) {
		std::string commands[11] = { "JOIN", "KICK", "LIST", "NICK", "OPER", "PART", "PASS" , "PRIVMSG", "QUIT", "USER", "PING"};
		std::vector<std::string> params;

		std::size_t idx =  str.find_first_of(" ");
		std::string command = idx == std::string::npos ? str : str.substr(0, idx);
		if (str.length()) {
			for (unsigned int i = 0; i < 11; i++) {
				if (command == commands[i]) {
					switch (i) {
						case 0:
							params = ft::split(str, ' ', 2);
							return new Join(client, params[1]);
						case 1:
							params = ft::split(str, ' ', 4);
							return new Kick(client, params[1], params[2], params[3]);
						case 2:
							params = ft::split(str, ' ', 2);
							return new List(client);
						case 3:
							params = ft::split(str, ' ', 2);
							return new Nick(client, params[1]);
						case 4:
							params = ft::split(str, ' ', 3);
							return new Oper(client, params[1], params[2]);
						case 5:
							params = ft::split(str, ' ', 2);
							return new Part(client, params[1]);
						case 6:
							params = ft::split(str, ' ', 2);
							return new Pass(client, params[1]);
						case 7:
							params = ft::split(str, ' ', 3);
							return new PrivMsg(client, params[1], params[2]);
						case 8:
							params = ft::split(str, ' ', 2);
							return new Quit(client);
						case 9:
							params = ft::split(str, ' ', 4);
							// if (params[2] != "0" || params[3] != "*") throw Message(); // 461
							return new User(client, params[1]);
						case 10:
							params = ft::split(str, ' ', 2);
							return new Ping(client);
					}
				} else
					continue;
			}
		}
		std::vector<int> targets;
		targets.push_back(client->getFd());
		throw Message(targets, ERR_UNKNOWNCOMMAND, command); // 421
	};

}
