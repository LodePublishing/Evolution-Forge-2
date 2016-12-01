#if 0
#include "guimain.hpp"
#include "../ui/editfield.hpp"
#include "../ui/tooltip.hpp"
#include "configuration.hpp"

Main::Main(DC* const dc):
	mainWindow(NULL),
	helpWindow(NULL),
	settingsWindow(NULL),
//	mapWindow(NULL),
	maus(),
	currentTab(0)
{
// ----- INITIALIZE DATABASE -----	
	toLog(Object::theme.lookUpString(START_LOAD_BITMAPS_FONTS_STRING));
#ifdef __linux__
	Object::theme.loadGraphicData("settings/ui/default.ui","data/bitmaps/","data/fonts/",dc);
	Object::theme.loadWindowData("settings/ui/windows.ui", 0, 1);
	Object::theme.loadWindowData("settings/ui/split_windows.ui", 0, 2);
	Object::theme.loadWindowData("settings/ui/split_windows.ui", 1, 2);
#elif WIN32
	Object::theme.loadGraphicData("settings\\ui\\default.ui","data\\bitmaps\\","data\\fonts\\",dc);
	Object::theme.loadWindowData("settings\\ui\\windows.ui", 0, 1);
	Object::theme.loadWindowData("settings\\ui\\split_windows.ui", 0, 2);
	Object::theme.loadWindowData("settings\\ui\\split_windows.ui", 1, 2);
#endif
	loadHarvestData();
	loadMaps();
	loadStartConditions();
	loadGoals();

// goal beschreibt Rasse, Ziele und Modus
	
// Map in "map.txt" is now map[0]
// choose the first map we loaded (map[0])
// ----- END OF INITIALIZING DATABASE -----
	mainWindow = new MainWindow();
	
	helpWindow = new HelpWindow(mainWindow);
	settingsWindow = new SettingsWindow(mainWindow);
//	mapWindow = new MapWindow(mainWindow);
	
	Main::msgWindow = new MessageWindow(mainWindow);
	ForceWindow::techTreeWindow = new TechTreeWindow(NULL);
	ForceWindow::techTreeWindow->Hide();
	
	mainWindow->Show();
	helpWindow->Hide();
//	mapWindow->Hide();
	settingsWindow->Hide();
	msgWindow->addMessage(Object::theme.lookUpString(WELCOME_MSG1_STRING));
	msgWindow->addMessage(Object::theme.lookUpString(WELCOME_MSG2_STRING));
	msgWindow->addMessage("Visit www.clawsoftware.de - - - ");

	for(unsigned int i = MAX_TABS;i--;)
	{
		tabToGameList[i] = -1;
		tabToSplitGameList[i] = -1;
	}
	for(unsigned int i = MAX_GAME;i--;)
		game[i]=NULL;
	
	initializeGame(0);
}

void Main::reloadOriginalSize()
{
	mainWindow->reloadOriginalSize();
	ForceWindow::techTreeWindow->reloadOriginalSize();
}

void Main::initializeGame(const unsigned int tab_number)
{
	// erstes freies suchen:
	signed int game_number;
	int game_nr = 0;
	int game_max = 0;
	for(game_number = 0;game_number < MAX_GAME; ++game_number)
		if(game[game_number]==NULL)
			break;
	if(game_number == MAX_GAME)
		return;
	

	if(tabToGameList[tab_number]>=0)
	{
		if(tabToSplitGameList[tab_number]>=0)
		{
#ifdef _SCC_DEBUG
			toLog("ERROR: WTF!.");return;
#endif    
			// => schon besetzt! Fehler!
		} else
		{
			game_nr = 1;
			game_max = 2;
			game[tabToGameList[tab_number]]->setMode(0,game_max);
			tabToSplitGameList[tab_number] = game_number;
			// => als split window hernehmen!
		}
	} else
	{
	// => new tab
		game_nr = 0;
		game_max = 1;
		tabToGameList[tab_number] = game_number;
		mainWindow->addNewGameTab();
		mainWindow->forcePressTab(tab_number);
	}
	game[game_number] = new Game(mainWindow, game_nr, game_max); // TODO
	game[game_number]->assignMap(database.getMap(0));
	game[game_number]->setHarvestSpeed(1, TERRA, database.getHarvestSpeed(TERRA, 0));
	game[game_number]->setHarvestSpeed(1, PROTOSS, database.getHarvestSpeed(PROTOSS, 0));
	game[game_number]->setHarvestSpeed(1, ZERG, database.getHarvestSpeed(ZERG, 0));
	game[game_number]->setStartRace(1, TERRA); // <- ok
	game[game_number]->setStartPosition(1, 1); // <- TODO
	game[game_number]->assignGoal(1, database.getGoal(TERRA, 0)); // <- immer auf 0 setzen
	game[game_number]->assignStartCondition(1, database.getStartCondition(TERRA, 0)); // <- evtl auswaehlen... jo, aber erst spaeter einbauen TODO
	game[game_number]->initSoup();
	game[game_number]->fillGroups();
	game[game_number]->newGeneration();
	game[game_number]->Show();
	Window::setResetFlag();
}


