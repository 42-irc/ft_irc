#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include "netdb.h"
#include "server_socket.hpp"
#include "../Client.hpp"
#include "../Server.hpp"

void create_client_socket(int server_socket, int kq);

#endif