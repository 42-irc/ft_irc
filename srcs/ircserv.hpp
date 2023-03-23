#ifndef IRCSERV_HPP
# define IRCSERV_HPP

#include "netdb.h"

#include "Command.hpp"
#include "Server.hpp"

enum e_status {
	FAIL = -1,
	SUCCESS = 0
};

int create_server_socket(int port);
int set_server_on_kqueue(int server_socket);

int create_client_socket(int server_socket, int kq, Server* server);

Command* parse(Client* client, const std::string& str);

#endif