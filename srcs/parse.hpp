#ifndef PARSE_HPP
# define PARSE_HPP

#include "utils.hpp"
#include "../Message.hpp"
#include "../Client.hpp"
#include "../commands/Command.hpp"
#include "../commands/Join.hpp"
#include "../commands/Kick.hpp"
#include "../commands/List.hpp"
#include "../commands/Nick.hpp"
#include "../commands/Oper.hpp"
#include "../commands/Part.hpp"
#include "../commands/PrivMsg.hpp"
#include "../commands/Quit.hpp"
#include "../commands/User.hpp"

namespace ft
{

	Command* parse(Client client, std::string str);

}
#endif