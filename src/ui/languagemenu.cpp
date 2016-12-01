#include "languagemenu.hpp"

#if 0

LanguageMenu::LanguageMenu(Object* language_parent, const Rect language_rect, const Size distance_bottom_right, const ePositionMode position_mode) :
	Menu(language_parent, language_rect, distance_bottom_right, position_mode, false)
{
	for(unsigned int i=0;i<2;++i)
	{
		MenuEntry* entry = new MenuEntry(this, Rect(), (eString)(SETTING_ENGLISH_LANGUAGE_STRING+i));
		entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_5_BUTTON+i));
   		menuEntries.push_back(entry);
	}
	reloadOriginalSize();
}

void LanguageMenu::reloadOriginalSize()
{
	updateItemSizes(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH));
	Object::reloadOriginalSize();
	updateItemPositions(TWO_COLOUMN_MENU);
}


LanguageMenu::~LanguageMenu() 
{ }

void LanguageMenu::process()
{
	Menu::process();
	if(!isShown())
		return;
}
	
void LanguageMenu::draw(DC* const dc) const
{
	if(!isShown())
		return;
	Menu::draw(dc);
}	

#endif