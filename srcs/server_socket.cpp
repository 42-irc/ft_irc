#include "server_socket.hpp"
#include "main.hpp"

int create_server_socket(int port) {
	int server_socket;
	struct sockaddr_in server_addr;

	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == -1)
		err_exit("creating server socket : " + std::string(strerror(errno)));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		err_exit("binding server socket : " + std::string(strerror(errno)));

	if (listen(server_socket, 5) == -1)
		err_exit("server socket listening : " + std::string(strerror(errno)));

	if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting server socket flag : " + std::string(strerror(errno)));

	return server_socket;
}

int set_server_on_kqueue(int server_socket) {
	int kq = kqueue();
	if (kq == -1)
		err_exit("creating kqueue : " + std::string(strerror(errno)));

	struct kevent server_socket_event;
	EV_SET(&server_socket_event, server_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &server_socket_event, 1, NULL, 0, NULL);
	
	return kq;
}
