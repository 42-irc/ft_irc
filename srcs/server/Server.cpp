#include "Server.hpp"
#include "ircserv.hpp"
#include "Quit.hpp"
#include <sstream>
#include <string>

Server::Server(int port, int kq, int serverSocket, const std::string& password, const std::string& adminName, const std::string& adminPassword): _port(port),_kq(kq), _serverSocket(serverSocket), _password(password),_adminName(adminName), _adminPassword(adminPassword) {
	Client *bot = new Client(1, this);

	bot->setNickName("BOT🤖");
	_bot = bot;
}

Server::~Server() {
	std::map<std::string, Channel*>::const_iterator it = _channels.begin();
	std::map<std::string, Channel*>::const_iterator ite = _channels.end();

	for (; it != ite; it++)
		delete it->second;

	std::map<std::string, Client*>::const_iterator it2 = _clients.begin();
	std::map<std::string, Client*>::const_iterator ite2 = _clients.end();

	for (; it2 != ite2; it2++)
		delete it2->second;
};

Client* Server::getBot() { return _bot; }

int Server::getPort() { return _port; }

std::map<std::string, Channel*> Server::getChannels() { return _channels; }

std::map<std::string, Client*> Server::getClients() { return _clients; }

const std::string Server::getPassword() { return _password; }

const std::string Server::getAdminName() { return _adminName; }

const std::string Server::getAdminPassword() { return _adminPassword; }

void Server::setPort(int port) { _port = port; };

void Server::setPassword(const std::string& password) { _password = password; }

Channel* Server::findChannel(Client* client, const std::string& name) {
	std::map<std::string, Channel*>::const_iterator it = _channels.find(name);

	if (it != _channels.end())
		return it->second;

	Message msg(ERR_NOSUCHCHANNEL);

	msg.addTarget(client->getFd());
	msg.addParam(name);
	throw msg;
}

Client* Server::findClient(Client* client, const std::string& name) {
	std::map<std::string, Client*>::const_iterator it = _clients.find(name);

	if (it != _clients.end())
		return it->second;
	
	Message msg(ERR_NOSUCHNICK);

	msg.addTarget(client->getFd());
	msg.addParam(name);
	throw msg;
}

Client* Server::findClient(int fd) {
	std::map<int, Client*>::const_iterator it = _clientsFd.find(fd);

	if (it != _clientsFd.end())
		return it->second;

	throw Message();
}

void Server::addChannel(Channel* channel) {
	_channels.insert(std::pair<std::string, Channel*>(channel->getName(), channel));
}

void Server::addClient(Client* client) {
	_clients[client->getNickName()] = client;
	_clientsFd[client->getFd()] = client;
}

void Server::removeChannel(Channel* channel) {
	_channels.erase(channel->getName());
}

void Server::removeClient(Client* client) {
	_clients.erase(client->getNickName());
	if (_clientsFd.find(client->getFd())->second->getNickName() == client->getNickName())
		_clientsFd.erase(client->getFd());
	delete client;
}

void Server::execute() {
	while (true) {
		struct kevent events[100];
		int eventCnt = kevent(_kq, NULL, 0, events, 100, NULL);

		if (eventCnt == -1)
			continue ;
		for (int i = 0; i < eventCnt; ++i) {
			if (events[i].ident == (uintptr_t)_serverSocket) {
				if (create_client_socket(_serverSocket, _kq, this) == -1)
					continue ;
			} else {
				int clientSocket = events[i].ident;
				Client *client;
				try {
					client = findClient(clientSocket);
				} catch (Message& e) {
					close(clientSocket);
					continue ;
				}

				char receiver[1025];
				while (true) {
					memset(receiver, 0, sizeof(receiver));
					ssize_t n = recv(clientSocket, receiver, sizeof(receiver) - 1, 0);
					if (n <= 0)
						break;
					client->addToBuffer(receiver);
				}

				if (events->flags & EV_EOF) {
					try {
						Quit(client).execute();
					} catch (Message& e) {}
					close(clientSocket);
				} else {
					if (client->getBuffer().find("\r") == std::string::npos && client->getBuffer().find("\n") == std::string::npos)
						continue ;
					std::vector<std::string> tokens = split(client->getBuffer(), "\r\n");
					std::vector<std::string>::const_iterator it = tokens.begin();
					std::vector<std::string>::const_iterator ite = tokens.end();

					for (; it != ite; it++) {
						Command* command = NULL;
						try {
							command = parse(findClient(clientSocket), *it);
							command->execute();
							delete command;
						} catch (Message& e) {
							e.sendMessage();
							delete command;
						} catch (std::exception& e) {
							findClient(clientSocket)->clearBuffer();
							if (command)
								delete command;
							continue ;
						}
					}
				}
			}
		}
	}
}
