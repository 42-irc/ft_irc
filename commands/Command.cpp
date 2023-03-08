#include "Command.hpp"

Command::Command(Client client, std::string type): _client(client), _type(type) {}

Command::~Command() {}

Message Command::excute() { return Message(); }