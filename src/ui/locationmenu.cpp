#include "locationmenu.hpp"

LocationMenu::LocationMenu(Object* location_parent, const BASIC_MAP* location_map, const Rect& location_rect):
	Menu(location_parent, location_rect, Size(0,0), DO_NOT_ADJUST, true, TWO_COLOUMNS_MENU, SMALL_BUTTON_WIDTH),
	locationList()
{
	assignMap(location_map);
	resetData();
}

LocationMenu::LocationMenu(Object* location_parent, const std::list<std::string>& location_list, const Rect& location_rect):
	Menu(location_parent, location_rect, Size(0,0), DO_NOT_ADJUST, true, TWO_COLOUMNS_MENU, SMALL_BUTTON_WIDTH),
	locationList(location_list)
{
	resetData();
}

LocationMenu::~LocationMenu()
{ }


void LocationMenu::resetData()
{
	std::list<std::string>::iterator i = locationList.begin();
	for(std::list<MenuEntry*>::iterator m=menuEntries.begin(); m!=menuEntries.end(); ++m)
	{
		if(i == locationList.end())
		{
			(*m)->Hide();
			continue;
		}

		(*m)->Show();
		(*m)->setButtonColorsType(eButtonColorsType(UNIT_TYPE_6_BUTTON));
		(*m)->updateText(*i);
		++i;
    	}
	for(;i!=locationList.end();++i)
	{
		MenuEntry* entry = new MenuEntry(this, Rect(), *i);
		entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_6_BUTTON));
		menuEntries.push_back(entry);
	}
	reloadOriginalSize();
}

void LocationMenu::reloadOriginalSize()
{
	Menu::reloadOriginalSize();
}

void LocationMenu::assignMap(const std::list<std::string>& location_list)
{
	locationList.clear();
	locationList = location_list;
}

void LocationMenu::assignMap(const BASIC_MAP* location_map)
{
	locationList.clear();
	for(unsigned int i = 0;i < location_map->getMaxLocations();i++)
		locationList.push_back(location_map->getLocation(i)->getName());
}

void LocationMenu::process()
{
	Menu::process();
}

void LocationMenu::draw() const
{
	Menu::draw();
}

