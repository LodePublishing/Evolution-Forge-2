#ifndef _BUILD_STORAGES_BUILDDIRECTORIES_HPP
#define _BUILD_STORAGES_BUILDDIRECTORIES_HPP

#include <string>

class BuildDirectories
{
public:
	static void init();
	static void initTemp(const std::string prefixDirectory); // for tests
};

#endif // _BUILD_STORAGES_BUILDDIRECTORIES_HPP