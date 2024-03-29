#include "force.hpp"

#if 0

#include "savebox.hpp"
#include <sstream>

ForceWindow::ForceWindow(Object* force_parent, const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max) :
	Window(force_parent, FORCE_WINDOW_TITLE_STRING, theme.lookUpPlayerRect(FORCE_WINDOW, game_number, game_max, player_number, player_max), theme.lookUpPlayerMaxHeight(FORCE_WINDOW, game_number, game_max, player_number, player_max), NOT_SCROLLED),
	currentGoalUnit(0),
	startLine(0),
	menuRadio(new Radio(this, Rect(getRelativeClientRectPosition() + Size(5,5), Size()), Size(), HORIZONTAL_GROUP)),
	nongoalsText(new StaticText(this, NON_GOALS_STRING, Rect(), Size(), FORCE_TEXT_COLOR, SMALL_BOLD_FONT, DO_NOT_ADJUST)),
	goalsText(new StaticText(this, GOALS_STRING, Rect(), Size(), FORCE_TEXT_COLOR, SMALL_BOLD_FONT, DO_NOT_ADJUST)),
	legend(new StaticText(this, TIME_LEGEND_STRING, Rect(Point(200, 0), Size()), Size(), FORCE_TEXT_COLOR, SMALL_FONT, DO_NOT_ADJUST)), // TODO
	goalName(new Button(this, Rect(), Size(), TEXT_BUTTON, NULL_BITMAP, STATIC_BUTTON_MODE, CHOOSE_GOAL_NAME_STRING, DO_NOT_ADJUST, SMALL_SHADOW_BOLD_FONT, AUTO_SIZE)),
	goalForceList(),
	nongoalForceList(),
	markedUnit(0),
	oldMarkedUnit(0),
	anarace(NULL),
	
	unitMenu(new UnitMenu(this, Rect(5,0,0,0), Size(0,0), DO_NOT_ADJUST)),
	goalMenu(new GoalMenu(this, Rect(5,0,0,0), Size(0,0), DO_NOT_ADJUST)),
//	locationMenu(new LocationMenu(this, anarace, getRelativeClientRect())),
	gameNumber(game_number),
	gameMax(game_max),
	playerNumber(player_number),
	playerMax(player_max),
	saveBox(false),
	goalMenuOpenedExternally(false),
	unitMenuOpenedExternally(false),
	savingGoal(false),
	assignGoal(-1)
{	
	menuButton[UNIT_MENU] = new Button(menuRadio, Rect(Point(), Size(21,20)), Size(), MENU_BUTTON, ADD_BITMAP, STATIC_BUTTON_MODE, NULL_STRING, DO_NOT_ADJUST);
	menuButton[GOAL_MENU] = new Button(menuRadio, Rect(Point(), Size(21,20)), Size(), MENU_BUTTON, LOAD_BITMAP, STATIC_BUTTON_MODE, NULL_STRING, DO_NOT_ADJUST);
	menuButton[SAVE_GOALS] = new Button(menuRadio, Rect(Point(), Size(21,20)), Size(), MENU_BUTTON, SAVE_BITMAP, STATIC_BUTTON_MODE, NULL_STRING, DO_NOT_ADJUST),
	
	menuButton[UNIT_MENU]->updateToolTip(ADD_GOALS_TOOLTIP_STRING);
	menuButton[GOAL_MENU]->updateToolTip(CHOOSE_GOALS_TOOLTIP_STRING);
	menuButton[SAVE_GOALS]->updateToolTip(SAVE_GOAL_TOOLTIP_STRING);

	legend->Hide();

//	for(unsigned int i = 0; i<MAX_FORCE_MENUS; ++i)	
	menuRadio->addButton(menuButton[UNIT_MENU], UNIT_MENU);
	menuRadio->addButton(menuButton[GOAL_MENU], GOAL_MENU);
	menuRadio->addButton(menuButton[SAVE_GOALS], SAVE_GOALS);
/*	for (unsigned int j = 0; j < 2; ++j)	
		for (unsigned int loc = 0; loc < (*anarace->getMap())->getMaxLocations(); ++loc)
		{
			locationName[j][loc] = new StaticText(this, (*anarace->getMap())->getLocation(loc)->getName(), Rect(getRelativeClientRectPosition()+Point(0,20), getClientRectSize()), FORCE_TEXT_COLOR, SMALL_BOLD_FONT);
			locationName[j][loc]->Hide();
		}*/
	addHelpButton(DESCRIPTION_UNIT_LIST_WINDOW_CHAPTER);
	reloadOriginalSize();
}

