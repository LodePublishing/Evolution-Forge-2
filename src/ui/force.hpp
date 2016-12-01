#ifndef _UI_FORCE_HPP
#define _UI_FORCE_HPP


#if 0

#include "unitmenu.hpp"
#include "goalmenu.hpp"
//#include "racemenu.hpp"
#include "forceentry.hpp"
//#include "locationmenu.hpp"
#include "techtree.hpp"

#include <gui/radio.hpp>

#include "../core/database.hpp"

enum eMenu
{
//	RACE_MENU,
	UNIT_MENU,
	GOAL_MENU,
	SAVE_GOALS,
	
	MAX_FORCE_MENUS
};

class ForceWindow : public Window
{
	public:
		ForceWindow(Object* force_parent, const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		~ForceWindow();
		
		void processList();
		void process();

		void draw() const;
		const unsigned int getMarkedUnit() const;
		void setMarkedUnit(const unsigned int marked_unit);
		void assignAnarace(ANABUILDORDER* force_anarace);
		void reloadStrings();
		void setMode(const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		void reloadOriginalSize();
		static TechTreeWindow* techTreeWindow;

		void resetData();

		void needSaveBox();
		void saveBoxIsCanceled();
		void saveBoxIsDone(std::string& input_string);

		const bool saveGoal();
		const bool openGoalMenu();
		const bool openUnitMenu();
		const signed int getAssignedGoal() const;

	private:
		unsigned int currentGoalUnit; // which goal is currently highlighted?
		unsigned int startLine;

		
		void closeMenus();

		Radio* menuRadio;
		Button* menuButton[MAX_FORCE_MENUS];

		StaticText* nongoalsText;
		StaticText* goalsText;
//		StaticText* locationName[2][MAX_LOCATIONS];
		StaticText* legend;

		Button* goalName;

		std::list<ForceEntry*> goalForceList;
		std::list<ForceEntry*> nongoalForceList;

		unsigned int markedUnit, oldMarkedUnit;
		ANABUILDORDER* anarace;

		UnitMenu* unitMenu;
		GoalMenu* goalMenu;
//		RaceMenu* raceMenu;
//		LocationMenu* locationMenu;
		unsigned int gameNumber;
		unsigned int gameMax;
		unsigned int playerNumber;
		unsigned int playerMax;
		bool saveBox;


		void mouseHasLeft();
		
		bool goalMenuOpenedExternally;
		bool unitMenuOpenedExternally;

		bool savingGoal;
		signed int assignGoal;
};

inline const signed int ForceWindow::getAssignedGoal() const {
	return(assignGoal);
}

inline void ForceWindow::setMarkedUnit(const unsigned int marked_unit)
{
#ifdef _SCC_DEBUG
	if(marked_unit >= RACE::UNIT_TYPE_COUNT) {
		toErrorLog("DEBUG: (ForceWindow::setMarkedUnit): Value marked_unit out of range.");return;
	}
#endif
	markedUnit = marked_unit;
}
	
inline const unsigned int ForceWindow::getMarkedUnit() const
{
#ifdef _SCC_DEBUG
	if(markedUnit >= RACE::UNIT_TYPE_COUNT) {
		toErrorLog("DEBUG: (ForceWindow::getMarkedUnit): Value markedUnit out of range.");return(0);
	}
#endif
	return (markedUnit);
}

#endif

#endif // _UI_FORCE_HPP

