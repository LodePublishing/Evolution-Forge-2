#include "mainmenuline.hpp"
#include "game.hpp"

#include <guicore/buttoncolors_storage.hpp>
#include <guicore/windowcolors_storage.hpp>
#include <misc/ids.hpp>

const unsigned int MAX_VISIBLE_GAME_TABS = 5;
const unsigned int MAX_GAME_TABS = 100;

#define SMALL_BUTTON_WIDTH 100

MainMenuLine::MainMenuLine(Object* main_parent) : 
	Object( main_parent, Rect(), Size()),


	removeCurrentTabButton(new Button(this, Rect( Point((SMALL_BUTTON_WIDTH+2)*MAX_VISIBLE_GAME_TABS + 30, 2), Size()), Size(), ButtonColorsStorage::instance().get(IDS::STANDARD_BUTTON_ID))), // TODO CANCEL_BITMAP_ID MENU_BUTTON_ID
	scrollLeftButton(new Button(this, Rect(0, 2, 8, 8), Size(0,0), ButtonColorsStorage::instance().get(IDS::STANDARD_BUTTON_ID))), // TODO SMALL_ARROW_LEFT_BITMAP ARROW_BUTTON_ID
	scrollRightButton(new Button(this, Rect( Point((SMALL_BUTTON_WIDTH+2)*MAX_VISIBLE_GAME_TABS + 15, 2), Size(8, 8)), Size(0,0), ButtonColorsStorage::instance().get(IDS::STANDARD_BUTTON_ID))), // TODO SMALL_ARROW_RIGHT_BITMAP ARROW_BUTTON_ID
	gameTabCount(0),
	gameNumber(1),
	viewTabs(0),
	leftTabs(new Group(this, Rect(Point(10, -3), Size(100,0)), Size(0, 0), HORIZONTAL_GROUP, WindowColorsStorage::instance().get(IDS::STANDARD_WINDOWCOLORS_ID), boost::shared_ptr<const Text>(), false, TOP_LEFT)),
	rightTabs(new Group(this, Rect(Point(0, -3), Size(100,0)), Size(0, 0), HORIZONTAL_GROUP, WindowColorsStorage::instance().get(IDS::STANDARD_WINDOWCOLORS_ID), boost::shared_ptr<const Text>(), false, TOP_RIGHT)),
	oldTab((eTabs)0),
	tabHasChanged(true),
	markForRemove(false),
	markForNewGame(false),
	newGameTab(0)
{
// TODO: nach resolutions ordnen! *theme.lookUpRect etc. in data.txt eintragen
// left:

	for(unsigned int i = MAX_TABS;i--;)
	{
		gameNumbers[i] = 0;
		tab[i] = NULL;
	}
	/*tab[0] = new Button(leftTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, NULL_BITMAP, TOP_TAB_BUTTON_MODE, NEW_GAME_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);
// right:
	tab[DATABASE_TAB] = new Button(rightTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, MAP_BITMAP, TOP_TAB_BUTTON_MODE, DATABASE_TAB_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH); // TODO
//	tab[MAP_TAB] = new Button(NULL, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), MAP_TAB_BUTTON, true, TOP_TAB_BUTTON_MODE, MAP_TAB_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);
	tab[SETTINGS_TAB] = new Button(rightTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, SETTING_BITMAP, TOP_TAB_BUTTON_MODE, SETTINGS_TAB_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);
	tab[HELP_TAB]     = new Button(rightTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, HELP_BITMAP, TOP_TAB_BUTTON_MODE, HELP_TAB_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);

	tab[DATABASE_TAB]->updateToolTip(DATABASE_TAB_TOOLTIP_STRING);
//	tab[MAP_TAB]->updateToolTip(MAP_TAB_TOOLTIP_STRING);
	tab[SETTINGS_TAB]->updateToolTip(SETTINGS_TAB_TOOLTIP_STRING);
	tab[HELP_TAB]->updateToolTip(HELP_TAB_TOOLTIP_STRING);*/

	setDrawType(TRANSPARENT_OBJECT);
	reloadOriginalSize();
}

MainMenuLine::~MainMenuLine()
{
	for(unsigned int i=MAX_TABS;i--;)
		delete tab[i];
	delete removeCurrentTabButton;
	delete scrollLeftButton;
	delete scrollRightButton;
}