ForceWindow::~ForceWindow()
{
	for(std::list<ForceEntry*>::iterator i = nongoalForceList.begin(); i!= nongoalForceList.end(); ++i)
		delete (*i);
	for(std::list<ForceEntry*>::iterator i = goalForceList.begin(); i!= goalForceList.end(); ++i)
		delete (*i);
	
	delete nongoalsText;
	delete goalsText;
	delete legend;
	delete goalName;

	for(unsigned int i=MAX_FORCE_MENUS;i--;)
		delete menuButton[i];
//	for(int j = 0; j < 2; ++j)
//		for (unsigned int loc = 0; loc < (*anarace->getMap())->getMaxLocations(); ++loc)
//			delete locationName[j][loc];
	
	delete unitMenu;
	delete goalMenu;
	
	delete menuRadio;
//	delete locationMenu;
}

void ForceWindow::setMode(const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max)
{
	if((game_number == gameNumber) && (game_max == gameMax) && (player_number == playerNumber) && (player_max == playerMax))
		return;
	gameNumber = game_number;
	gameMax = game_max;
	playerNumber = player_number;
	playerMax = player_max;
}


void ForceWindow::reloadOriginalSize()
{
	setOriginalRect(Object::theme.lookUpPlayerRect(FORCE_WINDOW, gameNumber, gameMax, playerNumber, playerMax));
	setMaxHeight(Object::theme.lookUpPlayerMaxHeight(FORCE_WINDOW, gameNumber, gameMax, playerNumber, playerMax));
	
	Window::reloadOriginalSize();

	unitMenu->setOriginalPosition(Point(5, menuRadio->getRelativeLowerBound()));
	goalMenu->setOriginalPosition(Point(5, menuRadio->getRelativeLowerBound()));
}

void ForceWindow::assignAnarace(ANABUILDORDER* force_anarace)
{
	anarace = force_anarace;
	unitMenu->assignAnarace(anarace);
	goalMenu->assignAnarace(anarace);
//	locationMenu->assignMap(anarace->getMap());
// resetData?
}

void ForceWindow::resetData()
{
	for(std::list<ForceEntry*>::iterator i = nongoalForceList.begin(); i!= nongoalForceList.end(); ++i)
		delete (*i);
	for(std::list<ForceEntry*>::iterator i = goalForceList.begin(); i!= goalForceList.end(); ++i)
		delete (*i);
	nongoalForceList.clear();
	goalForceList.clear();
	goalMenu->resetData();
//	locationMenu->assignMap(anarace->getMap());
//	locationMenu->resetData();
	processList();
}

void ForceWindow::mouseHasLeft()
{
	if(!goalMenuOpenedExternally)
	{
		if(menuButton[GOAL_MENU]->isCurrentlyActivated())
		{
			menuButton[GOAL_MENU]->forceUnpress();
			goalMenu->close();
		}
	}
	if(!unitMenuOpenedExternally)
	{
		if(menuButton[UNIT_MENU]->isCurrentlyActivated())
		{
			menuButton[UNIT_MENU]->forceUnpress();
			unitMenu->close();
		}
	}
	ForceEntry::mouseHasLeftWindow();
}

void ForceWindow::closeMenus()
{
	unitMenu->close();
	goalMenu->close();
//	locationMenu->close();
}

