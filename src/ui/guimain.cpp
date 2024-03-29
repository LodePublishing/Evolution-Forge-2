#include "guimain.hpp"

#if 0

#include "files.hpp"
//#include <gui/editfield.hpp>
#include <gui/tooltip.hpp>
#include "configuration.hpp"
#include <iomanip>

const std::string intro_string = "TEST TEST TEST#";
Main::Main():
	mainMenuLine(NULL),
	backGround(NULL),
	introWindow(NULL),
	intro(NULL),
	helpWindow(NULL),
	settingsWindow(NULL),
	dataBaseWindow(NULL),
//	mapWindow(NULL),
	saveBox(NULL),
	languageMenu(NULL),
	maus(),
	gameCount(0),
	currentTab((eTabs)0),
	currentGame(0),
	gameTypeHasChanged(false)
{
	for(unsigned int i = MAX_TABS;i--;)
	{
		tabToGameList[i] = -1;
		tabToSplitGameList[i] = -1;
	}
	
	for(unsigned int i = MAX_GAME;i--;)
		game[i] = NULL;
}
#include <sstream>
const bool Main::initGUI()
{
	toInitLog(Object::theme.lookUpString(START_LOAD_UI_BITMAPS_FONTS_STRING));
#ifdef __linux__
	Object::theme.loadData("settings/ui/default.ui", "data/bitmaps/", "data/animations/", "data/fonts/", Object::dc);
	Object::sound.loadSoundDataFile("data/sounds/");
	Object::theme.loadWindowDataFile("settings/ui/windows.ui", 0, 1);
	Object::theme.loadWindowDataFile("settings/ui/split_windows.ui", 0, 2);
	Object::theme.loadWindowDataFile("settings/ui/split_windows.ui", 1, 2);
#elif WIN32
	Object::theme.loadData("settings\\ui\\default.ui", "data\\bitmaps\\", "data\\animations\\", "data\\fonts\\", Object::dc);
	Object::sound.loadSoundDataFile("data\\sounds\\");
	Object::theme.loadWindowDataFile("settings\\ui\\windows.ui", 0, 1);
	Object::theme.loadWindowDataFile("settings\\ui\\split_windows.ui", 0, 2);
	Object::theme.loadWindowDataFile("settings\\ui\\split_windows.ui", 1, 2);
#endif

// ----- INITIALIZING WINDOWS -----
	toInitLog(Object::theme.lookUpString(START_INIT_UI_STRING)); // ? TODO

	toInitLog("* " + Object::theme.lookUpString(START_INIT_MAIN_WINDOW_STRING));
	backGround = new BackGround();

	mainMenuLine = new MainMenuLine(backGround);
	
	toInitLog("* " + Object::theme.lookUpString(START_INIT_HELP_WINDOW_STRING));
	helpWindow = new HelpWindow(backGround);
	
	toInitLog("* " + Object::theme.lookUpString(START_INIT_SETTINGS_WINDOW_STRING));
	settingsWindow = new SettingsWindow(backGround);
	
	toInitLog("* " + Object::theme.lookUpString(START_INIT_DATABASE_WINDOW_STRING));
	dataBaseWindow = new DataBaseWindow(backGround);
	
//	toInitLog("* " + Object::theme.lookUpString(START_INIT_MAP_WINDOW_STRING));
//	mapWindow = new MapWindow(backGround);
	
//	toInitLog("* " + Object::theme.lookUpString(START_INIT_MSG_WINDOW_STRING));
//	Main::msgWindow = new MessageWindow(backGround);
	
	toInitLog("* " + Object::theme.lookUpString(START_INIT_INTRO_WINDOW_STRING));
	introWindow = new IntroWindow(backGround);
	intro = new Intro(backGround, backGround->getRelativeRect(), Size(), DO_NOT_ADJUST);
	
	languageMenu = new Menu(NULL, Rect(Point((backGround->getWidth() - Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH))/2, Object::max_y/2), Size(0,0)), Size(0,0), DO_NOT_ADJUST, true, ONE_COLOUMN_MENU, SMALL_BUTTON_WIDTH, 2, SETTING_ENGLISH_LANGUAGE_STRING, UNIT_TYPE_5_BUTTON);
	
	debugWindow = new DebugWindow(backGround);

	toInitLog("* " + Object::theme.lookUpString(START_INIT_TECHTREE_WINDOW_STRING));
	ForceWindow::techTreeWindow = new TechTreeWindow(backGround);
	
	toInitLog("* " + Object::theme.lookUpString(START_HIDING_WINDOWS_STRING));

	intro->Hide();
	introWindow->Hide();
	ForceWindow::techTreeWindow->Hide();
	mainMenuLine->Hide();
	helpWindow->Hide();
	settingsWindow->Hide();
	dataBaseWindow->Hide();
	debugWindow->Hide();
	languageMenu->Hide();
	
	Object::addMessage(WELCOME_MSG1_STRING);
	Object::addMessage(WELCOME_MSG2_STRING);
	Object::addMessage("Visit www.clawsoftware.de - - - ");
