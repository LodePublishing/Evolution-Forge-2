#ifndef _UI_RESOLUTIONMENU_HPP
#define _UI_RESOLUTIONMENU_HPP

#include "menu.hpp"

class ResolutionMenu : public Menu
{
	public:
		ResolutionMenu(Object* resolution_menu_parent, const Rect rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~ResolutionMenu();
		void reloadOriginalSize();
		void process();
		void draw(DC* const dc) const;
};

#endif // _UI_RESOLUTIONMENU_HPP

