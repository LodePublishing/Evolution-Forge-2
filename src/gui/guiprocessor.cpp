#include "guiprocessor.hpp"

#include <misc/exceptions.hpp>
#include <misc/log.hpp>
#include <lang/text_storage.hpp>
#include <misc/ids.hpp>

// TODO SDL_NOFRAME for intro picture!

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#define MUSIC_TRANSITION_DURATION 2000
#endif 

#ifdef _FMOD_SOUND
#include <fmod.hpp>
#include <fmod_errors.h>
#endif

GuiProcessor::GuiProcessor():
	tooltip(NULL),
	toolTipParent(NULL),
	currentWindow(NULL),
	windowSelected(false),
	mouseType(0), //?
	mouse(),
	defaultCursor(SDL_GetCursor())
{ }


GuiProcessor::~GuiProcessor()
{

	//	toInfoLog("* " + TextStorage::instance().get(IDS::END_RESET_MOUSE_CURSOR_TEXT_ID)->getText());
	//	SDL_SetCursor(defaultCursor);
	// TODO: Jeder Mauszeiger der benutzt wurde verursacht bei SDL_FreeCursor einen segfault :/ (bzw. 'wurde schon geloescht' Fehler der glibc
}


//void GuiProcessor::animateWaitCursor();



void GuiProcessor::process(DC* dc) {
	if(!windowSelected) {
		currentWindow = NULL;
	}

	BOOST_ASSERT(dc);
	SDL_Object::processAll();
	SDL_Object::redrawnObjects = 0;
	SDL_Object::updateAreasToUpdate();
	SDL_Object::drawAll(dc);
	dc->updateScreen();
	// frameRateControl.updateConfiguration(); TODO
	//inline void Gui::poll(const eTicks etick) {
	//	frameRateControl.poll(etick);
	//}


}


// ------ DC INTERFACE END ------



// ------ EVENTS ------

void GuiProcessor::setMouse(const Point& p, SDL_Object* root_object, const bool showTooltip, const Size& windowSize)
{
	if((p == mouse) && (!Button::isWasResetted())) {
		return;
	}

	Button::setWasResetted(false);
	mouse = p;

	if(Button::isCurrentButtonHasAlreadyLeft())
	{
		if(Button::getCurrentButton() && Button::getCurrentButton()->getAbsoluteRect().isTopLeftCornerInside(p))
		{
			Button::getCurrentButton()->mouseHasEnteredArea();
			Button::setCurrentButtonHasAlreadyLeft(false);
		}
		else {
			return;
		}
	}

	if(Button::getCurrentButton() && !Button::getCurrentButton()->getAbsoluteRect().isTopLeftCornerInside(p))
	{
		Button::getCurrentButton()->mouseHasLeftArea();
		if(!Button::isCurrentButtonPressed()) {
			Button::resetButton();
		}
		else {
			Button::setCurrentButtonHasAlreadyLeft();
		}
	}

	// ignore mousemove if button is still pressed		
	if(Button::getCurrentButton())
	{
		if(Button::isCurrentButtonPressed())
		{
			Button::getCurrentButton()->doHighlight();
			//			Button::getCurrentButton()->mouseHasMoved();
		}
		return;
	}
	if(!Button::isMoveByMouse())
	{
		//		if(SDL_Object::focus==NULL) // TODO
		//		{
		SDL_Object::setHighlighted(root_object->checkHighlight(mouse)); // TODO
		//		} //else
		//		if((!temp_button)&&(Object::editFieldActive()))
		//			temp_button = Object::getEditField()->checkHighlight());
		if(SDL_Object::getHighlighted() && SDL_Object::getHighlighted() != Button::getCurrentButton())
		{
			Button::resetButton();
			Button::setCurrentButton( (Button*)SDL_Object::getHighlighted());
			Button::getCurrentButton()->mouseHasEnteredArea();
			Button::setCurrentButtonHasAlreadyLeft(false);
		}

		if(showTooltip)
		{
			// first we have to check the object with checkToolTip.
			// The result is either the object itself or one of its children that owns a tooltip

			const Object* temp = toolTipParent;
			toolTipParent = NULL;

			const Object* temp2 = ((Object*)root_object)->checkToolTip(mouse);
			if(temp2 != NULL) {
				toolTipParent = temp2;
			}
			// toolTipParent changed or tooltip has to be deleted?
			if(((toolTipParent != temp) || (tooltip == NULL)))
			{
				delete tooltip;
				if(!toolTipParent) {
					tooltip = NULL;
				}
				else 
				{	
					//					if(toolTipParent->getToolTipEString()!=NULL_STRING)
					//						tooltip = new ToolTip(root_object, toolTipParent->getToolTipEString());
					//					else
					// TODO!					tooltip = new ToolTip(root_object, toolTipParent->getToolTipString());
				}
			} else if(tooltip) {
				Point tp = mouse + Size(8, 8);
				if(tp.getX() + tooltip->getWidth() + 10 >= windowSize.getWidth()) {
					tp.setX(windowSize.getWidth() - tooltip->getWidth() - 10);
				}
				if(tp.getY() + tooltip->getHeight() + 10 >= windowSize.getHeight()) {
					tp.setY(windowSize.getHeight() - tooltip->getHeight() - 10);
				}
				tooltip->setPosition(tp);
			}

		}
	}

	if(!showTooltip && tooltip)
	{
		delete tooltip;
		tooltip = NULL;
	}
}


