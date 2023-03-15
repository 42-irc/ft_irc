#include "ircserv.hpp"

int main(int argc, char *argv[]) {
	int port = validate_args(argc, argv);
	int server_socket = create_server_socket(port);
	int kq = set_server_on_kqueue(server_socket);
	std::string password(argv[2]);
	Server* server;

	while (1) {
		try {
			server = new Server(port, kq, server_socket, password, "admin", "admin");
			break ;
		} catch (std::exception& e) {
			continue ;
		}
	}

	std::cout << "Start Waiting for events..." << std::endl;

	server->execute();
	delete server;

	return 0;
}