void ForceWindow::process()
{
	if(!isShown())
		return;
	ForceEntry::changed = NO_MESSAGE;

	bool line_has_changed = false;
	
	signed int oldStartLine = -1;
	if(unitMenu->getHeight()/2 > oldStartLine)
		oldStartLine = unitMenu->getHeight()/2;
	if(goalMenu->getHeight() > oldStartLine)
		oldStartLine = goalMenu->getHeight();

	Window::process();
	
	oldMarkedUnit = markedUnit;
	markedUnit = 0;

	if(ForceEntry::changed)
	{
		if(ForceEntry::forceEntryIsGoal)
		{
			if((ForceEntry::changed == NUMBER_HAS_CHANGED) || ((ForceEntry::changed==GOAL_TIME_HAS_CHANGED)&&(ForceEntry::forceEntryCount<0)))
			{
				// check whether this one is the only goal of this sort if only the goal time has changed:
				if((ForceEntry::changed == GOAL_TIME_HAS_CHANGED) && (anarace->getGoal()->hasSimilarGoal(ForceEntry::forceEntryUnit, ForceEntry::forceEntryLocation)))
				{
					// => just remove time
					ForceEntry::currentForceEntry->setTime(0);
					setChangedFlag();
				}
				else if((ForceEntry::changed == GOAL_ALWAYS_BUILD_CHANGED) || (ForceEntry::changed == GOAL_BUILD_MUCH_CHANGED))
				{
					// TODO: andere 'similar' goals evtl entfernen ?
					setChangedFlag();
				}
				else 
				{
					const std::list<GOAL> error_list = anarace->getGoal()->tryToAddGoal(ForceEntry::forceEntryUnit, ForceEntry::forceEntryTime, ForceEntry::forceEntryLocation, ForceEntry::forceEntryCount);

					if(error_list.size()>0)
					{
						if(ForceEntry::changed == GOAL_TIME_HAS_CHANGED)
						{
							// => just remove time
							ForceEntry::currentForceEntry->setTime(0);
							setChangedFlag();
						} else
						for(std::list<GOAL>::const_iterator blink = error_list.begin(); blink != error_list.end(); ++blink)
						{
							Object::sound.playSound(ERROR_SOUND, (getAbsolutePosition() + getSize()/2).x);
							for(std::list<ForceEntry*>::iterator f = goalForceList.begin(); f != goalForceList.end(); ++f)
								if(((*f)->getUnit() == blink->getUnit())&&((*f)->getTime() == blink->getTime()))//&&((*f)->getLocation() == blink->getLocation()))
								{
									(*f)->resetGradient();
									break;
								}
							for(std::list<ForceEntry*>::iterator f = nongoalForceList.begin(); f != nongoalForceList.end(); ++f)
								if((*f)->getUnit() == blink->getUnit())
								{
									(*f)->resetGradient();
									break;
								}
						}
					}
					else
					{
						if(ForceEntry::forceEntryCount >0)
							Object::msgList.push_back(Object::theme.lookUpFormattedString(ADDED_ONE_GOAL_STRING, GAME::lookUpUnitString(anarace->getRace(), ForceEntry::forceEntryUnit)));
						else if(ForceEntry::forceEntryCount <0)
							Object::msgList.push_back(Object::theme.lookUpFormattedString(REMOVED_ONE_GOAL_STRING, GAME::lookUpUnitString(anarace->getRace(), ForceEntry::forceEntryUnit)));
						setChangedFlag();
					}
				} // end of changed == GOAL_TIME_HAS_CHANGED && similar_goal
			} else 
			if(ForceEntry::changed == GOAL_TIME_HAS_CHANGED)
				setChangedFlag();
			
		} else if((!ForceEntry::forceEntryIsGoal)&&(ForceEntry::changed == NUMBER_HAS_CHANGED))
		{
			anarace->getGoal()->tryToAddGoal(ForceEntry::forceEntryUnit, ForceEntry::forceEntryTime, ForceEntry::forceEntryLocation, ForceEntry::forceEntryCount);
			Object::msgList.push_back(Object::theme.lookUpFormattedString(MOVED_NON_GOAL_STRING, GAME::lookUpUnitString(anarace->getRace(), ForceEntry::forceEntryUnit)));
			Button::resetButton();
			setChangedFlag();
		} 
	}
	
	if(ForceEntry::doCompleteSound)
	{
		ForceEntry::doCompleteSound = false;
		Object::sound.playSound(COMPLETE_SOUND, (getAbsolutePosition() + getSize()/2).x);
	}

// TODO rechtsklick -> entfernen, auch im unitmenu!

// ------ TRANSLATE THE CHOSEN MENU ITEM
	currentGoalUnit = unitMenu->getMarkedItem()+1;
//	if((!unitMenu->secondLevel())&&(currentGoalUnit==2))
//		currentGoalUnit = GAS_SCV; TODO


// ------ CHECK FOR PRESSED UNIT ITEM
	int pressed;
	if((pressed = unitMenu->getPressedItem())>=0)
	{
		const std::list<GOAL> error_list = anarace->getGoal()->tryToAddGoal(pressed, 0, 0, 1);
		if(error_list.size()>0)
		{
			for(std::list<GOAL>::const_iterator blink = error_list.begin(); blink != error_list.end(); ++blink)
			{
				Object::sound.playSound(ERROR_SOUND, (getAbsolutePosition() + getSize()/2).x);
				for(std::list<ForceEntry*>::iterator f = goalForceList.begin(); f!=goalForceList.end(); ++f)
					if(((*f)->getUnit() == blink->getUnit())&&((*f)->getTime() == blink->getTime()))//&&((*f)->getLocation() == blink->getLocation()))
					{
						(*f)->resetGradient();
						break;
					}
				for(std::list<ForceEntry*>::iterator f = nongoalForceList.begin(); f!=nongoalForceList.end(); ++f)
					if((*f)->getUnit() == blink->getUnit())
					{
						(*f)->resetGradient();
						break;
					}
			}
		} else
		{
			Object::msgList.push_back(Object::theme.lookUpFormattedString(ADDED_GOAL_STRING, GAME::lookUpUnitString(anarace->getRace(), pressed)));
			setChangedFlag();
		}
	}

	if(assignGoal != -1)
		goalName->updateText(anarace->getGoal()->getName());
	assignGoal = -1;
	if((assignGoal = goalMenu->getPressedItem())>=0)
	{
		setChangedFlag();
		menuRadio->forceUnpressAll();
		menuButton[GOAL_MENU]->forceUnpress();
	}
	
// ------ OPEN/CLOSE MENUES

	switch(menuRadio->getMarked())
	{
		case -1:break;
		case UNIT_MENU:
		{
			unitMenu->open();
			if(!unitMenu->isOpen())
			{
				menuRadio->forceUnpressAll();
				closeMenus();
				unitMenuOpenedExternally = false;
			} else 
			{
				menuButton[UNIT_MENU]->forcePress();
				closeMenus();
				unitMenu->open();
			}
		}break;
			
		case GOAL_MENU:
		{
			goalMenu->open();
			if(!goalMenu->isOpen()) 
			{
				menuRadio->forceUnpressAll();
				closeMenus();
				goalMenuOpenedExternally = false;
			} else 
			{
				menuButton[GOAL_MENU]->forcePress();
				closeMenus();
				goalMenu->open();
			}
		}
		break;
// ------ CREATE EDITBOX FOR SAVING BUILD ORDER
		case SAVE_GOALS:
		{
			savingGoal = true;
			needSaveBox();
		}
		break;			
		default:break;
	} // end of menuRadio has changed

	if(goalName->isLeftClicked())
	{
		savingGoal = false;
		needSaveBox();
	}
	
	if(saveBox)
	{
		if(Window::saveBoxCanceled)
		{
			saveBoxIsCanceled();
			saveBox = false;
			Window::saveBoxCanceled = false;
		}
		else if(Window::saveBoxDone)
		{
			saveBoxIsDone(Window::saveBoxString);
			Window::saveBoxString = "";
			saveBox = false;
			Window::saveBoxDone = false;
		}
	}
		
// ------ CLOSE MENUES IF MOUSE HAS LEFT FORCE WINDOW	
	if(!isMouseInside()) 
		mouseHasLeft();

/*	if(assignGoal>=0)
	{
		anarace->assignStartGoal(database.getGoal(anarace->getRace(), assignGoal));
		Object::msgList.push_back(Object::theme.lookUpFormattedString(SET_NEW_GOAL_LIST_STRING, anarace->getGoal()->getName()));
		std::list<ForceEntry*>::iterator a = goalForceList.begin();
		while(a!=goalForceList.end())
		{
			delete(*a);
			a = goalForceList.erase(a);
		}
		a = nongoalForceList.begin();
		while(a!=nongoalForceList.end())
		{
			delete(*a);
			a = nongoalForceList.erase(a);
		}
		setChangedFlag(); // TODO, evtl resetten irgendwie...
	}*/

	startLine = 0;
	if(unitMenu->getHeight()/2 > startLine)
		startLine = unitMenu->getHeight()/2;
	if(goalMenu->getHeight() > startLine)
		startLine = goalMenu->getHeight();


	if(unitMenu->menuHasChanged())
	{
		if(unitMenu->secondLevel())
			menuButton[UNIT_MENU]->setBitmap(BACK_BITMAP);
//				updateText(BACK_STRING);
		else if(unitMenu->isOpen())
			menuButton[UNIT_MENU]->setBitmap(DELETE_BITMAP);
//				updateText(CLOSE_STRING);
		else	
			menuButton[UNIT_MENU]->setBitmap(ADD_BITMAP);
//				updateText(ADD_GOAL_STRING);
	}

	
	if((startLine!=oldStartLine)||(getChangedFlag()))
	{
		if(getChangedFlag())
			anarace->getpStart()->readjustGoals();
					//(*anarace->getStartCondition())->getUnit(0) );
		processList();
	}

	if(unitMenu->isOpen())
	{
		techTreeWindow->assignAnarace(anarace);
		techTreeWindow->setCurrentGoalUnit(currentGoalUnit);
		techTreeWindow->Show();
	}
	else 
	{
		// TODO was wenn mehrere player? => 'Hide()' guimain ueberlassen!
		techTreeWindow->Hide();
	}
}

