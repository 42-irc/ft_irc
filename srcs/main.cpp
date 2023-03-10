#include "main.hpp"
#include "parse.hpp"
#include "../commands/Command.hpp"

void err_exit(std::string error_msg) {
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	int port = validate_args(argc, argv);
	// Server server(port, argv[2], "admin", "adminpwd");
	Server::setPort(port);
	Server::setPassword(std::string(argv[2]));
	int server_socket = create_server_socket(port);
	int kq = set_server_on_kqueue(server_socket);

	while (true) {
		std::cout << "Waiting for events..." << std::endl;

		struct kevent occurred_events[100];
		int occured_events_cnt = kevent(kq, NULL, 0, occurred_events, 100, NULL);
		if (occured_events_cnt == -1)
			err_exit("calling kevent : " + std::string(strerror(errno)));

		std::cout << occured_events_cnt << " events occur!" << std::endl;

		for (int i = 0; i < occured_events_cnt; ++i) {
			// 이벤트가 발생한 식별자가 서버 소켓의 fd인 경우
			if (occurred_events[i].ident == (uintptr_t)server_socket) {
				if (occurred_events[i].filter == EVFILT_READ)
					create_client_socket(server_socket, kq);
				else
					std::cerr << "something in server socket" << std::endl;
			}
			// 이벤트가 발생한 식별자가 클라이언트 소켓의 fd인 경우
			else {
				// READ 이벤트 발생
				int event_client_socket = occurred_events[i].ident;
				if (occurred_events[i].filter == EVFILT_READ) {
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
						// 클라이언트에 보낼 메시지 작성 후 전송
						// char *reply = buffer;
						Command* cmd = ft::parse(Server::findClient(event_client_socket), std::string(buffer));
						std::vector<Message> msg = cmd->execute();
						std::vector<Message>::iterator first = msg.begin();
						std::vector<Message>::iterator last = msg.end();

						while (first != last) {
							std::vector<int> targets = first->getTargets();
							std::vector<int>::iterator firstTarget = targets.begin();
							std::vector<int>::iterator lastTarget = targets.end();

							while (firstTarget != lastTarget) {
								send(*firstTarget, first->getMessage().c_str(), first->getMessage().size(), 0);
								firstTarget++;
							}
							first++;
						}
					}
				// WRITE 이벤트 발생
				} else if (occurred_events[i].filter == EVFILT_WRITE) {
					// 해당 클라이언트에 보낼 메시지가 있는 경우만 전송하게 조건 추가
					if (false) {
						char message[] = "";
						ssize_t n = send(event_client_socket, message, sizeof(message), 0);
						if (n < 0) {
							err_exit("sending to client socket : " + std::string(strerror(errno)));
						} else {
							// 메시지 전송 성공 -> 해당 클라이언트에 보낼 메시지 삭제 해주기
						}
					}
				}
			}
		}
	}
}