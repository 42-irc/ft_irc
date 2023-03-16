#include "ircserv.hpp"
#include "command/Join.hpp"
#include "command/Kick.hpp"
#include "command/List.hpp"
#include "command/Nick.hpp"
#include "command/Oper.hpp"
#include "command/Part.hpp"
#include "command/Pass.hpp"
#include "command/PrivMsg.hpp"
#include "command/Quit.hpp"
#include "command/User.hpp"
#include "command/Ping.hpp"

Command* parse(Client* client, const std::string& str) {
	std::string commands[11] = { "JOIN", "KICK", "LIST", "NICK", "OPER", "PART", "PASS" , "PRIVMSG", "QUIT", "USER", "PING"};
	std::vector<std::string> params;

	std::size_t idx =  str.find_first_of(" ");
	std::string command = idx == std::string::npos ? str : str.substr(0, idx);
	if (str.length()) {
		for (unsigned int i = 0; i < 11; i++) {
			if (command == commands[i]) {
				switch (i) {
					case 0:
						params = split(str, ' ', 3);
						return new Join(client, params[1]);
					case 1:
						params = split(str, ' ', 4);
						return new Kick(client, params[1], params[2], params[3]);
					case 2:
						return new List(client);
					case 3:
						params = split(str, ' ', 2);
						return new Nick(client, params[1]);
					case 4:
						params = split(str, ' ', 3);
						return new Oper(client, params[1], params[2]);
					case 5:
						params = split(str, ' ', 3);
						return new Part(client, params[1], params[2]);
					case 6:
						params = split(str, ' ', 2);
						return new Pass(client, params[1]);
					case 7:
						params = split(str, ' ', 3);
						return new PrivMsg(client, params[1], params[2]);
					case 8:
						return new Quit(client);
					case 9:
						params = split(str, ' ', 3);
						return new User(client, params[1]);
					case 10:
						return new Ping(client);
				}
			}
		}
	}
	Message msg(ERR_UNKNOWNCOMMAND);
	msg.addParam(command);
	msg.addTarget(client->getFd());
	throw msg;
};
