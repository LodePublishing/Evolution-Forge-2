#ifndef _UI_GOALMENU_HPP
#define _UI_GOALMENU_HPP

#if 0

#include <gui/menu.hpp>
#include "../core/database.hpp"

class GoalMenu : public Menu
{
	public:
		GoalMenu(Object* goal_parent, const Rect& goal_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~GoalMenu();
		
		void process();
		void draw() const;
		void resetData();
		void assignAnarace(ANABUILDORDER* goal_anarace);
		void reloadOriginalSize();
		const bool addKey(unsigned int key, unsigned int mod);
	private:
		ANABUILDORDER* anarace;
		unsigned int lastRace;
	
		GoalMenu(const GoalMenu& object);
		GoalMenu& operator=(const GoalMenu& object);
};

#endif

#endif // _UI_GOALMENU_HPP

