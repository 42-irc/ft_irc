#include "client_socket.hpp"

void printChannels() {
    std::cout << "------------------exist channels------------------" << std::endl;
    std::map<std::string, Channel*> channels = Server::getChannels();
    std::map<std::string, Channel*>::iterator it = channels.begin();
    std::map<std::string, Channel*>::iterator ite = channels.end();
    for (; it != ite; it++) {
        std::cout << "Channel name: " << it->second->getName() << std::endl;
        // std::cout << "Channel operator: " << it->second->getOperator()->getNickName() << std::endl;
        std::cout << "Channel clients: " << std::endl;
        std::map<std::string, Client*> clients = it->second->getClients();
        std::map<std::string, Client*>::iterator it2 = clients.begin();
        std::map<std::string, Client*>::iterator ite2 = clients.end();
        for (; it2 != ite2; it2++) {
            std::cout << "\tClient name: " << it2->second->getNickName() << std::endl;
        }
    }
    std::cout << std::endl;
}

void printClients() {
    std::cout << "------------------exist clients------------------" << std::endl;
    std::map<std::string, Client*> clients = Server::getClients();
    std::map<std::string, Client*>::iterator it = clients.begin();
    std::map<std::string, Client*>::iterator ite = clients.end();
    for (; it != ite; it++) {
        std::cout << "Client name: " << it->second->getNickName() << std::endl;
        std::cout << "Client fd: " << it->second->getFd() << std::endl;
        std::cout << "Client channels: " << std::endl;
        std::set<std::string> channels = it->second->getJoinedChannels();
        std::set<std::string>::iterator it2 = channels.begin();
        std::set<std::string>::iterator ite2 = channels.end();
        for (; it2 != ite2; it2++) {
            std::cout << "\tChannel name: " << *it2 << std::endl;
        }
    }
}

void create_client_socket(int server_socket, int kq, Server* server) {
	struct sockaddr_in client_addr;
	socklen_t client_addr_size = sizeof(client_addr);
	int new_client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
	if (new_client_socket == -1)
		err_exit("accepting client : " + std::string(strerror(errno)));

	char client_host[NI_MAXHOST];
	getnameinfo((struct sockaddr*)&client_addr, client_addr_size, client_host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
	
	std::cout << client_host << ": New client connected\n" << std::endl;

	if (fcntl(new_client_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting client socket flag : " + std::string(strerror(errno)));

    try {
        server->findClient(new_client_socket);
    } catch (Message& e) {
        Client* client = new Client(new_client_socket, server);
        client->setHostName(client_host);
    }

	struct kevent client_socket_event[2];
	EV_SET(&client_socket_event[0], new_client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	EV_SET(&client_socket_event[1], new_client_socket, EVFILT_WRITE, EV_ONESHOT, 0, 0, NULL);
	kevent(kq, &client_socket_event[0], 2, NULL, 0, NULL);

	// 임시 접속 메시지
	char message[] = "🍀 WELCOME TO IRC SERVER 🍀\n";
	send(new_client_socket, message, sizeof(message), 0);
	// printChannels();// 디버깅용 프린트 함수
	// printClients();// 디버깅용 프린트 함수
}