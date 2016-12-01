#ifndef _GAMEMENU_HPP
#define _GAMEMENU_HPP

#if 0

#include <gui/menu.hpp>

class GameMenu : public Menu
{
	public:
		GameMenu(Object* game_parent, const Rect& game_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~GameMenu();
		void process();
		void draw() const;
};

#endif

#endif // _GAMEMENU_HPP

