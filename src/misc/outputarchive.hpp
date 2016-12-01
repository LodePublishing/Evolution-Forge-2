#ifndef _MISC_OUTPUTARCHIVE_HPP
#define _MISC_OUTPUTARCHIVE_HPP

#include <fstream>
#include "xmlnode.hpp"

class OutputArchive
{
public:
	OutputArchive(std::ofstream& outputFile);
	~OutputArchive();

	OutputArchive& operator<<(const XmlNode& node);

private:
	std::ofstream& outputFile;
};


#endif // _MISC_OUTPUTARCHIVE_HPP