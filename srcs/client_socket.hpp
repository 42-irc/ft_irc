#ifndef _CLIENT_SOCKET_HPP_
#define _CLIENT_SOCKET_HPP_

#include "server_socket.hpp"

void create_client_socket(int server_socket, int kq);

#endif