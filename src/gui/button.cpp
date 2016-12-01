#include "button.hpp"
#include "radio.hpp"

#pragma warning(push, 0)
#include <boost/assert.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)


Button::Button(SDL_Object* const button_parent, 
		const Rect& button_rect, 
		const Size& distance_bottom_right, 
		const boost::shared_ptr<const ButtonColors>& button_colors, 
		const boost::shared_ptr<const Text>& button_text, 		
		const std::list<std::string> parameterList,
		const boost::shared_ptr<const Text>& button_tooltip, 
		const eButtonMode button_mode, 
		const ePositionMode button_position_mode, 
		const eAutoSize button_auto_size) :
	Object(button_parent, button_rect, distance_bottom_right, 
			button_position_mode == SPECIAL_BUTTON_LEFT ? DO_NOT_ADJUST : button_position_mode, button_auto_size),
	radio(NULL), //?

	allowMoveByMouse(false),
	moved(false),
	isOriginalPosition(false),
	wasPressed(false),
	gradient(0),
	oldGradient(999),
	pressdepth(0),
	buttonColors(button_colors),
	statusFlags(0),
	frameNumber(0),
	text(NULL),
	animationPhase(NORMAL_BUTTON_PHASE),
	bitmap(buttonColors->getButtonAnimation(NORMAL_BUTTON_PHASE)->getBitmap()?new BitmapObject(this, Rect(), Size(), buttonColors->getButtonAnimation(NORMAL_BUTTON_PHASE)->getBitmap(), VERTICALLY_CENTERED):NULL)
{
	init(button_text, button_tooltip, parameterList, button_mode, button_position_mode, button_auto_size);
}

Button::Button(
		const boost::uuids::uuid id,
		SDL_Object* const button_parent, 
		const Rect& button_rect, 
		const Size& distance_bottom_right, 
		const boost::shared_ptr<const ButtonColors>& button_colors, 
		const boost::shared_ptr<const Text>& button_text, 		
		const std::list<std::string> parameterList,
		const boost::shared_ptr<const Text>& button_tooltip, 
		const eButtonMode button_mode, 
		const ePositionMode button_position_mode, 
		const eAutoSize button_auto_size) :
	Object(button_parent, button_rect, distance_bottom_right, 
			button_position_mode == SPECIAL_BUTTON_LEFT ? DO_NOT_ADJUST : button_position_mode, button_auto_size),
	radio(NULL), //?

	allowMoveByMouse(false),
	moved(false),
	isOriginalPosition(false),
	wasPressed(false),
	gradient(0),
	oldGradient(999),
	pressdepth(0),
	buttonColors(button_colors),
	statusFlags(0),
	frameNumber(0),
	text(NULL),
	animationPhase(NORMAL_BUTTON_PHASE),
	bitmap(buttonColors->getButtonAnimation(NORMAL_BUTTON_PHASE)->getBitmap()?new BitmapObject(this, Rect(), Size(), buttonColors->getButtonAnimation(NORMAL_BUTTON_PHASE)->getBitmap(), VERTICALLY_CENTERED):NULL)
{
	init(button_text, button_tooltip, parameterList, button_mode, button_position_mode, button_auto_size);
}

