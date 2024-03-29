#include "resolutionmenu.hpp"

#if 0


ResolutionMenu::ResolutionMenu(Object* resolution_menu_parent, const Rect rect, const Size distance_bottom_right, const ePositionMode position_mode) :
	Menu(resolution_menu_parent, rect, distance_bottom_right, position_mode, true)
{
	for(unsigned int i=1;i<MAX_RESOLUTIONS;i++)
	{
 		MenuEntry* entry = new MenuEntry(this, Rect(), (eString)(SETTING_RESOLUTION_ZERO_STRING+i));
		entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_6_BUTTON));
   		menuEntries.push_back(entry);
	}
	reloadOriginalSize();
}

void ResolutionMenu::reloadOriginalSize()
{
	updateItemSizes(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH));
	Object::reloadOriginalSize();
	updateItemPositions(TWO_COLOUMN_MENU);
}

ResolutionMenu::~ResolutionMenu() 
{ }

void ResolutionMenu::process()
{
	Menu::process();
	if(!isShown())
		return;
}
	
void ResolutionMenu::draw(DC* const dc) const
{
	if(!isShown())
		return;
	Menu::draw(dc);
}	

#endif