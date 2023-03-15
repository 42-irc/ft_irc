#include "ircserv.hpp"

int create_client_socket(int server_socket, int kq, Server* server) {
	struct sockaddr_in client_addr;
	socklen_t client_addr_size = sizeof(client_addr);
	int new_client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);

	if (new_client_socket == -1) 
		return FAIL;

	char client_host[NI_MAXHOST];

	getnameinfo((struct sockaddr*)&client_addr, client_addr_size, client_host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
	// std::cout << "New client connected: " << client_host << std::endl;
	if (fcntl(new_client_socket, F_SETFL, O_NONBLOCK) == -1) {
		close(new_client_socket);
		return FAIL;
	}

	Client* client;
    try {
        client = server->findClient(new_client_socket);
    } catch (Message& e) {
		try {
			client = new Client(new_client_socket, server);
		} catch (std::exception& e) {
			close(new_client_socket);
			return FAIL;
		}
        client->setHostName(client_host);
    }

	struct kevent client_socket_event;
	EV_SET(&client_socket_event, new_client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(kq, &client_socket_event, 1, NULL, 0, NULL) == -1) {
		client->leaveServer();
		close(new_client_socket);
		return FAIL;
	};
	return SUCCESS;
}