void Button::init(const boost::shared_ptr<const Text>& button_text, const boost::shared_ptr<const Text>& button_tooltip, const std::list<std::string>& parameterList, const eButtonMode button_mode, const ePositionMode button_position_mode, const eAutoSize button_auto_size) {
	updateToolTip(button_tooltip);
	switch(button_mode)
	{
		case NO_BUTTON_MODE:statusFlags |= BF_NOT_CLICKABLE;break;
		case STATIC_BUTTON_MODE:statusFlags |= BF_STATIC;break;
		case PRESS_BUTTON_MODE:break;
		case PUSH_BUTTON_MODE:statusFlags |= BF_REPEATS;break;
		case TAB_BUTTON_MODE:statusFlags |= BF_IS_TAB; statusFlags |= BF_STATIC;break;
		case TOP_TAB_BUTTON_MODE:statusFlags |= BF_IS_TOP_TAB; statusFlags |= BF_IS_TAB; statusFlags |= BF_STATIC;break;
		case BOGRAPH_BUTTON_MODE:statusFlags |= BF_IS_RECTANGLE;break;
		case CHECK_BUTTON_MODE:statusFlags |= BF_STATIC; statusFlags |= BF_IS_CHECKBUTTON;break;
		default:break;
	} 

	Size bitmap_size;
	if(bitmap)
	{
		bitmap_size = bitmap->getBitmapSize();
		setClipped();
	//	bitmap->setPositionParent(this);
	}

	if(button_text!=NULL)
	{
		if(button_position_mode == SPECIAL_BUTTON_LEFT) {
			text = new StaticText(this, Rect(Point(bitmap_size.getWidth()+4,0), getSize()), Size(0,0), buttonColors->getButtonAnimation(PRESSED_BUTTON_PHASE)->getStartTextColor(), buttonColors->getFont(), button_text, parameterList, CENTER_LEFT); // TODO
		} else if(button_auto_size == AUTO_SIZE) {
			text = new StaticText(this, Rect(Point(bitmap_size.getWidth()+4,0), getSize()), Size(0,0), buttonColors->getButtonAnimation(PRESSED_BUTTON_PHASE)->getStartTextColor(), buttonColors->getFont(), button_text, parameterList, DO_NOT_ADJUST); // TODO
		} else {
			text = new StaticText(this, Rect(Point(bitmap_size.getWidth(), 1), getSize()), Size(0,0), buttonColors->getButtonAnimation(PRESSED_BUTTON_PHASE)->getStartTextColor(), buttonColors->getFont(), button_text, parameterList, TOTAL_CENTERED); // TODO
		}
	} else if(bitmap) {
		setOriginalSize(bitmap_size);
	}

	if(text != NULL) {
		text->connect(boost::bind(&Button::updateText, this, _1, _2));
	}
}
	
Button::~Button()
{
	if(Button::currentButton == this) {
		Button::resetButton();
	}
	delete bitmap; // ~_~
	delete text;
}

void Button::updateParameters(const std::list<std::string>& parameterList) {
	text->updateParameters(parameterList);
}

void Button::updateText(const std::string& text, const Size& size) {
	adjustSize((SDL_Object*)getParent(), CHILD_WAS_CHANGED, size);

	// reloadOriginalSize() TODO?
}

void Button::reloadOriginalSize()
{
	// TODO signal -> statictext
	if((text==NULL)&&(bitmap)) {
		setOriginalSize(bitmap->getBitmapSize());
	}
	Object::reloadOriginalSize();	
}

void Button::setPressDepth(const unsigned int depth)
{
	if((pressdepth == depth)||(statusFlags & BF_NOT_CLICKABLE))
		return;
//	Object::addToProcessArray(this);
	pressdepth = depth;
	wasPressed = true;
	if(statusFlags & BF_IS_CHECKBUTTON)
	{
		if(pressdepth == 0) {
			bitmap->setChecked(false);
		} else {
			bitmap->setChecked(true);
		}
	}
}


// Render button.  How it draws exactly depends on it's current state.
void Button::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);


//		if(!(statusFlags & BF_NOT_CLICKABLE)) // ?? TODO
//		{
//			dc->setBrush(*gui.lookUpBrush(NULL_BRUSH));
//			dc->setPen(*gui.lookUpPen(DARK_BACKGROUND_PEN));
//			dc->DrawEdgedRectangle(Rect(getAbsolutePosition()-Size(1,1), getSize() + Size(2,2)));

