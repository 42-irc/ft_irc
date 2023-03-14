#include "ircserv.hpp"

void create_client_socket(int server_socket, int kq, Server* server) {
	struct sockaddr_in client_addr;
	socklen_t client_addr_size = sizeof(client_addr);
	int new_client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);

	if (new_client_socket == -1)
		err_exit("accepting client : " + std::string(strerror(errno)));

	char client_host[NI_MAXHOST];
	getnameinfo((struct sockaddr*)&client_addr, client_addr_size, client_host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
	
	std::cout << client_host << " : New client connected\n" << std::endl;

	if (fcntl(new_client_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting client socket flag : " + std::string(strerror(errno)));

    try {
        server->findClient(new_client_socket);
    } catch (Message& e) {
        Client* client = new Client(new_client_socket, server);
        client->setHostName(client_host);
    }

	struct kevent client_socket_event;
	EV_SET(&client_socket_event, new_client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	// EV_SET(&client_socket_event[1], new_client_socket, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
	kevent(kq, &client_socket_event, 2, NULL, 0, NULL);

	// printChannels(server);// 디버깅용 프린트 함수
	// printClients(server);// 디버깅용 프린트 함수
}