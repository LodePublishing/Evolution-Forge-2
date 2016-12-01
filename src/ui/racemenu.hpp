#ifndef _UI_RACEMENU_HPP
#define _UI_RACEMENU_HPP

#if 0

#include <gui/menu.hpp>

class RaceMenu : public Menu
{
	public:
		RaceMenu(Object* race_parent, const Rect race_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~RaceMenu();
		const bool addKey(unsigned int key, unsigned int mod);
		void process();
		void draw() const;
	private:
};

#endif

#endif // _UI_RACEMENU_HPP

