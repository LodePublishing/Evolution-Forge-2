#ifndef _UI_TECHTREE_HPP
#define _UI_TECHTREE_HPP

#if 0

#include <gui/window.hpp>
#include "../core/anabuildorder.hpp"


class TechTreeWindow : public Window
{
	public:
		TechTreeWindow(Object* tree_parent);
		~TechTreeWindow();
		
		void process();
		void draw() const;
		void assignAnarace(ANABUILDORDER* techtree_anarace);
		void setCurrentGoalUnit(unsigned int current_goal_unit);
		void reloadOriginalSize();
	private:
		void processList();
		bool unitChanged;
		unsigned int currentGoalUnit; // which goal is currently highlighted?
		ANABUILDORDER* anarace;
		Size s, s2;
		GOAL_TREE tree;
		std::vector<Object*> node;
};

inline void TechTreeWindow::setCurrentGoalUnit(unsigned int current_goal_unit)
{
	if(currentGoalUnit == current_goal_unit)
		return;
	currentGoalUnit = current_goal_unit;
	unitChanged = true;
}

#endif

#endif // _UI_TECHTREE_HPP
