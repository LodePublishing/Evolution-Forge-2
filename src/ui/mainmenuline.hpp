#ifndef _UI_MAINMENULINE_HPP
#define _UI_MAINMENULINE_HPP

#include <gui/window.hpp>
#include <gui/group.hpp>

enum eTabs
{
	HELP_TAB=28,
	SETTINGS_TAB,
//	MAP_TAB,
	DATABASE_TAB,	
	MAX_TABS
};

class MainMenuLine : public Object
{
	public:
		MainMenuLine(Object* main_parent);
		~MainMenuLine();
		void process();
		void draw() const;
		void reloadOriginalSize();
	
		void addNewGameTab();
		void removeGameTab(const unsigned int game_number);
		
		const unsigned int getGameTabCount() const;

		void reloadStrings();

		// absolute Nummer
		void activateTab(const eTabs tab_number);
		// nach Reihenfolge:
		void activateTabNumber(unsigned int tab_number);
		const eTabs getCurrentTab() const;

		const bool  markedForRemove() const;
		const bool  markedForNewGame() const;
		const bool hasTabChanged() const;
		const unsigned int getNewGameTab() const;
	private:
		Button* tab[MAX_TABS];

		void scrollLeft();
		void scrollRight();
		Button* removeCurrentTabButton;
		Button* scrollLeftButton;
		Button* scrollRightButton;

		unsigned int gameTabCount;
		unsigned int gameNumber;
		unsigned int gameNumbers[MAX_TABS];

		void adjustView();
		unsigned int viewTabs;
	
		Group* leftTabs;
		Group* rightTabs;
		eTabs oldTab;

		bool tabHasChanged;
		bool markForRemove;
		bool markForNewGame;
		unsigned int newGameTab;
};

inline const bool MainMenuLine::hasTabChanged() const {
	return(tabHasChanged);
}

inline const unsigned int MainMenuLine::getGameTabCount() const {
	return gameTabCount;
}

inline const unsigned int MainMenuLine::getNewGameTab() const {
	return(newGameTab);
}

inline const bool MainMenuLine::markedForNewGame() const {
	return(markForNewGame);
}
inline const bool MainMenuLine::markedForRemove() const {
	return(markForRemove);
}

#endif // _UI_MAINMENULINE_HPP

