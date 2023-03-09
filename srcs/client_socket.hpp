#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include "server_socket.hpp"

void create_client_socket(int server_socket, int kq);

#endif