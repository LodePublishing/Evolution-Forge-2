#ifndef _UI_BITDEPTHMENU_HPP
#define _UI_BITDEPTHMENU_HPP

#include "menu.hpp"

class BitDepthMenu : public Menu
{
	public:
		BitDepthMenu(Object* bit_depth_menu_parent, const Rect rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~BitDepthMenu();
		void reloadOriginalSize();
		void process();
		void draw(DC* const dc) const;
};

#endif // _UI_BITDEPTHMENU_HPP

