#include "main.hpp"
#include "parse.hpp"
#include "../commands/Command.hpp"

void err_exit(std::string error_msg) {
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	int port = validate_args(argc, argv);
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
			// 이벤트가 발생한 식별자가 서버 소켓의 fd인 경우
			if (occurred_events[i].ident == (uintptr_t)server_socket) {
				if (occurred_events[i].filter == EVFILT_READ)
					create_client_socket(server_socket, kq, server);
				else
					std::cerr << "something in server socket" << std::endl;
			}
			// 이벤트가 발생한 식별자가 클라이언트 소켓의 fd인 경우
			else {
				int event_client_socket = occurred_events[i].ident;
				// if (occurred_events[i].filter == EVFILT_READ) {
				char buffer[1024];
				memset(buffer, 0, sizeof(buffer));
				ssize_t n = recv(event_client_socket, buffer, sizeof(buffer), 0);
				if (n < 0) {
					err_exit("receiving from client socket : " + std::string(strerror(errno)));
				} else if (n == 0) {
					// 클라이언트 연결 종료
					std::cout << event_client_socket << " Client closed connection\n" << std::endl;
					close(event_client_socket);
				} else {
					// 클라이언트 메시지 수신 성공
					std::cout << "[" << event_client_socket << "] client : " << buffer << std::endl;
					std::vector<std::string> tokens = ft::split(std::string(buffer), "\r\n");
					std::vector<std::string>::const_iterator first = tokens.begin();
					std::vector<std::string>::const_iterator last = tokens.end();

					while (first != last) {
						// 클라이언트에 보낼 메시지 작성 후 전송
						try {
							Command* command = ft::parse(server->findClient(event_client_socket), *first);
							command->execute();
							delete command;
						} catch (Message &e) {
							send(event_client_socket, e.getMessage().c_str(), e.getMessage().size(), 0);
						} catch (std::exception &e) {
							send(event_client_socket, MALLOC_ERR, strlen(MALLOC_ERR),0);
						}
						first++;
					}
				}
				// }
			}
		}
	}