void MainMenuLine::reloadOriginalSize()
{
/*	setOriginalRect(Rect(0,0,Object::theme.getCurrentResolutionSize().getWidth(), 30));
	for(unsigned int i = 0; i < MAX_TABS; i++)
		if(tab[i])
		{
			tab[i]->setOriginalSize(Size(theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0));
			tab[i]->reloadOriginalSize();
		}
	removeCurrentTabButton->setOriginalPosition(Point((theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)+2)*MAX_VISIBLE_GAME_TABS + 30, 2));
	scrollRightButton->setOriginalPosition(Point((theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH)+2)*MAX_VISIBLE_GAME_TABS + 15, 2));
	Object::reloadOriginalSize();*/ // TODO
}



const eTabs MainMenuLine::getCurrentTab() const
{
	for(unsigned int i = MAX_TABS; i--;) {
		if((tab[i])&&(tab[i]->isCurrentlyActivated())) {
			return((eTabs)i);
		}
	}
	return((eTabs)0);
}

void MainMenuLine::activateTab(const eTabs tab_number)
{
#ifdef _SCC_DEBUG
	if(tab_number<0) {
		toErrorLog("DEBUG (MainMenuLine::activateTab()): Value tab_number out of range.");return;
	}
#endif
	for(unsigned int i = MAX_TABS; i--;)
		if(tab[i])
		{
			if(i == (unsigned int)tab_number) {
				tab[i]->forcePress();
			} else {
				tab[i]->forceUnpress();
			}
		}
}

void MainMenuLine::activateTabNumber(unsigned int tab_number)
{
	unsigned int n = 0;
	for(unsigned int i = 0; i < MAX_TABS; ++i)
		if(tab[i])
		{
			if(n!=tab_number) {
				tab[i]->forceUnpress();
			} else {
				tab[i]->forcePress();
			}
			++n;
		}
}

void MainMenuLine::addNewGameTab()
{
	/*delete(tab[gameTabCount]); // 'new game' loeschen
	
	tab[gameTabCount] = new Button(leftTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, NULL_BITMAP, TOP_TAB_BUTTON_MODE, Object::theme.lookUpFormattedString(GAME_NUMBER_STRING, gameNumber), DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);
	activateTab((eTabs)gameTabCount);

	gameNumbers[gameTabCount] = gameNumber;
	++gameTabCount;
	++gameNumber;
	
	if(gameTabCount<MAX_GAME_TABS)
	{
	 	tab[gameTabCount] = new Button(leftTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, NULL_BITMAP, TOP_TAB_BUTTON_MODE, NEW_GAME_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);
		if(gameTabCount >= MAX_VISIBLE_GAME_TABS) {
			scrollRight();
		}
		Button::resetButton();
		Button::setCurrentButton(tab[gameTabCount]);
	}
	*/
}

void MainMenuLine::adjustView()
{
	for(unsigned int i = MAX_GAME_TABS; i--;)
		if(tab[i])
		{
			if((i >= viewTabs) && (i < viewTabs + MAX_VISIBLE_GAME_TABS)) {
				tab[i]->Show();
			} else {
				tab[i]->Hide();
			}
		}
	leftTabs->reloadOriginalSize();
}

void MainMenuLine::scrollLeft()
{
	leftTabs->reloadOriginalSize();
	if(viewTabs == 0) {
		return;
	}
	--viewTabs;
	adjustView();
}

void MainMenuLine::scrollRight()
{
	leftTabs->reloadOriginalSize();
	if(viewTabs + MAX_VISIBLE_GAME_TABS > gameTabCount) {
		return;
	}
	++viewTabs;
	adjustView();
}
		
void MainMenuLine::removeGameTab(const unsigned int game_number)
{
#ifdef _SCC_DEBUG
	if(game_number>=gameTabCount) {
		toErrorLog("DEBUG: (MainMenuLine::removeGameTab): Value game_number out of range.");return;
	}
#endif
	/*bool was_pressed = tab[game_number]->isCurrentlyActivated();
	Object::currentWindow = NULL;
	delete(tab[game_number]);
	if((game_number>0) && (game_number == gameTabCount-1)) {// last one
		tab[game_number-1]->forcePress();
	} else if(game_number < gameTabCount-1) {
		tab[game_number+1]->forcePress();
	}

	for(unsigned int i = game_number; i < gameTabCount-1; ++i) {
		tab[i] = tab[i+1];
	}
	--gameTabCount;
	if(gameTabCount == MAX_GAME_TABS-1) // alles voll => letztes durch new game ersetzen
	{
	 	tab[gameTabCount] = new Button(leftTabs, Rect(0, 0, theme.lookUpButtonWidth(SMALL_BUTTON_WIDTH), 0), Size(2, 0), TAB_BUTTON, NULL_BITMAP, TOP_TAB_BUTTON_MODE, NEW_GAME_STRING, DO_NOT_ADJUST, MIDDLE_SHADOW_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH);		
		adjustView();
	} else 
	{
		tab[gameTabCount] = tab[gameTabCount+1];
		tab[gameTabCount+1] = NULL;
		if(viewTabs + MAX_VISIBLE_GAME_TABS > gameTabCount) {
			scrollLeft();
		} else {
			adjustView();
		}
	}*/
}

