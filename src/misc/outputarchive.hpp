#ifndef _MISC_OUTPUTARCHIVE_HPP
#define _MISC_OUTPUTARCHIVE_HPP

#include <fstream>
#include "node.hpp"

class OutputArchive
{
public:
	OutputArchive(std::ofstream& outputFile);
	~OutputArchive();

	OutputArchive& operator<<(const Node& node);

private:
	std::ofstream& outputFile;
};


#endif // _MISC_OUTPUTARCHIVE_HPP