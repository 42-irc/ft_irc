#include "main.hpp"
#include "parse.hpp"
#include "../commands/Command.hpp"

/* 디버깅용 프린트 함수 */
void printMessages(std::vector<Message> messages) {
    std::vector<Message>::const_iterator it = messages.begin();
    std::vector<Message>::const_iterator ite = messages.end();
	if (it == ite)
		return;
	std::vector<int> targets = it->getTargets();
	std::vector<int>::const_iterator firstTarget = targets.begin();
	std::vector<int>::const_iterator lastTarget = targets.end();
	std::cout << "--- Messages ---" << std::endl;
	for (; firstTarget != lastTarget; firstTarget++) {
		std::cout << "\tTarget : " << *firstTarget << std::endl;
	}
    for (; it != ite; it++) {
        std::cout << "Message - " << it->getMessage() << std::endl;
    }
	std::cout << "----------------" << std::endl;
}

void err_exit(std::string error_msg) {
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	int port = validate_args(argc, argv);
	int server_socket = create_server_socket(port);
	int kq = set_server_on_kqueue(server_socket);
	Server* server = new Server(port, argv[2], "admin", "admin");

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
					create_client_socket(server_socket, kq, server);
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
						std::vector<std::string> tokens = ft::split(std::string(buffer), "\r\n");
						std::vector<std::string>::const_iterator first = tokens.begin();
						std::vector<std::string>::const_iterator last = tokens.end();

						while (first != last) {
							// 클라이언트에 보낼 메시지 작성 후 전송
							try {
								Command* command = ft::parse(server->findClient(event_client_socket), *first);
								std::vector<Message> messages = command->execute();
								delete command;
								std::vector<Message>::const_iterator first = messages.begin();
								std::vector<Message>::const_iterator last = messages.end();

								while (first != last) {
									std::vector<int> targets = first->getTargets();
									std::vector<int>::const_iterator firstTarget = targets.begin();
									std::vector<int>::const_iterator lastTarget = targets.end();

									while (firstTarget != lastTarget) {
										send(*firstTarget, first->getMessage().c_str(), first->getMessage().size(), 0);
										firstTarget++;
									}
									first++;
								}
								// printMessages(messages);// 디버깅용 프린트 함수
							} catch (Message &e) {
								send(event_client_socket, e.getMessage().c_str(), e.getMessage().size(), 0);
							} catch (std::exception &e) {
								send(event_client_socket, MALLOC_ERR, strlen(MALLOC_ERR),0);
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