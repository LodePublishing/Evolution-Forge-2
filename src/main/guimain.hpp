#if 0
#ifndef _GMAIN_HPP
#define _GMAIN_HPP

const float GVERSION=0.51;

#include "game.hpp"
#include "msgwindow.hpp"
#include "info.hpp"
#include "helpwindow.hpp"
//#include "mapwindow.hpp"
#include "mainwindow.hpp"
#include "setwindow.hpp"

#include "progressbar.hpp"

#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "endrundialog.hpp"
//#include "mapwindow.hpp"

class Main
{
	public:
		Main(DC* const dc);
		~Main();

		void process();
		void OnIdle();
		void resetData();
		
		
		const bool isAnyOptimizing() const;
		void stopAllOptimizing();
		void startAllOptimizing();

		void noticeFullscreen();

		const bool newRun();
		const bool hasBitDepthChanged() const;
		const bool hasResolutionChanged() const;
		const bool hasFullScreenChanged() const;

		void reloadOriginalSize();
	
	private:
		void initializeGame(const unsigned int game_number);
		MainWindow* mainWindow;
		HelpWindow* helpWindow;
		SettingsWindow* settingsWindow;
//		MapWindow* mapWindow;
		Point maus;
		unsigned int gameCount; 
		Game* game[MAX_GAME];
		static InfoWindow* infoWindow;
		static MessageWindow* msgWindow;
//		StatisticsWindow* statisticsWindow;
		void loadGoals();
		void loadStartConditions();
		void loadHarvestData();
		void loadMaps();

		signed int tabToGameList[MAX_TABS];
		signed int tabToSplitGameList[MAX_TABS];

		unsigned int currentTab;
};

inline const bool Main::hasBitDepthChanged() const {
	return settingsWindow->hasBitDepthChanged();
}

inline const bool Main::hasResolutionChanged() const {
	return settingsWindow->hasResolutionChanged();
}

inline const bool Main::hasFullScreenChanged() const {
	return settingsWindow->hasFullScreenChanged();
}
																			
#endif

#endif