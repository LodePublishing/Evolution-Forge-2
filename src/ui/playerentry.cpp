#include "playerentry.hpp"

#if 0


#include "configuration.hpp"
#include <sstream>

PlayerEntry::PlayerEntry(Object* player_parent, const Rect rect, const Size distance_bottom_right) :
	Object(player_parent, rect, distance_bottom_right),
	currentScore(MAX_TIME),
	programScore(MAX_TIME),
	goalComplete(0),
	initMode(INACTIVE),
	scoreMode(SCORE_FULFILL_MODE),
// TODO Object:: arrange top left :(
// 
	playerText(new StaticText(this, "", Rect(), Size(0, 0), IMPORTANT_COLOR, SMALL_BOLD_FONT, DO_NOT_ADJUST)),
	currentActionButton(new Button(this, Rect(), Size(0,0), STANDARD_BUTTON, NULL_BITMAP, STATIC_BUTTON_MODE, PAUSED_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH)),
	raceMenuButton(new Button(this, Rect(Point(0, FONT_SIZE+8), Size(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)/2, 0)), Size(0, 0), TAB_BUTTON, NULL_BITMAP, STATIC_BUTTON_MODE, CHOOSE_RACE_STRING, DO_NOT_ADJUST, SMALL_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH)),
	raceMenu(new RaceMenu(this, Rect(), Size(0,0), DO_NOT_ADJUST )),
//	removePlayerButton(new Button(this, Rect(Point(0, 1), Size(8, 8)), Size(5, 0), CANCEL_BUTTON, true, PRESS_BUTTON_MODE, NULL_STRING, DO_NOT_ADJUST)),
	scoreText(new StaticText(this, Rect(), Size(5, 0), IMPORTANT_COLOR, LARGE_SHADOW_BOLD_FONT, DO_NOT_ADJUST)),
	speedText(new StaticText(this, Rect(), Size(5, 0), IMPORTANT_COLOR, SMALL_FONT, DO_NOT_ADJUST)),
	goalsFulfilledText(new StaticText(this, Rect(Point(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)/2 + 5, FONT_SIZE+8), Size(0, 0)), Size(5, 0), IMPORTANT_COLOR, SMALL_BOLD_FONT, DO_NOT_ADJUST)),
//	addPlayerButton(new Button(this, Rect(Point(5, 0), Size(60, 0)), Size(5, 0), MY_BUTTON, false, PRESS_BUTTON_MODE, ADD_PLAYER_STRING, TOP_CENTER, LARGE_BOLD_FONT, AUTO_SIZE)),
	optimizing(false),
	assignRace(-1),
	raceMenuOpenedExternally(false)
{
/* TODO:
- Startposition
- Startbedingungen
 * */
	speedText->Hide();
	raceMenu->setPositionParent(raceMenuButton);
	addPlayer();
/*	currentActionButton->Hide();
	scoreText->Hide();
	goalsFulfilledText->Hide();
	playerText->Hide();
//	addPlayerButton->Show();
//	removePlayerButton->Hide();
	raceMenuButton->Hide();*/
	for(unsigned int i=20;i--;)
	{
		oldScoreCounter[i] = 0;
		oldScore[i] = MAX_TIME-1;
	}
	reloadStrings();
	process();
	reloadOriginalSize();
}

void PlayerEntry::reloadOriginalSize()
{
	playerText->setOriginalPosition(Point(0, 0));
//	removePlayerButton->setOriginalPosition(Point(0, 1));
	goalsFulfilledText->setOriginalPosition(Point(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)/2 + 5, FONT_SIZE+8));

	currentActionButton->setOriginalSize(Size(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)*10/9, 0));
	currentActionButton->setOriginalPosition(Point(playerText->getRelativeRect().getLeft()+playerText->getTextSize().getWidth()+5, -1));
	scoreText->setOriginalPosition(Point(currentActionButton->getRelativeRightBound()+5, -2));
	raceMenuButton->setOriginalPosition(Point(0, FONT_SIZE+8));
	raceMenuButton->setOriginalSize(Size(Object::theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)/2, 0));
	raceMenu->setOriginalPosition(Point(0, 2*raceMenuButton->getTextHeight()));
	Object::reloadOriginalSize();
	speedText->setOriginalPosition(Point(scoreText->getRelativeRightBound() - speedText->getTextSize().getWidth(), -speedText->getTextSize().getHeight()));
}