const bool ForceWindow::saveGoal()
{
	savingGoal = true;
	needSaveBox();
	return(true);
}

const bool ForceWindow::openGoalMenu()
{
	if(goalMenu->isOpen())
	{
		menuRadio->leftButtonReleased(menuButton[GOAL_MENU]);
		goalMenu->close();
		goalMenuOpenedExternally = false;
		Object::focus = NULL;
	} else
	{
		menuRadio->leftButtonPressed(menuButton[GOAL_MENU]);
		goalMenuOpenedExternally = true;
		Object::focus = goalMenu;
	}
	return(true);
}

const bool ForceWindow::openUnitMenu()
{
	if(unitMenu->isOpen())
	{
		menuRadio->leftButtonReleased(menuButton[UNIT_MENU]);
		unitMenu->close();
		unitMenuOpenedExternally = false;
		Object::focus = NULL;
	} else
	{
		menuRadio->leftButtonPressed(menuButton[UNIT_MENU]);
		unitMenuOpenedExternally = true;
		Object::focus = unitMenu;
	}
	return(true);
}

void ForceWindow::needSaveBox()
{
	Button::resetButton();
	Window::needSaveBox = true;
	if(savingGoal)
		Window::saveBoxParameter.saveboxText = SAVE_GOALS_AS_STRING;
	else 
		Window::saveBoxParameter.saveboxText = NULL_STRING;
	Window::saveBoxParameter.descriptionText = GIVE_GOAL_A_NAME_STRING;
	Window::saveBoxParameter.okString = SAVE_BOX_OK_STRING;
	Window::saveBoxParameter.cancelString = SAVE_BOX_CANCEL_STRING;
	Window::saveBoxParameter.inputProposal = "";
	saveBox = true;
}

