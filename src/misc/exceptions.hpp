#ifndef _MISC_EXCEPTIONS_HPP
#define _MISC_EXCEPTIONS_HPP

#include <stdexcept>

class SDLException : public std::runtime_error {
public:
	SDLException(const std::string& msg = "") : std::runtime_error(msg) {}
};

class FileException : public std::runtime_error {
public:
	FileException(const std::string& msg = "") : std::runtime_error(msg) {}
};

class GUIException : public std::runtime_error {
public:
	GUIException(const std::string& msg = "") : std::runtime_error(msg) {}
};
/*

 
struct MyException : public std::exception {
	std::string s;
	MyException(std::string ss) :
		s(ss)
		{}
	const char* what() const throw() {return s.c_str();}
};

struct MyWarning : public std::exception {
	std::string s;
	MyWarning(std::string ss) :
		s(ss)
		{}
	const char* what() const throw() {return s.c_str();}
};*/

#endif // _MISC_EXCEPTIONS_HPP