//			dc->setBrush(*gui.lookUpBrush(NULL_BRUSH)); //?
//			dc->setPen(*gui.lookUpPen(RECTANGLE_PEN));
//			dc->DrawRoundedRectangle(Rect(getAbsolutePosition(), getSize()), 2);
//		}
	dc->setGradient(gradient);
	dc->setPen(buttonColors->getButtonAnimation(animationPhase)->getStartBorderPen());
	dc->setEndPen(buttonColors->getButtonAnimation(animationPhase)->getEndBorderPen());

	if((text!=NULL)||((text==NULL)&&(!bitmap))) // textbutton/bitmaptextbutton or empty button (e.g. bograph)
	{
		dc->setBrush(buttonColors->getButtonAnimation(animationPhase)->getStartBrush());
		dc->setEndBrush(buttonColors->getButtonAnimation(animationPhase)->getEndBrush());
//TODO: eigene tab-button klasse

//			dc->setPen(*gui.lookUpPen(NULL_PEN));
//			if(statusFlags & BF_DOWN)

		if(text) {
			text->setGradient(gradient);
			text->setEndTextColor(buttonColors->getButtonAnimation(animationPhase)->getEndTextColor());
		}

// TODO TAB-BUTTON MODE
		if(pressdepth>0) {
			dc->setPressedRectangle(true);
		} else {
			dc->setPressedRectangle(false);
		}

		if(statusFlags & BF_IS_RECTANGLE) {
//			dc->DrawRectangle(getAbsolutePosition()+Size(pressdepth, pressdepth), getSize()/*+Size(1,1)*/);
			dc->DrawEdgedRoundedRectangle(Point(0, 0), getSize(), 2);
		} else if(statusFlags & BF_IS_TOP_TAB) {
			dc->DrawTabRectangle(Point(0,0), getSize());
		} else {
			dc->DrawEdgedRoundedRectangle(Point(0,0), getSize(), 4);
		}
		dc->setGradient(0);
		dc->setPressedRectangle(false);
	}

 // empty rectangle (e.g. bograph)
	
/*		if((animationPhase==PRESSED_BUTTON_PHASE)||(animationPhase==PRESSED_HIGHLIGHTED_BUTTON_PHASE))
		{
			dc->setPen(Pen(*(gui.lookUpBrush(WINDOW_BACKGROUND_BRUSH)->getColor()),1,SOLID_PEN_STYLE));
			dc->DrawLine(getAbsolutePosition() + Point(0, getHeight()-1), getAbsolutePosition() + Point(getWidth(), getHeight()-1));
			dc->DrawLine(getAbsolutePosition() + Point(getWidth()-1, 0), getAbsolutePosition() + Point(getWidth()-1, getHeight()));
		} ??? */

//		dc->DrawRectangle(Rect(originalButtonRect.getTopLeft() + getAbsolutePosition(), originalButtonRect.getSize()));
	Object::draw(dc);
//	dc->setPen(*gui.lookUpPen(RECTANGLE_PEN));
//	dc->DrawRectangle(getAbsoluteRect());
}



//void Button::set_hotkey_if_focus(int key)
//{
//	hotkey_if_focus = key;
//}
// reset anything that needs to be at the start of a new frame before processing
void Button::frameReset()
{
	statusFlags &= ~BF_HIGHLIGHTED;
	statusFlags &= ~BF_LEFT_CLICKED;
	statusFlags &= ~BF_DOUBLE_CLICKED;
// TODO bei -O3 bleiben die buttons gehighlighted... statusFlags = 0 behebt das, aber das wollen wir ja nicht :o
//	  hideToolTip(); ~~
}

void Button::mouseHasEnteredArea()
{
//	Object::addToProcessArray(this);
	resetBrightness();
	// TODO set brightness? TODO
	if(!(statusFlags & BF_HIGHLIGHTED))
	{
		statusFlags |= BF_JUST_HIGHLIGHTED;
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//		gui.getSound()->playSound(MOUSEOVER_SOUND, /*(getAbsolutePosition() + getSize()/2)*/gui.getMouse().getX()); TODO
#endif
	}
	statusFlags |= BF_HIGHLIGHTED;
	if(statusFlags & BF_WAS_PRESSED)
	{
		if(isOriginalPosition) {
			setPressDepth(0);
		} else {
			setPressDepth(1);
		}
		statusFlags |= BF_DOWN;
	}
/*	if((buttonColorsType == TEXT_BUTTON) || (buttonColorsType == VISITED_TEXT_BUTTON)) {
		SDL_SetCursor(gui.lookUpCursor(HAND_CURSOR, 0));
	}*/ // TODO
}

