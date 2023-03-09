#ifndef _SERVER_SOCKET_HPP_
#define _SERVER_SOCKET_HPP_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <vector>
#include <unistd.h>

void err_exit(std::string error_msg);
int create_server_socket();
int set_server_on_kqueue(int server_socket);

#endif