// ----- END INITIALIZING WINDOWS -----

	backGround->setZ(100);
	return(true); // TODO
}


const bool Main::initCore()
{
// ----- INITIALIZE DATABASE -----	
	toInitLog(Object::theme.lookUpString(START_INIT_CORE_STRING));

	database.init();

/*	if(!loadHarvestData()) {
		toErrorLog("ERROR (Main::init()): Harvest data was not successfully initialized.");
		return(false);
	}*/

	if(!loadMaps()) {
		toErrorLog("ERROR (Main::init()): Map data was not successfully initialized.");
		return(false);
	}
	
	if(!loadStartConditions()) {
		toErrorLog("ERROR (Main::init()): Start conditions were not successfully initialized.");
		return(false);
	}
	
	if(!loadGoals()) {
		toErrorLog("ERROR (Main::init()): Goals were not successfully initialized.");
		return(false);
	}
	
	if(!loadBuildOrders()) {
		toErrorLog("ERROR (Main::init()): Build orders were not successfully initialized.");
		return(false);
	}

	// TODO Ausgabestring
//	fillInfluenceList();
	
// ----- END OF INITIALIZING DATABASE -----

	return(true);
}

void Main::reloadOriginalSize()
{
	backGround->reloadOriginalSize();
	intro->setSize(Size(backGround->getWidth(), backGround->getHeight()));
}

void Main::reloadStrings()
{
	backGround->reloadStrings();
}

void Main::initializeGame(const unsigned int tab_number)
{
	toInitLog(Object::theme.lookUpString(START_PREPARE_FIRST_RUN_STRING));
	// erstes freies suchen:
	signed int game_number;
	unsigned int game_nr = 0;
	unsigned int game_max = 0;
	for(game_number = 0;game_number < MAX_GAME; ++game_number)
		if(game[game_number]==NULL)
			break;
	if(game_number == MAX_GAME)
		return;

	toInitLog("* " + Object::theme.lookUpString(START_CHOOSING_GAME_TAB_STRING));

	if(tabToGameList[tab_number]>=0)
	{
#ifdef _SCC_DEBUG
		if(tabToSplitGameList[tab_number]>=0)
		{
			toErrorLog("ERROR: WTF!.");return;
			// => schon besetzt! Fehler!
		} else
#endif    
		{
			game_nr = 0;
			game_max = 2;
			game[tabToGameList[tab_number]]->setMode(1, game_max);
			tabToSplitGameList[tab_number] = game_number;
			currentGame = 1;
			// => als split window hernehmen!
		}
	} else
	{
	// => new tab
		game_nr = 0;
		game_max = 1;
		tabToGameList[tab_number] = game_number;
		mainMenuLine->addNewGameTab();
		currentGame = 0;
//		mainMenuLine->forcePressTab(tab_number);
	}
	toInitLog("* " + Object::theme.lookUpString(START_CREATING_GAME_STRING));
	game[game_number] = new Game(backGround, database.getMap(0), game_nr, game_max); // TODO
//	game[game_number]->assignStartCondition(1, database.getStartCondition(TERRA, 0)); // <- evtl auswaehlen... jo, aber erst spaeter einbauen TODO
//	game[game_number]->setStartRace(1, TERRA); // <- ok
	game[game_number]->setStartPosition(0, 1); // <- TODO
//	game[game_number]->fillGroups();
//	game[game_number]->assignGoal(1, database.getGoal(TERRA, 0)); // <- default goal
	toInitLog("* " + Object::theme.lookUpString(START_ASSIGNING_HARVEST_SPEED_STRING));
//	game[game_number]->setHarvestSpeed(0, TERRA, database.getHarvestSpeed(TERRA, 0));
//	game[game_number]->setHarvestSpeed(0, PROTOSS, database.getHarvestSpeed(PROTOSS, 0));
//	game[game_number]->setHarvestSpeed(0, ZERG, database.getHarvestSpeed(ZERG, 0));

	toInitLog("* " + Object::theme.lookUpString(START_SHOWING_GAME_STRING));
//	game[game_number]->Show();
}