void GuiProcessor::leftDown(const Point& mouse, SDL_Object* root_object)
{
	if(Button::isWasResetted()) {
		return;
	}
	if(Button::getCurrentButton() != NULL)
	{
		Button::getCurrentButton()->mouseLeftButtonPressed(mouse);
		Button::setCurrentButtonPressed();
	} else {
		SDL_Object::resetFocus();
	}
}

void GuiProcessor::leftUp(const Point& mouse, SDL_Object* root_object)
{
	if((Button::getCurrentButton()!=NULL)&&(Button::isCurrentButtonPressed())) {
		Button::getCurrentButton()->mouseLeftButtonReleased(mouse);
	}
	Button::setCurrentButtonPressed(false);
	Button::setCurrentButtonHasAlreadyLeft(false);
	//setMouse(mouse, root_object);

	if(Button::isMoveByMouse()==true)
	{
		Button::setMoveByMouse(false);
		Button::setMouseMovePoint(Point(0, 0));
	}
	if(!Button::getCurrentButton()) {
		SDL_Object::resetFocus();
	}

}

void GuiProcessor::rightDown(const Point& mouse, SDL_Object* root_object)
{
	if(Button::isWasResetted()) {
		return;
	}
	if(Button::getCurrentButton()!=NULL)
	{
		Button::getCurrentButton()->mouseRightButtonPressed(mouse);
		Button::setCurrentButtonPressed();
	}
}

void GuiProcessor::rightUp(const Point& mouse, SDL_Object* root_object)
{
	if((Button::getCurrentButton()!=NULL)&&(Button::isCurrentButtonPressed())) {
		Button::getCurrentButton()->mouseRightButtonReleased(mouse);
	}
	Button::setCurrentButtonPressed(false);
	Button::setCurrentButtonHasAlreadyLeft(false);
	//setMouse(mouse, root_object);
}

void GuiProcessor::wheelToTop()
{
	if(currentWindow) {
		currentWindow->moveScrollBarToTop();
	}
}

void GuiProcessor::wheelToBottom()
{
	if(currentWindow) {
		currentWindow->moveScrollBarToBottom();
	}
}

void GuiProcessor::wheelUp()
{
	if(currentWindow) {
		currentWindow->wheelUp();
	}
}

void GuiProcessor::wheelDown()
{
	if(currentWindow) {
		currentWindow->wheelDown();
	}
}

void GuiProcessor::setCursor(Cursor* cursor) {
	SDL_SetCursor((SDL_Cursor*)cursor);
}

void GuiProcessor::resetCursor() {
	SDL_SetCursor(defaultCursor);
}


void GuiProcessor::resetWindow()
{
	windowSelected = false;
	currentWindow = NULL;
}