void MainMenuLine::process()
{
	Object::process();

	markForRemove = false;
	markForNewGame = false;

	for(unsigned int  i = MAX_TABS; i--;)
		if((tab[i]) && ((eTabs)i != oldTab) && (tab[i]->isCurrentlyActivated()))
		{
			tab[oldTab]->forceUnpress();
			break;
		}
	
	tabHasChanged = false;
	eTabs t = getCurrentTab();
#ifdef _SCC_DEBUG
	if(t < 0)
		toErrorLog("DEBUG (MainMenuLine::process()): getCurrentTab out of range.");
#endif
	if(oldTab != t)
	{
		oldTab = t;
		tabHasChanged = true;
		if(oldTab == (eTabs)gameTabCount) {
			markForNewGame = true;
		}
	}

	if((oldTab != HELP_TAB) && (oldTab != SETTINGS_TAB) && /*(oldTab != MAP_TAB) && */(oldTab != DATABASE_TAB) && ((unsigned int)oldTab < gameTabCount) && (gameTabCount>1))
	{
		removeCurrentTabButton->Show();
		if(removeCurrentTabButton->isLeftClicked()) {
			markForRemove = true;
		}
	}
	else removeCurrentTabButton->Hide();

	if(viewTabs == 0) {
		scrollLeftButton->Hide();
	} else {
		scrollLeftButton->Show();
	}

	if(viewTabs + MAX_VISIBLE_GAME_TABS > gameTabCount) {
		scrollRightButton->Hide();
	} else {
		scrollRightButton->Show();
	}

	if(scrollLeftButton->isLeftClicked()) {
		scrollLeft();
	}

	if(scrollRightButton->isLeftClicked()) {
		scrollRight();
	}
}

void MainMenuLine::draw(DC* dc) const
{
	//int y = tab[HELP_TAB]->getHeight();

	/*if(tab[getCurrentTab()]->isShown())
	{
		dc->setPen(Pen(dc->changeRelativeBrightness(*Object::theme.lookUpPen(Object::theme.lookUpButtonColors(TAB_BUTTON)->startBorderPen[NORMAL_BUTTON_PHASE])->getColor(), NOT_PRESSED_BRIGHTEN), 1, SOLID_PEN_STYLE));
		dc->DrawHorizontalLine(Point(0, tab[getCurrentTab()]->getAbsoluteLowerBound()), tab[getCurrentTab()]->getAbsoluteLeftBound());
		dc->setPen(Pen(dc->changeRelativeBrightness(*Object::theme.lookUpPen(Object::theme.lookUpButtonColors(TAB_BUTTON)->startBorderPen[NORMAL_BUTTON_PHASE])->getColor(), NOT_PRESSED_DARKEN), 1, SOLID_PEN_STYLE));
		dc->DrawHorizontalLine(Point(tab[getCurrentTab()]->getAbsoluteRightBound(), tab[getCurrentTab()]->getAbsoluteLowerBound()), getParent()->getRelativeRightBound());
	} else if(getCurrentTab() > viewTabs)
	{
		dc->setPen(Pen(dc->changeRelativeBrightness(*Object::theme.lookUpPen(Object::theme.lookUpButtonColors(TAB_BUTTON)->startBorderPen[NORMAL_BUTTON_PHASE])->getColor(), NOT_PRESSED_BRIGHTEN), 1, SOLID_PEN_STYLE));
		dc->DrawHorizontalLine(Point(0, tab[getCurrentTab()]->getAbsoluteLowerBound()), getParent()->getRelativeRightBound());
	} else
	{
		dc->setPen(Pen(dc->changeRelativeBrightness(*Object::theme.lookUpPen(Object::theme.lookUpButtonColors(TAB_BUTTON)->startBorderPen[NORMAL_BUTTON_PHASE])->getColor(), NOT_PRESSED_DARKEN), 1, SOLID_PEN_STYLE));
		dc->DrawHorizontalLine(Point(0, tab[getCurrentTab()]->getAbsoluteLowerBound()), getParent()->getRelativeRightBound());
	}*/
	Object::draw(dc);
}
