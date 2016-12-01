#ifndef _MISC_LOADSAVE_HPP
#define _MISC_LOADSAVE_HPP

#include <string>
#include "node.hpp"

class LoadSave
{
public:
	static void saveToXML(const Node& node, const std::string& dataFileName, const std::string& dataFileIdentifier);
	static Node loadFromXML(const std::string& dataFileName, const std::string& dataFileIdentifier);

protected:
	virtual ~LoadSave() {}
};

#endif // _MISC_LOADSAVE_HPP