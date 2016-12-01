#ifndef _MAIN_STORAGES_MAINDIRECTORIES_HPP
#define _MAIN_STORAGES_MAINDIRECTORIES_HPP

#include <string>

class MainDirectories
{
public:
	static void init();
	static void initTemp(const std::string prefixDirectory); // for tests
};

#endif // _MAIN_STORAGES_MAINDIRECTORIES_HPP