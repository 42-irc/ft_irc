#ifndef VALIDATE_ARGS_HPP
#define VALIDATE_ARGS_HPP

#include <string>

unsigned long num_of_digit(int num);
int validate_port(char *port);
void validate_password(std::string password);
int validate_args(int argc, char *argv[]);

#endif