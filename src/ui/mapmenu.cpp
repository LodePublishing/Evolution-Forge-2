#include "mapmenu.hpp"

#if 0


MapMenu::MapMenu(Object* map_parent, const Rect map_rect, const Size distance_bottom_right, const ePositionMode position_mode):
	Menu(map_parent, map_rect, distance_bottom_right, position_mode, true, ONE_COLOUMN_MENU, STANDARD_BUTTON_WIDTH)
{ 
	resetData();
	reloadOriginalSize();
}

MapMenu::~MapMenu()
{ }

void MapMenu::reloadOriginalSize() {
	Menu::reloadOriginalSize();
}

void MapMenu::resetData()
{
	unsigned int i=0;
	
	for(std::list<MenuEntry*>::iterator m=menuEntries.begin(); m!=menuEntries.end(); ++m)
	{
		if(i >= database.getMapCount())
		{
			(*m)->Hide();
			continue;
		}
		(*m)->Show();
		(*m)->setButtonColorsType(eButtonColorsType(UNIT_TYPE_4_BUTTON));
		(*m)->updateText(database.getMap(i)->getName());
		++i;
	}
	for(;i<database.getMapCount();++i)
	{
		MenuEntry* entry = new MenuEntry(this, Rect(), database.getMap(i)->getName());
		entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_4_BUTTON));
		menuEntries.push_back(entry);
	}
	reloadOriginalSize();
}


void MapMenu::process()
{
	Menu::process();
	if(!isShown())
		return;
}

void MapMenu::draw() const
{
	Menu::draw();
}

#endif