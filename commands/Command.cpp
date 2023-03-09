#include "Command.hpp"

Command::Command(Client client, std::string type): _client(client), _type(type) {}

Command::~Command() {}

std::vector<Message> Command::execute() { return std::vector<Message>(); }