Main::~Main()
{
	toInitLog("* " + Object::theme.lookUpString(END_FREEING_WINDOWS_STRING));
	delete mainMenuLine;
	delete introWindow;
	delete intro;
	delete languageMenu;
	delete ForceWindow::techTreeWindow;
//	delete msgWindow;
	delete helpWindow;
	delete settingsWindow;
	delete dataBaseWindow;
	delete debugWindow;
//	delete mapWindow;
	delete backGround;
	delete saveBox;
	toInitLog("* " + Object::theme.lookUpString(END_FREEING_GAMES_STRING));
	for(unsigned int i=MAX_GAME;i--;)
		delete game[i];
}

void Main::resetData()
{
	for(unsigned int i=MAX_GAME;i--;)
		if(game[i])
			game[i]->resetData();
}

void Main::goBack()
{
	if(helpWindow->isShown())
		helpWindow->goBack();
}

void Main::noticeFullscreen()
{
	if(settingsWindow)
	{
		settingsWindow->updateItems();
		settingsWindow->forceFullScreenChange();
	}
}

void Main::resetDataChange()
{
	if(settingsWindow)
		settingsWindow->resetDataChange();
	gameTypeHasChanged = false;
}

void Main::process()
{
	setMouse(maus);
	Window::gotoHelpChapter = -1;
	Object::windowSelected = false;

	BoEntry::entryIsMoving = false;
	debugWindow->updateData(frameRateControl.getPercentList(), frameRateControl.getFramesPerSecond(), frameRateControl.getGenerationsPerSecond());
	Object::processAll();
	int pressed = -1;

// ------ PROCESSING ------
	if((!languageMenu->isShown()) && (uiConfiguration.isFirstStart()) && ((pressed = languageMenu->getPressedItem())<0))
	{
// ------ CAP FRAMERATE ------
		toInitLog(Object::theme.lookUpString(START_INIT_FRAMERATE_STRING)); 
		
		original_desired_cpu = uiConfiguration.getDesiredCPU();
		original_desired_framerate = uiConfiguration.getDesiredFramerate();
		original_background_bitmap = uiConfiguration.isBackgroundBitmap();
		
		uiConfiguration.setBackgroundBitmap(false);
		uiConfiguration.setDesiredCPU(99);
		uiConfiguration.setDesiredFramerate(20); // for the intro
		languageMenu->Show();
		toErrorLog("show language menu");
	} else 
	if((languageMenu->isShown()) && ((pressed>=0) || ((pressed = languageMenu->getPressedItem())>=0)))
	{
		Object::theme.setLanguage((eLanguage)(pressed+1));
		uiConfiguration.setFirstStart(false);
		languageMenu->Hide();
		toErrorLog("hide language menu");
        }
// ------ END CAP FRAMERATE
	else if((!languageMenu->isShown()) && (!intro->isShown()) && (!intro->isDone()))
	{
		SDL_ShowCursor(SDL_DISABLE);
		intro->Show();
	}

	else if((!languageMenu->isShown()) && intro->isShown() && intro->isDone())
	{
		SDL_ShowCursor(SDL_ENABLE);
		uiConfiguration.setDesiredCPU(original_desired_cpu);
		uiConfiguration.setDesiredFramerate(original_desired_framerate);
		Object::sound.playMusic(DIABLO_MUSIC);

		intro->Hide();
		introWindow->Show();
	}
	else if((!languageMenu->isShown()) && introWindow->isShown() && (introWindow->isDone()))
	{
		introWindow->Hide();
		mainMenuLine->Show();
		debugWindow->Show(efConfiguration.isShowDebug());
		uiConfiguration.setBackgroundBitmap(original_background_bitmap);
	} 
	
// ------ PROCESSING ------
	if(mainMenuLine->isShown())
		checkTab();

	if(!Object::windowSelected)
		Object::currentWindow=NULL;

	if(saveBox == NULL)
	{
		if(Window::needSaveBox)
			saveBox = new SaveBox(NULL, Window::saveBoxParameter);
	} else
	{
		bool is_canceled = saveBox->isCanceled();
		bool is_done = saveBox->isDone();
		if(is_canceled || is_done)
		{
			if(is_canceled)
				Window::saveBoxCanceled = true;
			else if(is_done)
			{
				Window::saveBoxString = saveBox->getString();
				Window::saveBoxDone = true;
			}
			delete saveBox;
			saveBox = NULL;
			Button::resetButton();
			Window::focus = NULL;
			Window::needSaveBox = false;
		}
	}
	

	
	{
		unsigned int pressedg = 0;
		if((pressedg = introWindow->getGameType())>0)
		{
			if(coreConfiguration.setGameType(pressedg))
			{
				gameTypeHasChanged = true;
				Button::resetButton();
			}
		}
	}
	
	if(settingsWindow)
	{
		if(settingsWindow->hasCompactDisplayModeChanged())
			for(unsigned int i = MAX_GAME; i--;)
				if(game[i])
					game[i]->compactDisplayModeHasChanged();
		if(settingsWindow->hasLanguageChanged())
		{
			backGround->reloadStrings();
			Object::addMessage(LANGUAGE_HAS_CHANGED_STRING);
		}

		if(settingsWindow->hasAllowWaitOrdersChanged())
		{
			for(unsigned int i = MAX_GAME; i--;)
				if(game[i])
					game[i]->setResetFlag();
			Window::setChangedFlag();
		}

	/*	if(settingsWindow->hasGameSpeedChanged())
		{
			for(unsigned int i = MAX_GAME; i--;)
				if(game[i])
					game[i]->resetPlayerTime();
		}*/ // TODO see settings.hpp
		if(Window::gotoHelpChapter>=0)
		{
			mainMenuLine->activateTab(HELP_TAB);
			helpWindow->gotoChapter(Window::gotoHelpChapter);
		}
	}

	for(std::list<std::string>::iterator i = Object::msgList.begin(); i!= Object::msgList.end(); ++i)
	{
		Object::addMessage(*i);
		i = Object::msgList.erase(i);
	}
	
	database.changeAccepted();

	frameRateControl.updateConfiguration();
}

