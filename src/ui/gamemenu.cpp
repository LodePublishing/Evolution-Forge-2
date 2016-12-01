#include "gamemenu.hpp"

GameMenu::GameMenu(Object* game_parent, const Rect& game_rect, const Size distance_bottom_right, const ePositionMode position_mode) :
	Menu(game_parent, game_rect, distance_bottom_right, position_mode, true, TWO_COLOUMNS_MENU, MAX_BUTTON_WIDTH_TYPES)
//	Menu(game_parent, game_rect, distance_bottom_right, position_mode, true, ONE_COLOUMN_MENU, SMALL_BUTTON_WIDTH, 2, SETTING_ENGLISH_LANGUAGE_STRING, UNIT_TYPE_5_BUTTON)
{
	for(unsigned int i=0; i<GAME::MAX_GAME_TYPES; ++i)
	{
		MenuEntry* entry = new MenuEntry(this, Rect(), (eButtonColorsType)(STARCRAFT_BUTTON+i));
		menuEntries.push_back(entry);
	}
	updateItemPositions();
	open(); //?
}

GameMenu::~GameMenu() 
{ }

void GameMenu::process()
{
	Menu::process();
}
	
void GameMenu::draw() const
{
	Menu::draw();
}	