void ForceWindow::saveBoxIsCanceled()
{
	if(savingGoal)
		menuButton[SAVE_GOALS]->forceUnpress();
	else 
		goalName->forceUnpress();
	makePufferInvalid();
}

void ForceWindow::saveBoxIsDone(std::string& input_string)
{
	if(savingGoal)
	{
//		database.saveGoal(input_string, anarace->getGoal()); TODO
		goalMenu->resetData();
		Object::msgList.push_back(Object::theme.lookUpFormattedString(SAVED_GOAL_STRING, anarace->getGoal()->getName()));
	} else
	{
		goalName->updateText(input_string);
		anarace->getGoal()->setName(input_string);
	}
	saveBoxIsCanceled();
}



void ForceWindow::reloadStrings()
{
// TODO Problem wenn reloadStrings aufgerufen wird ohne dass je initialisiert wurde?
	processList();
	Window::reloadStrings();
}


void ForceWindow::processList()
{
//	if(!isShown())
//		return;

//	filledHeight = 0; ? TODO
	if(anarace==NULL)
		return;
	std::list<ForceEntry*>::iterator goal_entry = goalForceList.begin();

	for(std::list<GOAL>::iterator i = anarace->getGoal()->goalList.begin(); i!= anarace->getGoal()->goalList.end(); ++i)
	{
		if(goal_entry == goalForceList.end())
		{
		// Suche gleichen Nongoal Eintrag
			std::list<ForceEntry*>::iterator nongoal_entry = nongoalForceList.begin();
			while(nongoal_entry != nongoalForceList.end())
			{
				if((*nongoal_entry)->getUnit() == i->getUnit())
					break;
				++nongoal_entry;
			}
			if(nongoal_entry == nongoalForceList.end()) // =>     Not found? => Insert new goal at the end
			{
				ForceEntry* forceEntry = new ForceEntry(this, Rect(getRelativeClientRectPosition() + Point(5, 15), Size(getClientRectWidth() - 15, FONT_SIZE + 6)), "   " + GAME::lookUpUnitString(anarace->getRace(), i->getUnit()), i->getUnit(), GAME::race[anarace->getRace()].stats[i->getUnit()].unitType, (&*i));
				goalForceList.push_back(forceEntry);
			} //=> Found? => move
			else 
			{
				(*nongoal_entry)->assignGoal(&*i);
       				goalForceList.push_back(*nongoal_entry);
				nongoalForceList.erase(nongoal_entry);
			}
		} else 
		if((*goal_entry)->getUnit() != i->getUnit())
		{
			std::list<ForceEntry*>::iterator k = goal_entry;
			while(k != goalForceList.end())
			{
				if((*k)->getUnit() == i->getUnit())
					break;
				++k;
			}
			if(k != goalForceList.end()) // => Found, move the entry
			{
				ForceEntry* old = *k;
				goal_entry = goalForceList.insert(goal_entry, old);
				++goal_entry;
				goalForceList.erase(k);
			} else // => not found, insert a new one
			{
				ForceEntry* forceEntry = new ForceEntry(this, Rect(getRelativeClientRectPosition()+Point(5, 15), Size(getClientRectWidth()-15, FONT_SIZE+6)), "   " + GAME::lookUpUnitString(anarace->getRace(), i->getUnit()), i->getUnit(), GAME::race[anarace->getRace()].stats[i->getUnit()].unitType, (&*i));
				goal_entry = goalForceList.insert(goal_entry, forceEntry);
				++goal_entry;
			}
		} else // ok
//	      if((*entry)->getUnit() == (*order)->getUnit())
		{
			(*goal_entry)->updateText("   " + GAME::lookUpUnitString(anarace->getRace(), i->getUnit()));
			
			++goal_entry;
		}
	}

	while(goal_entry != goalForceList.end())
	{
	// Suche gleichen Nongoal Eintrag
		if(anarace->getGoal()->getIsBuildable((*goal_entry)->getUnit()))
		{
		// => is a non-goal! move it down!
			(*goal_entry)->assignGoal(NULL);
			nongoalForceList.push_front(*goal_entry);
			goal_entry = goalForceList.erase(goal_entry);
		} else
// not buildable? => delete
		{
			delete(*goal_entry);
			goal_entry = goalForceList.erase(goal_entry);
		}
	}

	
	std::vector<bool> checkedUnits(RACE::UNIT_TYPE_COUNT);
	checkedUnits.assign(RACE::UNIT_TYPE_COUNT, false);

	std::list<ForceEntry*>::iterator nongoal_entry = nongoalForceList.begin();

	while(nongoal_entry != nongoalForceList.end())
	{
		if(true)
//		if(anarace->getGoal()->getIsDisplayed((*nongoal_entry)->getUnit())) TODO
		{
			checkedUnits[(*nongoal_entry)->getUnit()] = true;
			(*nongoal_entry)->updateText("   " + GAME::lookUpUnitString(anarace->getRace(), (*nongoal_entry)->getUnit()));
			++nongoal_entry;
		} else
		{
			delete(*nongoal_entry);
			nongoal_entry = nongoalForceList.erase(nongoal_entry);
		}
	}


		for (unsigned int i = RACE::UNIT_TYPE_COUNT; i--;)
//		if ( (!anarace->getGoal()->isGoal(i)) && ((anarace->getGoal()->getIsBuildable(i))||(anarace->getLocationTotal(0,i))))
//	if (anarace->getGoal()->getIsDisplayed(i)) 
			if ((anarace->getGoal()->getIsHaveable(i))&&(!anarace->getGoal()->getIsGoal(i))&&(!checkedUnits[i])) //&&(anarace->getLocationTotal(loc, i))) TODO // displayed?

//			nonGoalList[i]=true;
			{
				checkedUnits[i]=true;
				ForceEntry* forceEntry;
//				if(n>=size) // add new at the end
				{
					forceEntry = new ForceEntry(this, Rect(getRelativeClientRectPosition()+Point(5, 15), Size(getClientRectWidth() - 15, FONT_SIZE+6)), "   " + GAME::lookUpUnitString(anarace->getRace(), i), i, GAME::race[anarace->getRace()].stats[i].unitType, NULL);
					nongoalForceList.push_back(forceEntry);
				//	++nongoal_size;
				//	++nongoal_n;
				} 
				/*else // adapt forceentry
				{
					forceEntry = *j;
					++j;
					forceEntry->setUnit(i);
					forceEntry->setType(stats[anarace->getRace()][i].unitType);
					forceEntry->updateText("   " + GAME::lookUpUnitString(anarace->getRace(), i));
					forceEntry->assignGoal(NULL);
					++nongoal_n;
				}*/
			}
/*	}
	for (unsigned int loc = 0; loc < 1; ++loc)
	{
		bool unitsthere = false;
		for (unsigned int i = LAST_UNIT; i--;)
			if ((anarace->getGoal()->getIsDisplayed(i))&&(anarace->getLocationTotal(loc, i)))
				unitsthere=true;
		if(!unitsthere)
		{
			locationName[1][loc]->Hide();
			continue;
		}	   

		for (unsigned int i = LAST_UNIT; i--;)
//		if ( (!anarace->getGoal()->isGoal(i)) && ((anarace->getGoal()->getIsBuildable(i))||(anarace->getLocationTotal(0,i))))
//	if (anarace->getGoal()->getIsDisplayed(i)) 
			if ((anarace->getGoal()->getIsDisplayed(i))&&(anarace->getLocationTotal(loc, i))&&(!checkedUnits[i]))
//			nonGoalList[i]=true;
			{
				ForceEntry* forceEntry;
				if(n>=size)
				{
					forceEntry = new ForceEntry(this, Rect(getRelativeClientRectPosition()+Point(0,0), Size(getClientRectWidth(), FONT_SIZE+6)),
					Rect(getRelativeClientRectPosition(), getClientRectSize()+Size(0, getMaxRect().GetHeight())), "");
					forceList.push_back(forceEntry);
					++size;
				} else
				{
					forceEntry = *j;
					++j;
				}
				forceEntry->setUnit(i);
				forceEntry->setType(stats[anarace->getRace()][i].unitType);
				forceEntry->updateText("   " + GAME::lookUpUnitString(anarace->getRace(), i)));
				forceEntry->assignGoal(NULL);
				++n;
			}
	}*/

/*	while(a!=goalForceList.end())
	{
		delete(*a);
		a = goalForceList.erase(a);
	}

	while(b!=nongoalForceList.end())
	{
		delete(*b);
		b = nongoalForceList.erase(b);
	}*/
		
//	int z = forceList.size();
//	int zz = anarace->getGoal()->goalList.size(); 
// ------------------- GOALS ----------------------------
// ------ START WHERE THE MENUES END
	startLine = 0;
	if(unitMenu->getHeight()/2 > startLine)
		startLine = unitMenu->getHeight()/2;
	if(goalMenu->getHeight() > startLine)
		startLine = goalMenu->getHeight();
	if(startLine)
		startLine++;

	unsigned int start_y = startLine * (FONT_SIZE+9) + menuRadio->getRelativeLowerBound();
	unsigned int line = 0;
	
	anarace->countUnitsTotal();
 // TODO hoehen...
//	goalsText->updateText(anarace->getGoal()->getName());
//	unitMenu->setOriginalPosition(Point(5, menuRadio->getRelativeLowerBound() + 5));
	if(anarace->getGoal()->goalList.size())
	{
		goalsText->Show();
		goalName->Show();
		goalsText->adjustRelativeRect(Rect(Point(7, 5 + start_y), Size()));
		goalName->adjustRelativeRect(Rect(Point(getWidth() - goalName->getWidth() - 15, 5 + start_y), Size(goalName->getWidth(), FONT_SIZE+6)));
//	legend->adjustRelativeRect(Rect(Point(100, line * (FONT_SIZE+7) + startLine*(FONT_SIZE+9)), Size(getClientRectWidth(), FONT_SIZE+5)));
		++line;
	} else
	{
		goalsText->Hide();
		goalName->Hide();
	}

	std::list<ForceEntry*>::iterator forceEntry = goalForceList.begin();
/*	unsigned int current_location = 99;
	for(int i = MAX_LOCATIONS;i--;)
		locationName[0][i]->Hide();*/



		
//	bool menuIsOpen=false;
	for(std::list<GOAL>::const_iterator i = anarace->getGoal()->goalList.begin(); i!= anarace->getGoal()->goalList.end(); ++i)
	{
/*		if(i->getLocation()!=current_location)
		{
			current_location = i->getLocation();
			locationName[0][current_location]->Show();
			locationName[0][current_location]->adjustRelativeRect(Rect(getRelativeClientRectPosition() + Point(0, line * (FONT_SIZE+7) + startLine*(FONT_SIZE+9)), Size(getClientRectWidth(), FONT_SIZE+5)));
			++line;
		}*/
	
	// TODO 2. Modus machen um Produktionsgebaeude ueber 'facility' zu bestimmen (fuer hotkeys geradezu praedestiniert)
		if(anarace->getLocationTotal(i->getLocation(), i->getUnit()) >= i->getCount())
			(*forceEntry)->setTargetForce(getClientRectWidth() /3);
		else
			(*forceEntry)->setTargetForce(anarace->getLocationTotal(i->getLocation(), i->getUnit()) * getClientRectWidth() / (3*i->getCount()));
		(*forceEntry)->setTotalNumber(anarace->getLocationTotal(i->getLocation(), i->getUnit()));
				
		Rect edge = Rect(getRelativeClientRectPosition() + Point(0, start_y + line * (FONT_SIZE+7)), Size((*forceEntry)->getWidth()/*getClientRectWidth()*/, FONT_SIZE+6));
		(*forceEntry)->adjustRelativeRect(edge);
	
/*		if((*forceEntry)->isLocationGoalClicked())
		{
			locationMenu->setParent(*forceEntry);
			locationMenu->open();
			menuIsOpen=true;
		}
	
		if((locationMenu->isOpen()) && (locationMenu->getParent() == *forceEntry))
			line+=locationMenu->getHeight();
		else*/
		++line;
		++forceEntry;
	} // end of for
//	if(!menuIsOpen)
//		locationMenu->close();
	nongoalsText->adjustRelativeRect(Rect(Point(7,  5 + start_y + line * (FONT_SIZE+7)), Size(getClientRectWidth(), FONT_SIZE+6)));
	line++;

//  ---------- NON GOALS
//	bool checkedUnits[LAST_UNIT];
//	for(int i=LAST_UNIT;i--;)
//		checkedUnits[i]=false;
	unsigned int loc=0;
/*	for (unsigned int loc = 1; loc < MAX_LOCATIONS; ++loc)
	{
		bool unitsthere = false;
		for (unsigned int i = LAST_UNIT; i--;)
			if ((anarace->getGoal()->getIsDisplayed(i))&&(anarace->getLocationTotal(loc, i)))
				unitsthere=true;
		if(!unitsthere)
		{
			locationName[1][loc]->Hide();
			continue;
		}
		locationName[1][loc]->Show();
		locationName[1][loc]->adjustRelativeRect(Rect(getRelativeClientRectPosition() + Point(0, line * (FONT_SIZE+7) + startLine*(FONT_SIZE+9)), Size(getClientRectWidth(), FONT_SIZE+5)));
		++line;*/

		forceEntry = nongoalForceList.begin();
		while(forceEntry!=nongoalForceList.end())
		{
//			if ((anarace->getGoal()->getIsDisplayed(i)))//&&(anarace->getLocationTotal(loc, i)))
			{
//				checkedUnits[i]=true;
				(*forceEntry)->setTargetForce(anarace->getLocationTotal(loc, (*forceEntry)->getUnit()) * getClientRectWidth() / (3*anarace->getNonGoalsUnitsTotalMax()));
				(*forceEntry)->setTotalNumber(anarace->getLocationTotal(loc, (*forceEntry)->getUnit()));
				Rect edge = Rect(getRelativeClientRectPosition() + Point(0, start_y + line * (FONT_SIZE+7)), 
							Size((*forceEntry)->getWidth(), FONT_SIZE+6));
				(*forceEntry)->adjustRelativeRect(edge);

				++line;
				++forceEntry;
			} // goal > 0*/
		}
	
/*	}
	for(int loc=0;loc<1;++loc)
	{
		bool unitsthere = false;
		for (unsigned int i = LAST_UNIT; i--;)
			if ((anarace->getGoal()->getIsDisplayed(i))&&(anarace->getLocationTotal(loc, i)))
				unitsthere=true;
		if(!unitsthere)
		{
			locationName[1][loc]->Hide();
			continue;
		}
		locationName[1][loc]->Show();
		locationName[1][loc]->adjustRelativeRect(Rect(getRelativeClientRectPosition() + Point(0, line * (FONT_SIZE+7) + startLine*(FONT_SIZE+9)), Size(getClientRectWidth(), FONT_SIZE+5)))
;
		++line;

		for (unsigned int i = LAST_UNIT; i--;)
//			if ((!anarace->getGoal()->isGoal(i)) && ((anarace->getGoal()->getIsBuildable(i))|| ( anarace->getLocationTotal(0,i))))
			if ((anarace->getGoal()->getIsDisplayed(i))&&(anarace->getLocationTotal(loc, i))&&(!checkedUnits[i]))
			{
				checkedUnits[i]=true;
				(*forceEntry)->setTargetForce(anarace->getLocationTotal(loc, i) * getClientRectWidth() / (3*anarace->getNonGoalsUnitsTotalMax()));
				(*forceEntry)->setTotalNumber(anarace->getLocationTotal(loc, i));
				Rect edge = Rect(getRelativeClientRectPosition() + Point(0, line * (FONT_SIZE+7) + startLine*(FONT_SIZE+9)),
				Size((*forceEntry)->getWidth(), FONT_SIZE+6));
				(*forceEntry)->adjustRelativeRect(edge);

				if((*forceEntry)->isLeftClicked())
				{
					addUnit = i;
					addCount = 1;
					addTime = 0;
					addLocation = 0;
					msgWindow->addMessage(Object::theme.lookUpFormattedString(MOVED_NON_GOAL_STRING, GAME::lookUpUnitString(anarace->getRace(), i)));
				}
				fitItemToRelativeClientRect(edge, true);
				++line;
				++forceEntry;
			} // goal > 0
	}*/

	--line;
	Rect edge=Rect(getRelativeClientRectPosition() + Point(0, start_y + line * (FONT_SIZE+7)), Size(getClientRectWidth(), FONT_SIZE+6));
	fitItemToRelativeClientRect(edge, true);
	

	markedUnit = 0;
}