void Main::checkTab()
{
	if(mainMenuLine->hasTabChanged())
	{
		currentTab = mainMenuLine->getCurrentTab();
		switch(currentTab)
		{
			case -1:break;
			case DATABASE_TAB:
				for(unsigned int i = MAX_GAME; i--;) 
					if(game[i]!=NULL) game[i]->Hide();
//				msgWindow->Show();
//				msgWindow->adjustRelativeRect(Rect(Point(5, Object::theme.lookUpGlobalRect(MESSAGE_WINDOW).getTop()), Object::theme.lookUpGlobalRect(MESSAGE_WINDOW).getSize()));
//				debugWindow->adjustRelativeRect(Rect(Point(msgWindow->getTargetRect().getRight()+5, Object::theme.lookUpGlobalRect(DEBUG_WINDOW).getTop()), Object::theme.lookUpGlobalRect(DEBUG_WINDOW).getSize()));
				settingsWindow->Hide();
				dataBaseWindow->Show();
//				mapWindow->Hide();
				helpWindow->Hide();
			break;
/*			case MAP_TAB:
				for(unsigned int i = MAX_GAME; i--;)
					if(game[i]!=NULL) game[i]->Hide();
				msgWindow->Show();
				settingsWindow->Hide();
				dataBaseWindow->Hide();
				mapWindow->Show();
				helpWindow->Hide();
			break;*/
			case SETTINGS_TAB:
				for(unsigned int i = MAX_GAME; i--;) 
					if(game[i]!=NULL) game[i]->Hide();
//				msgWindow->Hide();
				debugWindow->adjustRelativeRect(Rect(Point(5, Object::theme.lookUpGlobalRect(DEBUG_WINDOW).getTop()), Object::theme.lookUpGlobalRect(DEBUG_WINDOW).getSize()));
				settingsWindow->Show();
				settingsWindow->updateItems();
				dataBaseWindow->Hide();
//				mapWindow->Hide();
				helpWindow->Hide();
			break;
			case HELP_TAB:
				for(unsigned int i = MAX_GAME; i--;) 
					if(game[i]!=NULL) game[i]->Hide();
//				msgWindow->Hide();
				debugWindow->Hide();
				settingsWindow->Hide();
				dataBaseWindow->Hide();
//				mapWindow->Hide();
				helpWindow->Show();
			break;
			default:
				for(unsigned int i = MAX_GAME; i--;) 
					if(game[i]!=NULL) game[i]->Hide();
//				msgWindow->Show();
//				msgWindow->adjustRelativeRect(Object::theme.lookUpGlobalRect(MESSAGE_WINDOW));
				debugWindow->adjustRelativeRect(Object::theme.lookUpGlobalRect(DEBUG_WINDOW));
				settingsWindow->Hide();
				dataBaseWindow->Hide();
//				mapWindow->Hide();
				helpWindow->Hide();
				if(tabToGameList[currentTab]>=0)
				{
					game[tabToGameList[currentTab]]->Show(); //...
					if(tabToSplitGameList[currentTab]>=0)
						game[tabToSplitGameList[currentTab]]->Show();
				}
	//			else // new game!
	//				initializeGame(currentTab);
			break;
		} // end switch getCurrentTabs
//		msgWindow->makeFirstChild();
	}
	
	if((tabToGameList[currentTab]>=0)&&(game[tabToGameList[currentTab]]->isSplitGame())&&(tabToSplitGameList[currentTab]==-1))
	{
		initializeGame(currentTab);
//		msgWindow->makeFirstChild();
	}

	if(mainMenuLine->markedForRemove())
	{
		if(tabToSplitGameList[currentTab]>=0)
		{
			delete game[tabToSplitGameList[currentTab]];
			game[tabToSplitGameList[currentTab]] = NULL;
			tabToSplitGameList[currentTab] = -1;
		}
		if(tabToGameList[currentTab]>=0)
		{
			delete game[tabToGameList[currentTab]];
			game[tabToGameList[currentTab]] = NULL;
			tabToGameList[currentTab] = -1;
		}
		Object::currentWindow = NULL;
		Object::windowSelected = false;
		currentGame = 0;
		mainMenuLine->removeGameTab(currentTab);
	} else
	if(mainMenuLine->markedForNewGame())
	{
		initializeGame(currentTab);
	} else
	{
		if((tabToGameList[currentTab]>=0)&&(game[tabToGameList[currentTab]]->isRemoveGame()))
		{
			if(tabToSplitGameList[currentTab]>=0) // delete just the first game, move second game to the first
			{
				delete game[tabToGameList[currentTab]];
				game[tabToGameList[currentTab]]=NULL;
				tabToGameList[currentTab] = tabToSplitGameList[currentTab];
				tabToSplitGameList[currentTab]=-1;
				game[tabToGameList[currentTab]]->setMode(0,1);
				Object::currentWindow = NULL;
				Object::windowSelected = false;
				currentGame = 0;
			} else if(mainMenuLine->getGameTabCount()>1) // delete the whole tab if it's not the last
			{
				delete game[tabToGameList[currentTab]];
				game[tabToGameList[currentTab]]=NULL;
				for(unsigned int i = currentTab;i < mainMenuLine->getGameTabCount()-1;++i)
					tabToGameList[i] = tabToGameList[i+1];
				tabToGameList[mainMenuLine->getGameTabCount()-1]=-1;
				mainMenuLine->removeGameTab(currentTab);
				if(currentTab == (signed int)(mainMenuLine->getGameTabCount()))
					currentTab = (eTabs)(currentTab - 1);
				mainMenuLine->activateTab(currentTab);
				game[tabToGameList[currentTab]]->Show(); //...
				if(tabToSplitGameList[currentTab]>=0)
					game[tabToSplitGameList[currentTab]]->Show();
	//			if(mainMenuLine->getGameTabCount()) TODO show/hide removeButton;
				Object::currentWindow = NULL;
				Object::windowSelected = false;
				currentGame = 0;
			}
		} else if((tabToSplitGameList[currentTab]>=0)&&(game[tabToSplitGameList[currentTab]]->isRemoveGame())) // just the second game
		{
			delete game[tabToSplitGameList[currentTab]];
			game[tabToSplitGameList[currentTab]]=NULL;
			game[tabToGameList[currentTab]]->setMode(0,1);
			tabToSplitGameList[currentTab]=-1;
			Object::currentWindow = NULL;
			Object::windowSelected = false;
			currentGame = 0;
		}
	}
}

