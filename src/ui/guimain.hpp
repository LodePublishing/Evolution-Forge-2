#ifndef _UI_MAIN_HPP
#define _UI_MAIN_HPP

#if 0

#include "game.hpp"
#include "msgwindow.hpp"
//#include "info.hpp"
#include "helpwindow.hpp"
//#include "mapwindow.hpp"
#include "datawindow.hpp"
#include "mainmenuline.hpp"
#include "setwindow.hpp"
#include "debug.hpp"
#include <gui/framerate.hpp>
//#include "message.hpp"
#include <gui/background.hpp>

#include "gamemenu.hpp"

//#include "progressbar.hpp"

#include "introwindow.hpp"
#include "intro.hpp"

#include "savebox.hpp"

class Main
{
	public:
		Main();
		~Main();

		const bool initGUI();
		const bool initCore();
		
		
		void draw() const;
		
		void process();
		void resetData();
		
		void newGeneration();
		
		const bool isAnyOptimizing() const;
		void stopAllOptimizing();
		void startLastOptimizing();

		void noticeFullscreen();

		void leftDown();
		void leftUp(const Point p);
		void rightDown();
		void rightUp(const Point p);

		void wheelUp();
		void wheelDown();

		void wheelToTop();
		void wheelToBottom();
	
		void setMouse(const Point p);

		const bool newRun();
		const bool hasBitDepthChanged() const;
		const bool hasResolutionChanged() const;
		const bool hasFullScreenChanged() const;
		const bool hasThemeChanged() const;
		const bool hasGameTypeChanged() const;

		void resetDataChange();

		void reloadOriginalSize();
		void reloadStrings();

	
		void initializeGame(const unsigned int game_number);

		const bool openMenu(const ePlayerOrder order);
		
		const bool click();
		void goBack();
		
		void poll(const eTicks etick);

	private:
		MainMenuLine* mainMenuLine;
		UI_FrameRateControl frameRateControl;
		UI_BackGround* backGround;

		void checkTab();

		IntroWindow* introWindow;
		Intro* intro;
		HelpWindow* helpWindow;
		SettingsWindow* settingsWindow;
		DataBaseWindow* dataBaseWindow;

		DebugWindow* debugWindow;
		
//		MapWindow* mapWindow;

		SaveBox* saveBox;
		Menu* languageMenu;
		
		Point maus;
		unsigned int gameCount; 
		Game* game[MAX_GAME];
//		static InfoWindow* infoWindow;
//		static MessageWindow* msgWindow;
		const bool loadGoals();
		const bool loadBuildOrders();
		const bool loadStartConditions();
//		const bool loadHarvestData();
		const bool loadMaps();

		signed int tabToGameList[MAX_TABS];
		signed int tabToSplitGameList[MAX_TABS];

		eTabs currentTab;

		unsigned int currentGame; // for openRaceMenu

		bool gameTypeHasChanged;
		
		unsigned int original_desired_cpu; // for intro
		unsigned int original_desired_framerate;
		unsigned int original_background_bitmap;
};

inline void Main::poll(const eTicks etick) {
	frameRateControl.poll(etick);
}

inline const bool Main::hasBitDepthChanged() const {
	return(settingsWindow->hasBitDepthChanged());
}

inline const bool Main::hasResolutionChanged() const {
	return(settingsWindow->hasResolutionChanged());
}

inline const bool Main::hasFullScreenChanged() const {
	return(settingsWindow->hasFullScreenChanged());
}

inline const bool Main::hasThemeChanged() const {
	return(settingsWindow->hasThemeChanged());
}

inline const bool Main::hasGameTypeChanged() const {
	return(gameTypeHasChanged);
}

#endif
																	
#endif // _UI_MAIN_HPP

