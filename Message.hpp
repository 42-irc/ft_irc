#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

class Message {
	private:
		std::vector<int> _targets;
		int _code;
		std::string _prefix;
		std::string _command;
		std::string _params;

	public:
		Message(std::vector<int> targets, int code, std::string prefix, std::string command, std::string params = "");
		~Message();
		const int getCode() const;
		const std::string getPrefix() const;
		const std::string getCommand() const;
		const std::string getParams() const;
};

#endif