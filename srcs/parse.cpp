#include "parse.hpp"

namespace ft
{

	Command* parse(Client client, std::string str) {
		std::string commands[9] = { "JOIN ", "KICK ", "LIST ", "NICK ", "OPER ", "PART ", "PRIVMSG ", "QUIT", "USER" };
		std::vector<std::string> params;

		std::size_t idx =  str.find_first_of(" ");
		std::string command = idx == std::string::npos ? str : str.substr(0, idx);

		if (str.length()) {
			for (unsigned int i = 0; i < sizeof(commands); i++) {
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
							// return new Nick(client, params[1]);
						case 4:
							params = ft::split(str, ' ', 3);
							return new Oper(client, params[1], params[2]);
						case 5:
							params = ft::split(str, ' ', 2);
							return new Part(client, params[1]);
						case 6:
							params = ft::split(str, ' ', 3);
							return new PrivMsg(client, params[1], params[2]);
						case 7:
							params = ft::split(str, ' ', 2);
							return new Quit(client);
						case 8:
							params = ft::split(str, ' ', 4);
							if (params[2] != "0" || params[3] != "*") throw Message(); // 461
							return new User(client, params[1]);
					}
				}
			}
		}
		throw Message(); // 421
	};

}
