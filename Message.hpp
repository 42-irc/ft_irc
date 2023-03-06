#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>

class Message {
	private:
		int _code;
		std::string _prefix;
		std::string _command;
		std::string _params;

	public:
		Message(std::string str);
		~Message();
		const int getCode() const;
		const std::string getPrefix() const;
		const std::string getCommand() const;
		const std::string getParams() const;
};

#endif