const bool Main::click()
{
	if(intro->isShown())
	{
		intro->setWasClicked();
		return(true);
	}
	else
		return(false);
}

void Main::stopAllOptimizing()
{
	for(unsigned int i=MAX_GAME;i--;)
		if((game[i])&&(game[i]->isShown()))
			game[i]->stopOptimizing();
}

void Main::startLastOptimizing()
{
	for(unsigned int i=MAX_GAME;i--;)
		if((game[i])&&(game[i]->isShown()))
			game[i]->startLastOptimizing();
}

const bool Main::isAnyOptimizing() const
{
	for(unsigned int i=MAX_GAME;i--;)
		if((game[i])&&(game[i]->isShown())&&(game[i]->isAnyOptimizing()))
			return(true);
	return(false);
}
										
//settings: log level (none, debug only, +final result, +result of each run, +snapshot every X generations, +snapshot every generation, EVERYTHING (~2MB/generation!)

void Main::newGeneration()
{
	frameRateControl.delay(isAnyOptimizing()); 
	poll(IDLE_TICKS);

//	evtl savebox oder so
//	if(Object::focus==NULL) // TODO, bei Force/Bowindow abfragen
	while(frameRateControl.allowCalculation())
	{
		if((!BoEntry::entryIsMoving) || (!efConfiguration.isWaitAfterChange()))
		{
			for(unsigned int i=MAX_GAME;i--;)
				if((game[i])&&(game[i]->isShown()))
					game[i]->newGeneration();
			if(dataBaseWindow->isShown())
				dataBaseWindow->newGeneration();
		} else SDL_Delay(50);
	}
	poll(GENERATION_TICKS);
}


