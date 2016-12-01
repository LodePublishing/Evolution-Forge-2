#ifndef _UI_MAPMENU_HPP
#define _UI_MAPMENU_HPP

#include <gui/menu.hpp>
#include "../core/database.hpp"

class MapMenu : public Menu
{
	public:
		MapMenu(Object* map_parent, const Rect map_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~MapMenu();
		void process();
		void draw() const;
		void resetData();
		void reloadOriginalSize();
	private:
		MapMenu(const MapMenu& object);
		MapMenu& operator=(const MapMenu& object);
};

#endif // _UI_MAPMENU_HPP

