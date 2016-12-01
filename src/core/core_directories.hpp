#ifndef _CORE_STORAGES_COREDIRECTORIES_HPP
#define _CORE_STORAGES_COREDIRECTORIES_HPP

#include <string>

class CoreDirectories
{
public:
	static void init();
	static void initTemp(const std::string prefixDirectory); // for tests
};

#endif // _CORE_STORAGES_COREDIRECTORIES_HPP