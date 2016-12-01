#ifndef _UI_THEMEMENU_HPP
#define _UI_THEMEMENU_HPP

#if 0

#include "menu.hpp"

class ThemeMenu : public Menu
{
    public:
        ThemeMenu(Object* thememenu_parent, Rect rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~ThemeMenu();
        void process();
        void draw(DC* const dc) const;
};

#endif

#endif // _UI_THEMEMENU_HPP

