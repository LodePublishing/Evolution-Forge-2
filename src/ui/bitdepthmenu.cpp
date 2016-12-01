#include "bitdepthmenu.hpp"

BitDepthMenu::BitDepthMenu(Object* bit_depth_menu_parent, const Rect rect, const Size distance_bottom_right, const ePositionMode position_mode) :
	Menu(bit_depth_menu_parent, rect, distance_bottom_right, position_mode, true)
{
	for(unsigned int i=DEPTH_8BIT;i<=DEPTH_32BIT;i++)
	{
 		MenuEntry* entry = new MenuEntry(this, Rect(), (eString)(SETTING_DEPTH_8BIT_STRING+i));
		entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_7_BUTTON));
   		menuEntries.push_back(entry);
	}
	reloadOriginalSize();
}

void BitDepthMenu::reloadOriginalSize()
{
	updateItemSizes(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH));
	Object::reloadOriginalSize();
	updateItemPositions(TWO_COLOUMN_MENU);
}
BitDepthMenu::~BitDepthMenu() 
{ }

void BitDepthMenu::process()
{
	Menu::process();
	if(!isShown())
		return;
}
	
void BitDepthMenu::draw(DC* const dc) const
{
	if(!isShown())
		return;
	Menu::draw(dc);
}	

