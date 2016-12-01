#ifndef _UI_FORCEMENU_HPP
#define _UI_FORCEMENU_HPP

#if 0

#include "menu.hpp"
#include "../core/anabuildorder.hpp"
#include "../core/database.hpp"

class ForceMenu : public Menu
{
	public:
		ForceMenu(Object* force_parent, ANABUILDORDER* force_anarace, const Rect force_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		ForceMenu(const ForceMenu& object);
		ForceMenu& operator=(const ForceMenu& object);
		~ForceMenu();
		void process();
		void draw(DC* const dc) const;
	private:
};

#endif

#endif // _UI_FORCEMENU_HPP