Main::~Main()
{
	delete mainWindow;
	delete ForceWindow::techTreeWindow;
	delete msgWindow;
	delete helpWindow;
//	delete mapWindow;
	delete settingsWindow;
	for(unsigned int i=MAX_GAME;i--;)
		delete game[i];
}

void Main::resetData()
{
	for(unsigned int i=MAX_GAME;i--;)
		if(game[i])
			game[i]->resetData();
}

void Main::noticeFullscreen()
{
	settingsWindow->updateItems();
}

void Main::process()
{
	mainWindow->resetMinXY();
//	ForceWindow::techTreeWindow->Hide();
	
	Object::windowSelected = false;
	
	if((efConfiguration.isToolTips())&&(Object::tooltip))
		Object::tooltip->process();
	
	for(std::list<std::string>::iterator i = Object::msgList.begin(); i!= Object::msgList.end(); ++i)
	{
		msgWindow->addMessage(*i);
		i = Object::msgList.erase(i);
	}

	mainWindow->process();
	ForceWindow::techTreeWindow->process();
//	if(Button::getCurrentButton()==NULL) // TODO verschaerfen, boolvariable setzen wenn currentButton von !NULL auf NULL gesetzt wurde
		setMouse(maus);

	if(!Object::windowSelected)
	{
		if(Object::currentWindow)
			Object::currentWindow->setNeedRedrawNotMoved();
		Object::currentWindow=NULL;
	}
	
	if(settingsWindow->hasLanguageChanged())
	{
//		for(unsigned int i = MAX_GAME;i--;)
//			if(game[i])
//				game[i]->reloadStrings();
		mainWindow->reloadStrings();
		ForceWindow::techTreeWindow->reloadStrings();
//		settingsWindow->reloadStrings();
		msgWindow->addMessage(Object::theme.lookUpString(LANGUAGE_HAS_CHANGED_STRING));
	} else

/*	if(settingsWindow->hasResolutionChanged())
	{
                for(unsigned int i = MAX_GAME;i--;)
                        if(game[i])
                                game[i]->reloadStrings();
                mainWindow->reloadStrings();
                settingsWindow->reloadStrings();
// TODO msgWindow add Message
	}*/

	if(mainWindow->tabWasChanged())
	{
//		mainWindow->setGizmo(false);
		for(unsigned int i = MAX_GAME; i--;)
			if(game[i]!=NULL)
				game[i]->Hide();
		currentTab = mainWindow->getCurrentTab();
		switch(currentTab)
		{
			case MAP_TAB:
				msgWindow->Show();
				settingsWindow->Hide();
				helpWindow->Hide();
			break;
			case SETTINGS_TAB:
				msgWindow->Hide();
				settingsWindow->Show();
				settingsWindow->updateItems();
				helpWindow->Hide();
			break;
			case HELP_TAB:
				msgWindow->Hide();
				settingsWindow->Hide();
				helpWindow->Show();
			break;
			default:
			// => game[currentTab] wechseln, TODO mehrere auf eine Seite
				msgWindow->Show();
				settingsWindow->Hide();
				helpWindow->Hide();
				if(tabToGameList[currentTab]>=0)
				{
					game[tabToGameList[currentTab]]->Show(); //...
					if(tabToSplitGameList[currentTab]>=0)
						game[tabToSplitGameList[currentTab]]->Show();
				}
				else // new game!
				{
					initializeGame(currentTab);
				}
			break;
// TODO delete game!

			
		} // end switch getCurrentTabs
//		for(unsigned int i=MAX_GAME;i--;)
//			game[i]->setMode(currentTab, i); // TODO
	} // end tabwasChanged*/

	if((tabToGameList[currentTab]>=0)&&(game[tabToGameList[currentTab]]->isSplitGame())&&(tabToSplitGameList[currentTab]==-1))
	{
		initializeGame(currentTab);
	}
	if((tabToGameList[currentTab]>=0)&&(game[tabToGameList[currentTab]]->isRemoveGame()))
	{
		if(tabToSplitGameList[currentTab]>=0) // delete just the first game, move second game to the first
		{
			delete game[tabToGameList[currentTab]];
			game[tabToGameList[currentTab]]=NULL;
			tabToGameList[currentTab] = tabToSplitGameList[currentTab];
			tabToSplitGameList[currentTab]=-1;
			game[tabToGameList[currentTab]]->setMode(0,1);
		} else if(mainWindow->getGameTabCount()>1) // delete the whole tab if it's not the last
		{
			delete game[tabToGameList[currentTab]];
			game[tabToGameList[currentTab]]=NULL;
			for(unsigned int i = currentTab;i < mainWindow->getGameTabCount()-1;++i)
				tabToGameList[i] = tabToGameList[i+1];
			tabToGameList[mainWindow->getGameTabCount()-1]=-1;
			mainWindow->removeGameTab(currentTab);
			if(currentTab == mainWindow->getGameTabCount())
				currentTab--;
			mainWindow->forcePressTab(currentTab);
			game[tabToGameList[currentTab]]->Show(); //...
			if(tabToSplitGameList[currentTab]>=0)
				game[tabToSplitGameList[currentTab]]->Show();
//			if(mainWindow->getGameTabCount()) TODO show/hide removeButton;
		}
	} else if((tabToSplitGameList[currentTab]>=0)&&(game[tabToSplitGameList[currentTab]]->isRemoveGame())) // just the second game
	{
		delete game[tabToSplitGameList[currentTab]];
		game[tabToSplitGameList[currentTab]]=NULL;
		game[tabToGameList[currentTab]]->setMode(0,1);
		tabToSplitGameList[currentTab]=-1;
	}
	
	for(unsigned int i = MAX_GAME;i--;) // TODO
		if((game[i])&&(game[i]->checkForNeedRedraw()))
		{
			mainWindow->setNeedRedrawNotMoved();
			msgWindow->setNeedRedrawNotMoved();
			settingsWindow->setNeedRedrawNotMoved();
			helpWindow->setNeedRedrawNotMoved();
//			mapWindow->setNeedRedrawNotMoved();
			mainWindow->setNeedRedrawMoved();
			break;
		}

	
}