void Button::mouseHasLeftArea()
{
//	Object::addToProcessArray(this);
	statusFlags &= ~BF_HIGHLIGHTED;
	if(statusFlags & BF_WAS_PRESSED)
	{
		if(isOriginalPosition) {
			setPressDepth(1);
		} else {
			setPressDepth(0);
		}
		statusFlags &= ~BF_DOWN;
	}
	/*if(buttonColorsType == TEXT_BUTTON) {
		SDL_SetCursor(gui.lookUpCursor(ARROW_CURSOR, 0));
	}*/ // TODO
}

void Button::mouseLeftButtonPressed(const Point& mouse)
{
	if((statusFlags & BF_NOT_CLICKABLE)||((statusFlags & BF_IS_TAB)&&(isOriginalPosition==true))) {
		return;
	}
//	Object::addToProcessArray(this);
	statusFlags |= BF_WAS_PRESSED;
	statusFlags |= BF_DOWN;
	if(isOriginalPosition) {
		setPressDepth(0);
	} else {
		setPressDepth(1);
	}
	if(allowMoveByMouse)
	{
		Button::mouseMovePoint = mouse;
		Button::moveByMouse = true;
	}
}

void Button::mouseLeftButtonReleased(const Point& mouse)
{
	if((statusFlags & BF_NOT_CLICKABLE)) {
		return;
	}
//	Object::addToProcessArray(this);
	statusFlags &= ~BF_WAS_PRESSED;
	if(statusFlags & BF_DOWN)
	{
		statusFlags &= ~BF_DOWN;
		statusFlags |= BF_LEFT_CLICKED;
		if(statusFlags & BF_STATIC)
		{
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//			gui.getSound()->playSound(CLICKED_SOUND, gui.getMouse().getX()); TODO
#endif
			if((isOriginalPosition)&&(!(statusFlags & BF_IS_TAB))) {
				isOriginalPosition = false;
			}
			else if(!isOriginalPosition) {
				isOriginalPosition = true;
			}
			wasPressed = true;
			SDL_Object::setFocus(this);
		}
		else
		{
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//			gui.getSound()->playSound(CLICK_SOUND, gui.getMouse().getX()); TODO
#endif
			setPressDepth(0);
		}
		if(radio)
		{
			if(isOriginalPosition) {
				radio->leftButtonPressed(getId());
			} else if(!(statusFlags & BF_IS_TAB)) {
				radio->leftButtonReleased(getId());
			}
		}		
	}
	if(allowMoveByMouse)
	{
		Button::mouseMovePoint = Point(0,0);
		Button::moveByMouse = false;
	}
}

void Button::mouseRightButtonPressed(const Point& mouse)
{
	if((statusFlags & BF_NOT_CLICKABLE)||(statusFlags & BF_STATIC)||((statusFlags & BF_IS_TAB)&&(isOriginalPosition==true))) {
		return;
	}
//	Object::addToProcessArray(this);
	statusFlags |= BF_WAS_PRESSED;
	statusFlags |= BF_DOWN;
	
	if(isOriginalPosition) {
		setPressDepth(0);
	} else {
		setPressDepth(1);
	}
}

void Button::mouseRightButtonReleased(const Point& mouse)
{
	if((statusFlags & BF_NOT_CLICKABLE) || (statusFlags & BF_STATIC)) {
		return;
	}
//	Object::addToProcessArray(this);
	statusFlags &= ~BF_WAS_PRESSED;
	if(statusFlags & BF_DOWN)
	{
		statusFlags &= ~BF_DOWN;
		statusFlags |= BF_RIGHT_CLICKED;
	
		if(statusFlags & BF_STATIC)
		{
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//			gui.getSound()->playSound(CLICK_SOUND, gui.getMouse().getX()); TODO
//			gui.getSound()->playSound(CLICKED_SOUND, (getAbsolutePosition() + getSize()/2).x);
#endif
	/*		if((isOriginalPosition)&&(!(statusFlags & BF_IS_TAB)))
				isOriginalPosition=false;
			else if(!isOriginalPosition)
				isOriginalPosition=true;*/
		}
		else
		{
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//			gui.getSound()->playSound(CLICK_SOUND, gui.getMouse().getX()); TODO
#endif
			setPressDepth(0);
		}
	/*	if(radio)
		{
			if(isOriginalPosition)
				radio->rightButtonPressed(this);
			else 
			if(!(statusFlags & BF_IS_TAB))
				radio->rightButtonReleased();
		}		 // TODO?*/
	}
}



