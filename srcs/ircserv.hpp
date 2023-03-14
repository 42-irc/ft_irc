#ifndef IRCSERV_HPP
# define IRCSERV_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "netdb.h"

#include "utils.hpp"
#include "command/Command.hpp"
#include "server/Server.hpp"
#include "client/Client.hpp"

void err_exit(std::string error_msg);

int create_server_socket(int port);
int set_server_on_kqueue(int server_socket);

void create_client_socket(int server_socket, int kq, Server* server);

Command* parse(Client* client, const std::string& str);

#endif