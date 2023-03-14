#include "ircserv.hpp"

void err_exit(std::string error_msg) {
	std::cerr << "Error : " << error_msg << std::endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	int port = ft::validate_args(argc, argv);
	int server_socket = create_server_socket(port);
	int kq = set_server_on_kqueue(server_socket);
	Server* server = new Server(port, argv[2], "admin", "admin");

	std::cout << "Start Waiting for events..." << std::endl;
	while (true) {
		struct kevent occurred_events[100];
		int occured_events_cnt = kevent(kq, NULL, 0, occurred_events, 100, NULL);

		if (occured_events_cnt == -1)
			err_exit("calling kevent : " + std::string(strerror(errno)));
		for (int i = 0; i < occured_events_cnt; ++i) {
			if (occurred_events[i].ident == (uintptr_t)server_socket) {
				if (occurred_events[i].filter == EVFILT_READ)
					create_client_socket(server_socket, kq, server);
				else
					std::cerr << "something in server socket" << std::endl;
			} else {
				int event_client_socket = occurred_events[i].ident;

				if (occurred_events[i].filter == EVFILT_READ) {
					char buffer[1024];
					memset(buffer, 0, sizeof(buffer));
					ssize_t n = recv(event_client_socket, buffer, sizeof(buffer), 0);

					if (n < 0) {
						err_exit("receiving from client socket : " + std::string(strerror(errno)));
					} else if (n == 0) {
						std::cout << event_client_socket << " Client closed connection\n" << std::endl;
						close(event_client_socket);
					} else {
						std::cout << "client[" << event_client_socket << "] : " << std::endl;
						std::cout << buffer << std::endl;
						std::vector<std::string> tokens = ft::split(std::string(buffer), "\r\n");
						std::vector<std::string>::const_iterator first = tokens.begin();
						std::vector<std::string>::const_iterator last = tokens.end();

						while (first != last) {
							try {
								Command* command = parse(server->findClient(event_client_socket), *first);
								command->execute();
								delete command;
							} catch (Message& e) {
								e.sendMessage();
							} catch (std::exception& e) {
								send(event_client_socket, MALLOC_ERR, strlen(MALLOC_ERR),0);
							}
							first++;
						}
					}
				}
			}
		}
	}
}