const unsigned int PlayerEntry::getLineHeight() const
{
	return(1+raceMenu->getHeight());
}

const bool PlayerEntry::addPlayer()
{
	if(initMode == INACTIVE)
	{
		setInitMode(NOT_INITIALIZED);
//		addPlayerButton->Hide();
//		removePlayerButton->Show();
		playerText->Show();
		scoreText->Show();
		goalsFulfilledText->Hide();
		currentActionButton->Hide();
		raceMenuButton->Show();
		reloadOriginalSize();
		return(true);
	}
	else return(false);
}

const bool PlayerEntry::openRaceMenu()
{
	if(initMode == INACTIVE)
		return(false);
	if(raceMenu->isOpen())
	{
		raceMenuButton->forceUnpress();
		raceMenu->close();
		raceMenuOpenedExternally = false;
		Object::focus = NULL;
		return(true);
	} else 
	{
		raceMenuButton->forcePress();
		raceMenuOpenedExternally = true;
		Object::focus = raceMenu;
		return(true);
	}
}

void PlayerEntry::reloadStrings()
{
	playerText->updateText(Object::theme.lookUpFormattedString(PLAYER_STRING, number));
	Object::reloadStrings();
}

void PlayerEntry::setNumber(const unsigned int player_number)
{
	number = player_number;
	reloadStrings();
}

PlayerEntry::~PlayerEntry()
{
	delete currentActionButton;
	delete scoreText;
	delete speedText;
	delete goalsFulfilledText;
	delete playerText;
//	delete addPlayerButton;
//	delete removePlayerButton;
	delete raceMenuButton;
	delete raceMenu;
}

void PlayerEntry::mouseHasLeft()
{
	if(!raceMenuOpenedExternally)
	{
		if(raceMenuButton->isCurrentlyActivated())
		{
			raceMenuButton->forceUnpress();	
			raceMenu->close();
		}
	}
}

void PlayerEntry::resetTime()
{
	for(unsigned int i=20;i--;)
	{
		oldScoreCounter[i] = 0;
		oldScore[i] = MAX_TIME-1;
	}
	currentScore = MAX_TIME;
	programScore = MAX_TIME;
	goalComplete = 0;
}

void PlayerEntry::resetData()
{
	resetTime();	
	initMode = NOT_INITIALIZED;
	scoreMode = SCORE_FULFILL_MODE;
}

void PlayerEntry::setScore(const unsigned int score)
{
	if(score==programScore)
		return;
	programScore = score;
}

void PlayerEntry::setGoalComplete(const unsigned int goal_complete)
{
	if(goal_complete==goalComplete)
		return;
	goalComplete = goal_complete;
}

void PlayerEntry::setOptimizing(const bool opt)
{
	if((opt==optimizing)||(initMode!=INITIALIZED))
		return;
	optimizing = opt;
}

void PlayerEntry::setInitMode(const eInitMode init_mode)
{
	initMode = init_mode;
	if(initMode == INITIALIZED)
	{
		raceMenuButton->updateText(GAME::lookUpGameString(GAME::FIRST_RACE_STRING + assignRace));
		currentActionButton->Show();
		goalsFulfilledText->Show();	
	}
}

void PlayerEntry::setScoreMode(const eScoreMode score_mode)
{
	if(score_mode == scoreMode)
		return;
	scoreMode = score_mode;
}

const bool PlayerEntry::isOptimizing() const
{
	if(initMode!=INITIALIZED)
		return(false);
	else return(optimizing);
}