const Object* Button::checkToolTip(const Point& mouse) const 
{
	if( !isShown() || !getAbsoluteRect().isTopLeftCornerInside(mouse)) {
		return NULL;
	}
	return (Object*)this;
}

SDL_Object* Button::checkHighlight(const Point& mouse)
{
	if(!isShown()) {
		return NULL;
	}

	if(!getAbsoluteRect().isTopLeftCornerInside(mouse)) {
		return Object::checkHighlight(mouse);
	}
	return (SDL_Object*)this;
}

void Button::process()
{
	// TODO evtl Animation fuer jede Phase in die config datei
	// dann waere sowas moeglich, dass ich maus reinfahr und das langsam verblasst
	// evtl auch einfach brightencolor ueberlegen...

	if(wasPressed)
	{
		wasPressed = false;
//		setNeedRedrawMoved();
	} // TODO

//		gradient = 100;
//	else
	if(!(statusFlags & BF_HIGHLIGHTED)) {
		gradient += (100 - gradient) / 6 + 1;
	} else  
/*	if((!gui.isGlowingButtons()) || (buttonColors->animationType == NO_ANIMATION))
	{
		if(gradient > gradient / 10 + 1) {
			gradient -= gradient / 10 + 1;
		} else {
			gradient = 0;
		}
	}  
	else*/ // TODO
	{
//		Object::addToNextProcessArray(this);
		switch(buttonColors->getAnimationType())
		{	
//			case NO_ANIMATION:if(gradient < 100) ++gradient;else gradient = 100;break;
			case JUMPY_COLORS_ANIMATION:gradient=(frameNumber%buttonColors->getSpeed())*100/buttonColors->getSpeed();break;
			case GLOWING_ANIMATION:gradient=(unsigned int)(50*(sin(3.141*frameNumber/buttonColors->getSpeed())+1));break;
			case BLINKING_ANIMATION:if(frameNumber<buttonColors->getSpeed()/2) gradient=0;else gradient=100;break;
			default:break;
		}
	}

	if(gradient > 100) {
		gradient = 100;
	}
	
	if(gradient != oldGradient)
	{
		redrawWholeObject();
		oldGradient = gradient;
	}

	Point absoluteCoord = getRelativePosition();
	Size absoluteSize = getSize();
	Object::process();
	
	if(statusFlags & BF_WAS_PRESSED) {
		statusFlags |= BF_HIGHLIGHTED;
	}

	if(statusFlags & BF_HIGHLIGHTED)
	{
		if(frameNumber<buttonColors->getSpeed()) {
			frameNumber += 2;
		}
		else {
			frameNumber = 0;
		}
	}


	if((statusFlags & BF_STATIC)&&(isOriginalPosition))
	{
		if((statusFlags & BF_HIGHLIGHTED) || (gradient < 100 )) {
			animationPhase = PRESSED_HIGHLIGHTED_BUTTON_PHASE;
		} else {
			animationPhase = PRESSED_BUTTON_PHASE;
		}
	}
	else
	if(statusFlags & BF_DOWN)
	{
		if((statusFlags & BF_HIGHLIGHTED) || (gradient < 100 )) {
			animationPhase = PRESSED_HIGHLIGHTED_BUTTON_PHASE;
		} else {
			animationPhase = PRESSED_BUTTON_PHASE;
		}
	}
	else if((statusFlags & BF_HIGHLIGHTED) || (gradient < 100)) {
		animationPhase = HIGHLIGHT_BUTTON_PHASE;
	} else {
		animationPhase = NORMAL_BUTTON_PHASE;
	}

	if(bitmap)
	{
		if(buttonColors->getButtonAnimation(animationPhase)->getBitmap()) {// != bitmap->getBitmapHeight()) {
			bitmap->setBitmap(buttonColors->getButtonAnimation(animationPhase)->getBitmap());
		}
		bitmap->setClipRect(this->getClipRect());
		bitmap->setBrightness(static_cast<Uint8>(100-gradient/2));
	}
}

