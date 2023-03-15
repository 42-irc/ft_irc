#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <sys/socket.h>

std::vector<std::string> split(const std::string& str, char charset, unsigned long n = 0);
std::vector<std::string> split(const std::string& str, const std::string charset);

unsigned long num_of_digit(int num);
int validate_port(char* port);
void validate_password(std::string password);
int validate_args(int argc, char *argv[]);
void err_exit(std::string error_msg);

#endif