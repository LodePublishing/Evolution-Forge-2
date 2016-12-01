#ifndef _GUI_STORAGES_GUIDIRECTORIES_HPP
#define _GUI_STORAGES_GUIDIRECTORIES_HPP

#include <string>

class GuiDirectories
{
public:
	static void init();
	static void initTemp(const std::string prefixDirectory); // for tests
};

#endif // _GUI_STORAGES_GUIDIRECTORIES_HPP