const bool Main::newRun()
{
//	endrun=true; TODO
/*	if(efConfiguration.isAutoSaveRuns()) TODO
	{
		ostringstream os, os2;
		os << anarace[0]->getRun() << Object::theme.lookUpString(ENDRUN_FINISHED_STRING) << "[" << formatTime2(anarace[0]->getRealTimer()) << "]";
		addMessage(os.str());
		os2 << "bo_" << (*anarace[0]->getCurrentGoal())->getName() << "_" << formatTime2(anarace[0]->getRealTimer()) << "_" << anarace[0]->getRun();
//		if(EndRunDialog::getLastString()!="bo")
//			database.saveBuildOrder(EndRunDialog::getLastString(), anarace[0]); // TODO, evtl alle saven...
//		else
			database.saveBuildOrder(os2.str(), anarace[0]); // TODO, evtl alle saven...
		// TODO Name muss mitangegeben werden...
		// Dann ist auch die Frage wie die Ergebnisse gespeichert werden sollen, klar, nach Rasse sortiert 
		// Voreinstellung fuer Editfeld ist letzter benutzter Name  (oder 'leer') + fortlaufende Zahl (Reset bei neuem Namen)
		// Spaeter: ueberschreiben pruefen
		// In DateiName evtl auch Zeit einbauen
		addMessage(Object::theme.lookUpString(ENDRUN_SAVED_BUILDORDER_STRING));
		endrun=false;
	} else
	{
		ostringstream os;
		os << "bo_" << (*anarace[0]->getCurrentGoal())->getName() << "_" << formatTime2(anarace[0]->getRealTimer()) << "_" << anarace[0]->getRun();

		if(Object::editTextField==NULL)
			Object::editTextField = new EndRunDialog(mainMenuLine, os.str());
		// Dialog aufmachen: Weiterrechnen oder neubeginnen? (checkbox: nicht mehr fragen) Neuanfang kann u.U. einen neuen Weg ermoeglichen und u.U. ein besseres Ergebnis bringen... Abspeichern Checkbox, EXIT, CONTINUE, NEW ROUND...
		// you may want to use 'comparison' (not availible yet) to show all results 
		else
		{
			if((Object::editTextField->isDone())&&(Object::editTextField->getCaller()==NULL))
			{
				if(Object::editTextField->getString().length()>0)
				{
					ostringstream os;
					os << anarace[0]->getRun() << Object::theme.lookUpString(ENDRUN_FINISHED_STRING) << " [" << formatTime2(anarace[0]->getRealTimer()) << "]";
					addMessage(os.str());
					database.saveBuildOrder(Object::editTextField->getString(), anarace[0]); // TODO, evtl alle saven...
					addMessage(Object::theme.lookUpString(ENDRUN_SAVED_BUILDORDER_STRING));
				}
				delete Object::editTextField;
				Object::editTextField=NULL;
				endrun = false;
			} else
			if((Object::editTextField->isCanceled())&&(Object::editTextField->getCaller()==NULL))
			{
				delete Object::editTextField;
				Object::editTextField=NULL;
				endrun = false;
			}
		}
	}
	if(!endrun)
		for(unsigned int i=database.getMap(0)->getMaxPlayer();i--;)
			game[i]->resetData();
	return(endrun);*/
	return(false);
}	