/*void Main::stopAllOptimizing()
{
	for(unsigned int i=MAX_GAME;i--;)
		if((game[i])&&(game[i]->isShown()))
			game[i]->setOptimizing(false);
}

void Main::startAllOptimizing()
{
	for(unsigned int i=MAX_GAME;i--;)
		if((game[i])&&(game[i]->isShown()))
			game[i]->setOptimizing(true);
}*/

const bool Main::isAnyOptimizing() const
{
//	for(unsigned int i=MAX_GAME;i--;)
//		if((game[i])&&(game[i]->isShown())&&(game[i]->isOptimizing()))
			return true;
//	return false;
}




										
//settings: log level (none, debug only, +final result, +result of each run, +snapshot every X generations, +snapshot every generation, EVERYTHING (~2MB/generation!)

void Main::OnIdle()
{
	if((!Object::editTextField))
	{
		for(unsigned int i=MAX_GAME;i--;)
			if((game[i])&&(game[i]->isShown()))
				game[i]->newGeneration();
	}
}


const bool Main::newRun()
{
//	endrun=true; TODO
/*	if(efConfiguration.isAutoSaveRuns()) TODO
	{
		ostringstream os, os2;
		os << anarace[0]->getRun() << Object::theme.lookUpString(ENDRUN_FINISHED_STRING) << "[" << formatTime2(anarace[0]->getRealTimer()) << "]";
		msgWindow->addMessage(os.str());
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
		msgWindow->addMessage(Object::theme.lookUpString(ENDRUN_SAVED_BUILDORDER_STRING));
		endrun=false;
	} else
	{
		ostringstream os;
		os << "bo_" << (*anarace[0]->getCurrentGoal())->getName() << "_" << formatTime2(anarace[0]->getRealTimer()) << "_" << anarace[0]->getRun();

		if(Object::editTextField==NULL)
			Object::editTextField = new EndRunDialog(mainWindow, os.str());
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
					msgWindow->addMessage(os.str());
					database.saveBuildOrder(Object::editTextField->getString(), anarace[0]); // TODO, evtl alle saven...
					msgWindow->addMessage(Object::theme.lookUpString(ENDRUN_SAVED_BUILDORDER_STRING));
				}
				delete Object::editTextField;
				Object::resetButton();
				Object::editTextField=NULL;
				endrun = false;
			} else
			if((Object::editTextField->isCanceled())&&(Object::editTextField->getCaller()==NULL))
			{
				delete Object::editTextField;
				Object::resetButton();
				Object::editTextField=NULL;
				endrun = false;
			}
		}
	}
	if(!endrun)
		for(unsigned int i=database.getMap(0)->getMaxPlayer();i--;)
			game[i]->resetData();
	return endrun;*/
	return false;
}	

void Main::loadHarvestData()
{
	for(unsigned int i = 0; i < MAX_RACES; ++i)
	{
		std::list<std::string> harvestFiles = database.findFiles("settings", "harvest", raceString[i]);
		for(std::list<std::string>::iterator j = harvestFiles.begin(); j!=harvestFiles.end(); ++j)
			database.loadHarvestFile(*j);
	}
//TODO flag setzen ob was geladen wurde
}


void Main::loadStartConditions()
{
	for(unsigned int i = 0; i < MAX_RACES; ++i)
	{
		std::list<std::string> startFiles = database.findFiles("settings", "start", raceString[i]);
		for(std::list<std::string>::iterator j = startFiles.begin(); j!=startFiles.end(); ++j)
			database.loadStartConditionFile(*j);
	}
//TODO flag setzen ob was geladen wurde
}




InfoWindow* Main::infoWindow = NULL;
MessageWindow* Main::msgWindow = NULL;
#endif