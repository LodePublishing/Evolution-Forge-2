#ifndef _UI_BOMENU_HPP
#define _UI_BOMENU_HPP

#if 0

#include <gui/menu.hpp>
#include "../core/database.hpp"

class BoMenu : public Menu
{
	public:
		BoMenu(Object* bo_parent, const Rect bo_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~BoMenu();
		void resetData();
		void assignAnarace(ANABUILDORDER* bo_anarace);
		void reloadOriginalSize();
		const unsigned int getNumber() const;
		const bool addKey(unsigned int key, unsigned int mod);
	private:
		unsigned int number;
		ANABUILDORDER* anarace;
		unsigned int lastRace;
		GOAL_ENTRY* lastGoal;
		BoMenu(const BoMenu& object);
		BoMenu& operator=(const BoMenu& object);
};

inline const unsigned int BoMenu::getNumber() const {
	return(number);
}

#endif

#endif // _UI_BOMENU_HPP

