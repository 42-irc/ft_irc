#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>

class Message {
	private:
		std::vector<int> _targets;
		int _code;
		std::string _prefix;
		std::string _content;

	public:
		Message();
		Message(std::vector<int> targets, int code, std::string content);
		Message(std::vector<int> targets, std::string prefix, std::string content);
		~Message();
		const std::string getMessage();
};

#endif