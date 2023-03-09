#include "client_socket.hpp"

void create_client_socket(int server_socket, int kq) {
	struct sockaddr_in client_addr;
	int new_client_socket = accept(server_socket, (struct sockaddr *)&client_addr, NULL);
	if (new_client_socket == -1)
		err_exit("accepting client : " + std::string(strerror(errno)));

	std::cout << new_client_socket << ": New client connected\n" << std::endl;

	if (fcntl(new_client_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting client socket flag : " + std::string(strerror(errno)));

	Client client;

	std::cout << client_addr.sin_addr.s_addr << std::endl;

	struct kevent client_socket_event[2];
	EV_SET(&client_socket_event[0], new_client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	EV_SET(&client_socket_event[1], new_client_socket, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
	kevent(kq, &client_socket_event[0], 2, NULL, 0, NULL);
}