#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <iostream>

class User
{
	private:
		std::string	_name;
		std::string	_nickName;
		bool		_isAdmin;
		int			_fd;

	public:
		User(std::string name, std::string nickName);
		~User();
		const std::string	getName() const;
		const std::string	getNickName() const;
		bool		getIsAdmin() const;
		void		setName(std::string name);
		void		setNickName(std::string nickName);
		void		setIsAdmin(bool isAdmin);
};

#endif