void ForceWindow::draw() const
{
	Window::draw();
/*	mouseType=0;
	for(std::list<ForceEntry*>::const_iterator j = forceList.begin(); (!mouseType)&&(j!= forceList.end()); ++j)
		if((*j)->isCurrentlyHighlighted())
		{
			const std::list<unsigned int> subErrorList = anarace->getGoal()->allowDeletion((*j)->getUnit());
			const std::list<unsigned int> addErrorList = anarace->getGoal()->allowAddition((*j)->getUnit());
			if((subErrorList.size()>0)&&(!addErrorList.size()))
				mouseType = 1;
			else if((!subErrorList.size())&&(!addErrorList.size()))
				mouseType = 3;
			else if((!subErrorList.size())&&(addErrorList.size()>0))
				mouseType = 2;
			break;
		}
	for(std::list<ForceEntry*>::const_iterator j = forceList.begin(); (!mouseType)&&(j!= forceList.end()); ++j)
		if((*j)->isCurrentlyHighlighted())
		{
			const std::list<unsigned int> subErrorList = anarace->getGoal()->allowDeletion((*j)->getUnit());
			const std::list<unsigned int> addErrorList = anarace->getGoal()->allowAddition((*j)->getUnit());
			if((subErrorList.size()>0)&&(!addErrorList.size()))
				mouseType = 1;
			else if((!subErrorList.size())&&(!addErrorList.size()))
				mouseType = 3;
			else if((!subErrorList.size())&&(addErrorList.size()>0))
				mouseType = 2;
			break;
		}*/
	
}

TechTreeWindow* ForceWindow::techTreeWindow = NULL;

#endif