/*const bool Main::loadHarvestData()
{
	toInitLog("* " + Object::theme.lookUpString(START_LOAD_HARVEST_STRING));
	std::list<std::string> harvestFiles = findFiles("settings", "harvest", "", "");
	for(std::list<std::string>::iterator j = harvestFiles.begin(); j!=harvestFiles.end(); ++j)
		FILES::loadHarvestFile(*j);
	return(isHarvestDataInitialized());
}*/

const bool Main::loadStartConditions()
{
	toInitLog("* " + Object::theme.lookUpString(START_LOAD_STARTCONDITIONS_STRING));
	for(unsigned int i = 0; i < GAME::MAX_RACES; ++i)
	{
		std::list<std::string> startFiles = findFiles(GAME::gameDirectory, "start", GAME::race[i].raceString, "");
		for(std::list<std::string>::iterator j = startFiles.begin(); j!=startFiles.end(); ++j)
			FILES::loadStartConditionFile(*j);
	}
	return(database.isStartConditionDataInitialized());
}

const bool Main::loadMaps()
{
	toInitLog("* " + Object::theme.lookUpString(START_LOAD_MAPS_STRING));
	std::list<std::string> mapFiles = findFiles(GAME::gameDirectory, "maps", "", "");
	for(std::list<std::string>::iterator j = mapFiles.begin(); j!=mapFiles.end(); ++j)
		FILES::loadMapFile(*j);
	return(database.isMapDataInitialized());
}

const bool Main::loadGoals()
{
	toInitLog("* " + Object::theme.lookUpString(START_LOAD_GOALS_STRING));
	for(unsigned int i = 0; i < GAME::MAX_RACES; ++i)
	{
		database.addDefaultGoal(i);
		std::list<std::string> goalFiles = findFiles(GAME::gameDirectory, "goals", GAME::race[i].raceString, "");
		for(std::list<std::string>::iterator j = goalFiles.begin(); j!=goalFiles.end(); ++j)
			if(!FILES::loadGoalFile(*j))
				toErrorLog("WARNING (Main::loadGoals()): Goal file " + *j + " could not be loaded => file is ignored.");
	}
	return(database.isGoalDataInitialized());
}

const bool Main::loadBuildOrders()
{
	toInitLog("* " + Object::theme.lookUpString(START_LOAD_BUILD_ORDERS_STRING));
	for(unsigned int i = 0; i < GAME::MAX_RACES; ++i)
	{
//		database.addDefaultBuildOrder(i); :/ TODO
		std::list<std::string> boFiles = findFiles(GAME::gameDirectory, "bos", GAME::race[i].raceString, "");
		for(std::list<std::string>::iterator j = boFiles.begin(); j!=boFiles.end(); ++j)
			FILES::loadBuildOrderFile(*j);
	}
	return(database.isBuildOrderDataInitialized());
}


const bool Main::openMenu(const ePlayerOrder order)
{
#if 0
	// links?
	if(currentGame==0)
	{
		if(tabToGameList[currentTab]<0)
			return(false);
		if(!game[tabToGameList[currentTab]]->openMenu(order))
		{
			if((tabToSplitGameList[currentTab]>=0)&&(game[tabToSplitGameList[currentTab]]->openMenu(order)))
			{				
				currentGame = 1;
				return(true);
			}
			else return(false);
		} else return(true);
	} // oder rechts?
	else if(currentGame==1)
	{
		if((tabToSplitGameList[currentTab]==-1)||(!game[tabToSplitGameList[currentTab]]->openMenu(order)))
		{
			if((tabToGameList[currentTab]) && (game[tabToGameList[currentTab]]->openMenu(order)))
			{
				currentGame = 0;
				return(true);
			} else return(false);
		} 
		return(false);
	}
#endif 
	return(false);
}
// ------ END EVENTS ------

//InfoWindow* Main::infoWindow = NULL;
//MessageWindow* Main::msgWindow = NULL;

#endif