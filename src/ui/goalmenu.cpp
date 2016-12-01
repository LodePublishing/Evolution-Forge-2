#include "goalmenu.hpp"
#include "configuration.hpp"
#include <sstream>

GoalMenu::GoalMenu(Object* goal_parent, const Rect& goal_rect, const Size distance_bottom_right, const ePositionMode position_mode):
	Menu(goal_parent, goal_rect, distance_bottom_right, position_mode, true, TWO_COLOUMNS_MENU, STANDARD_BUTTON_WIDTH),
	anarace(NULL),
	lastRace(0)
{ }

GoalMenu::~GoalMenu()
{ }

void GoalMenu::process()
{
	Menu::process();
}

void GoalMenu::draw() const
{
	Menu::draw();
}

void GoalMenu::assignAnarace(ANABUILDORDER* goal_anarace)
{
	bool race_has_changed = false;
	if((anarace==NULL)||(lastRace != goal_anarace->getRace()))
		race_has_changed = true;
	anarace = goal_anarace;
	if(race_has_changed)
	{
		lastRace = anarace->getRace();
		resetData();
	}
}

void GoalMenu::reloadOriginalSize()
{
	Menu::reloadOriginalSize();
}

const bool GoalMenu::addKey(unsigned int key, unsigned int mod)
{
	if((key < SDLK_0) || (key > SDLK_9) || (!isOpen()))
		return(false);
	unsigned int i = key - SDLK_0;
	forcePressItem(i);
	return(true);
}

void GoalMenu::resetData()
{
	if(!anarace)
		return;
	std::list<MenuEntry*>::iterator m=menuEntries.begin(); 
	while(m!=menuEntries.end())
	{
		delete(*m);
		m = menuEntries.erase(m);
	}
	
	for(unsigned int i=0; i<database.getGoalCount(lastRace);++i)
	{
		const GOAL_ENTRY* my_goal = database.getGoal(lastRace, i);
		std::ostringstream os;
		os << my_goal->getName();
		if(Object::focus == this)
			os << " [" << i << "]";
		MenuEntry* entry = new MenuEntry(this, Rect(), os.str());
		if(i==0)
			entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_2_BUTTON));
		else
			entry->setButtonColorsType(eButtonColorsType(UNIT_TYPE_1_BUTTON));

		os.str("");
		for(std::list<GOAL>::const_iterator j = my_goal->goalList.begin();j!=my_goal->goalList.end();++j)
		{
			os << j->getCount() << "x $" << GAME::lookUpUnitString(lastRace, j->getUnit()) << "$";
			if(j->getTime()>0)
				os << " [" << formatTime(j->getTime(), efConfiguration.getGameSpeed()) << "]"; 
			os << "#";
		}
		entry->updateToolTip(os.str());
		menuEntries.push_back(entry);
	}
	
	reloadOriginalSize();
}



