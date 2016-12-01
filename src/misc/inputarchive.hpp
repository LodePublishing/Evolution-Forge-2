#ifndef _MISC_INPUTARCHIVE_HPP
#define _MISC_INPUTARCHIVE_HPP


#include "node.hpp"
#include <fstream>

class InputArchive
{
public:
	InputArchive(std::ifstream& inputFile);
	~InputArchive();

	InputArchive& operator>>(Node& node);

private:
	std::ifstream& inputFile;	

	std::string findName();
	std::string findValue();
};

#endif // _MISC_INPUTARCHIVE_HPP
