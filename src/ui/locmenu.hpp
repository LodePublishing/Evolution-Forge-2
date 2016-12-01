#ifndef _UI_LOCATIONMENU_HPP
#define _UI_LOCATIONMENU_HPP

#if 0

#include "menu.hpp"
#include "../core/anabuildorder.hpp"

class LocationMenu : public Menu
{
	public:
		LocationMenu(Object* location_parent, ANABUILDORDER* location_anarace, Rect location_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		LocationMenu(const LocationMenu& object);
		LocationMenu& operator=(const LocationMenu& object);
		~LocationMenu();
		void process();
		void draw(DC* const dc) const;
		void resetData();
		void assignAnarace(ANABUILDORDER* location_anarace);
	private:
		ANABUILDORDER* anarace;
};

#endif

#endif // _UI_LOCATIONMENU_HPP