void PlayerEntry::process()
{
	if(!isShown())
		return;
	Object::process();
	
	if(initMode!=INACTIVE)
	{
		if(currentActionButton->isLeftClicked())
		{
			optimizing = currentActionButton->isCurrentlyActivated();
		} else if(optimizing != currentActionButton->isCurrentlyActivated())
		// => aeusserer Einfluss => Button aktualisieren
		{
			if(optimizing)
				currentActionButton->forcePress();
			else currentActionButton->forceUnpress();
		}
		
		if(scoreMode==SCORE_FULFILL_MODE)
		{
			goalsFulfilledText->updateToolTip(OF_GOALS_FULFILLED_TOOLTIP_STRING);
			goalsFulfilledText->updateText(theme.lookUpFormattedString(OF_GOALS_FULFILLED_STRING, goalComplete));
			if(!isOptimizing()) 
				currentActionButton->updateText(PAUSED_STRING);
			else
				currentActionButton->updateText(SEARCHING_STRING);
			speedText->Hide();
		}
		else if(scoreMode==SCORE_TIME_MODE)
		{
			goalsFulfilledText->updateToolTip(OF_TIME_FULFILLED_TOOLTIP_STRING);
			goalsFulfilledText->updateText(theme.lookUpFormattedString(OF_TIME_FULFILLED_STRING, goalComplete));
			if(!isOptimizing())
				currentActionButton->updateText(PAUSED_STRING);
			else
				currentActionButton->updateText(OPTIMIZING_STRING);
			speedText->Show();
			speedText->updateText(GAME::lookUpGameString(GAME::FIRST_GAME_SPEED_STRING + efConfiguration.getGameSpeed()));
		} 
// else see below
/*	else if(surrentMode==SCORE_MODE
	{
		goalsFulfilledText->updateText(theme.lookUpFormattedString(RES_UNITS_STRUCT_STRING, 0,0,0));
		if(!anarace->isOptimizing())
			currentActionText->updateText(PAUSED_STRING);
		else
			currentActionText->updateText(OPTIMIZING_STRING);
		scoreText->updateText(theme.lookUpFormattedString(TOTAL_STRING, 123));
	}*/
	
		if(programScore!=currentScore)
		{
			currentScore -= ((signed int)currentScore - (signed int)programScore)/2;
		    	if(programScore<currentScore)
				--currentScore;
			else if(programScore>currentScore)
				++currentScore;
			std::ostringstream os;
			if(scoreMode==SCORE_FULFILL_MODE)
				os << "[--:--]";
			else
				os << "[" << formatTime(currentScore, efConfiguration.getGameSpeed()) << "]";
			scoreText->updateText(os.str());
		}
	}
	else if(initMode == INACTIVE)
	{
		playerText->Hide();
		scoreText->Hide();
		speedText->Hide();
		currentActionButton->Hide();
		raceMenuButton->Hide();
		goalsFulfilledText->Hide();
	}
	
/*	if(addPlayerButton->isLeftClicked())
		addPlayer();
	if(removePlayerButton->isLeftClicked())
	{
		resetData();
		setInitMode(INACTIVE);
		addPlayerButton->Show();
		removePlayerButton->Hide();
		playerText->Hide();
		scoreText->Hide();
		goalsFulfilledText->Hide();
		currentActionButton->Hide();
		raceMenuButton->updateText(CHOOSE_RACE_STRING);
		raceMenuButton->Hide();
	}*/

	assignRace=-1;
	if((assignRace = raceMenu->getPressedItem())>=0)
	{	
// closing:
		raceMenuButton->forceUnpress();
		setInitMode(INITIALIZED);
	} else
	if(raceMenuButton->isLeftClicked())
	{
		raceMenu->open();
		if(!raceMenu->isOpen())
		{
			raceMenuButton->forceUnpress();		
			raceMenu->close();
			raceMenuOpenedExternally = false;
		} else
		{
			raceMenu->close();
			raceMenu->open();
		}
	}
}

#endif