void Button::doHighlight(const bool high_light) 
{
	if(high_light) {
		statusFlags |= BF_HIGHLIGHTED;
	} else {
		statusFlags &= ~BF_HIGHLIGHTED;
	}
}

bool Button::isLeftClicked()
{
	if(!isShown()) {
		return false;
	}
// currently pressed
	if (statusFlags & BF_LEFT_CLICKED)
	{
		statusFlags &= ~BF_LEFT_CLICKED;
		return true;
	}
	else {
		return false;
	}
}

bool Button::isRightClicked()
{
	if(!isShown()) {
		return false;
	}
// currently pressed
	if (statusFlags & BF_RIGHT_CLICKED)
	{
		statusFlags &= ~BF_RIGHT_CLICKED;
		return true;
	}
	else {
		return false;
	}
}


bool Button::isCurrentlyActivated() const
{
//	if(!isShown())
//			return false;
	if ( (statusFlags & BF_STATIC) && (isOriginalPosition==true) ) {
		return true;
	} else {
		return false;
	}
}

bool Button::isCurrentlyPressed() const
{
	if(!isShown()) {
		return false;
	}
	if (statusFlags & BF_DOWN) {
		return true;
	} else {
		return false;
	}
}

// Is the mouse over this button?
bool Button::isCurrentlyHighlighted() const
{
	if(!isShown()) {
		return false;
	}
	return (statusFlags & BF_HIGHLIGHTED) == BF_HIGHLIGHTED;
}

// changes static buttons
void Button::check(const bool is_checked)
{
	if(isCurrentlyActivated() != is_checked)
    {
		if(!is_checked) {
			forceUnpress();
		} else {
			forcePress();
		}
		makePufferInvalid();
	}
}

// Force button to get pressed, doesn't work for non-static buttons yet
void Button::forcePress(const bool click_message)
{
	if (!(statusFlags & BF_NOT_CLICKABLE))
    {
		if((statusFlags & BF_STATIC) && (!isOriginalPosition))
        {
			if(click_message) {
				statusFlags |= BF_LEFT_CLICKED;
			}
            statusFlags &= ~BF_WAS_PRESSED;
            isOriginalPosition = true;
//          if (statusFlags & BF_DOWN)
//			{
            statusFlags &= ~BF_DOWN;
            setPressDepth(1);
		} else if((!(statusFlags & BF_STATIC)) && (!(statusFlags & BF_DOWN))) {
			if(click_message)
			{
				statusFlags |= BF_LEFT_CLICKED;
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
//				gui.getSound()->playSound(CLICK_SOUND, (getAbsolutePosition() + getSize()/2).getX()); TODO
#endif
			}
			statusFlags |= BF_DOWN;                        //~?
            setPressDepth(1); //?
        }
    }
}

void Button::forceUnpress(const bool click_message)
{
	if((statusFlags & BF_STATIC) && (isOriginalPosition))
    {
		isOriginalPosition = false;
        statusFlags &= ~BF_WAS_PRESSED;
//		if(click_message);
//      statusFlags |= BF_LEFT_CLICKED;
        statusFlags &= ~BF_DOWN; // ~~
        setPressDepth(0);
	}
}


bool Button::addKey(unsigned int key, unsigned int mod)
{
	if(((key == SDLK_KP_ENTER)||(key == SDLK_RETURN))&& (!(mod & (KMOD_LALT | KMOD_RALT | KMOD_ALT))))
	{
		forcePress();
		return true;
	}
	return false;	
}

void Button::resetButton()
{
	if(Button::currentButton!=NULL) {
		Button::currentButton->frameReset();
	}
	Button::currentButton = NULL;
	Button::currentButtonHasAlreadyLeft = false;
	Button::currentButtonPressed = false;
	Button::mouseMovePoint = Point(0, 0);
	Button::moveByMouse = false;
	Button::setWasResetted();
//	SDL_SetCursor(gui.lookUpCursor(ARROW_CURSOR, 0)); // TODO
}


bool Button::currentButtonPressed = false;
bool Button::currentButtonHasAlreadyLeft = false;
Button* Button::currentButton = NULL;
bool Button::moveByMouse = false;
Point Button::mouseMovePoint = Point();
bool Button::doClickedSound = false;
bool Button::wasResetted = false;
