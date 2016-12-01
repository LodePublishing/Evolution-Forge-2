#include "scrollbar.hpp"

#define MAX_INTERNAL_SCROLLY 10000

ScrollBar::ScrollBar(SDL_Object* const scroll_parent, 
						   const Sint16 start_y, 
						   const Uint16 max_height, 
						   const boost::shared_ptr<const ButtonColors>& up_button_colors,
						   const boost::shared_ptr<const ButtonColors>& down_button_colors,
						   const boost::shared_ptr<const WindowColors>& window_colors,
						   const bool scroll_hideable) :
	Object(scroll_parent, Rect()),//scroll_parent->getWidth(), scroll_parent->getHeight())), // TODO
	firstItemY(0),
	lastItemY(0),
	startY(start_y),
	hideable(scroll_hideable),
	internalScrollY(0),
	internalHeight(0),
	currentScrollY(0),
	targetScrollY(0),
	barHeight(0),
	clientHeight(0),
	clientTargetHeight(0),
	totalHeight(0),
	maxHeight(max_height),
	windowColors(window_colors),
	add(new Button(this, Rect(((SDL_Object*)getParent())->getWidth()-10, 0, 8, 8), Size(0,0), down_button_colors)),// SMALL_ARROW_DOWN_BITMAP, PRESS_BUTTON_MODE, NULL);
	sub(new Button(this, Rect(((SDL_Object*)getParent())->getWidth()-10, 0, 8, 8), Size(0,0), up_button_colors))//ARROW_BUTTON, SMALL_ARROW_UP_BITMAP, PRESS_BUTTON_MODE, NULL);
{ }

ScrollBar::~ScrollBar()
{
	delete add;
	delete sub;
}



void ScrollBar::checkBoundsOfChildren(const Sint16 upper_bound, const Sint16 lower_bound)
{
	Object* tmp = (Object*)getChildren();
	if (tmp) {
		do {
			if((tmp != add) && (tmp != sub))
			{
				if(((tmp->getAbsoluteUpperBound() < upper_bound) || (tmp->getAbsoluteLowerBound() > lower_bound)))
				{
					if(tmp->isClipped())
					{
						if((tmp->getAbsoluteLowerBound() > upper_bound) && (tmp->getAbsoluteUpperBound() < lower_bound))
						{
							tmp->Show();
							tmp->setClipRect(Rect(tmp->getAbsoluteLeftBound(), upper_bound, tmp->getWidth(), lower_bound - upper_bound));
						} else 
						{
							tmp->Hide();
							tmp->setClipRect(Rect());
						}
					}	
					else
						tmp->Hide();
				}
				else tmp->Show();
			}
			tmp = (Object*)(tmp->getNextBrother());
		} while (tmp != (Object*)getChildren());
	}
}

SDL_Object* ScrollBar::checkHighlight(const Point& mouse) {
	if(Rect(((SDL_Object*)getParent())->getAbsolutePosition(), ((SDL_Object*)getParent())->getSize() + Size(8, 0)).isTopLeftCornerInside(mouse)) {
		add->Show();
		sub->Show();
	} else {
		add->Hide();
		sub->Hide();
	}
	return SDL_Object::checkHighlight(mouse);
}

// TODO: Klarer gliedern zwischen virtueller Hoehe und realer Hoehe!
void ScrollBar::process() // process messages, continue animation etc.
{

	if(!isShown()) {
		return;
	}

	
	totalHeight = lastItemY - firstItemY + clientHeight; //? :-/

// totalHeight wird 0... ?

//	unsigned int oldBarHeight = barHeight;

	if(lastItemY == firstItemY) {
		barHeight = clientHeight;
	} else {
		barHeight = clientHeight * clientHeight / totalHeight;
	}
	
	if(barHeight > clientHeight) {
		barHeight = clientHeight;
	}
	
//	signed int oldScrollY = currentScrollY;
	currentScrollY = targetScrollY;
	if(currentScrollY < 0) {
		currentScrollY = 0;
	}

	if(currentScrollY > (signed int)clientHeight - (signed int)barHeight) {
		currentScrollY = (signed int)clientHeight - (signed int)barHeight;
	}

	Sint16 position = 0;
	if(clientHeight <= 0) {
		position = 0;
	} else {
		position = currentScrollY * (signed int)(totalHeight / clientHeight);
	}
	setPosition(Point(0, startY-position));
	add->setPosition(Point(((SDL_Object*)getParent())->getWidth() -12, clientHeight + position + 6));
	sub->setPosition(Point(((SDL_Object*)getParent())->getWidth() -12, position - 4));


	targetScrollY = currentScrollY;
	
	Object::process();

//	if((currentScrollY != oldScrollY)||(barHeight != oldBarHeight)||(add->checkForNeedRedraw())||(sub->checkForNeedRedraw()))
//		setNeedRedrawMoved(); TODO

	if(add->isLeftClicked()) {
		moveDown();
	}
	if(sub->isLeftClicked()) {
		moveUp();
	}

	// TODO: nicht zeichnen falls Hoehe zu klein
}


#include <sstream>
void ScrollBar::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	// TODO!
	dc->setBrush(windowColors->getBackgroundBrush());
//	if(gui.isMouseInside(Rect(getParent()->getAbsolutePosition() + Point(getWidth(), startY+5) - Size(14, 0), Size(12, getHeight()+12)))) {
//		dc->setPen(windowsColors->getHighlightedBorderPen()));//*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
//	} else { TODO
		dc->setPen(windowColors->getBorderPen());
//	}
		
	dc->DrawRectangle(Rect(((SDL_Object*)getParent())->getAbsolutePosition() + Size(((SDL_Object*)getParent())->getWidth()-13, startY+5) - Size(getAbsolutePosition().getX(), getAbsolutePosition().getY()), Size(10, clientHeight)));
	//dc->setBrush(*gui.lookUpBrush(CONTINUE_BUTTON_BRUSH)); TODO
	dc->DrawRectangle(Rect(((SDL_Object*)getParent())->getAbsolutePosition() + Point(((SDL_Object*)getParent())->getWidth()-12, startY+currentScrollY+5) - Size(getAbsolutePosition().getX(), getAbsolutePosition().getY()), Size(8, barHeight)));
	Object::draw(dc);
		
	/*Point p = Point(100, 300);
	dc->setTextForeground(DC::toSDL_Color(255, 20, 20));
	dc->setFont(gui.lookUpFont(LARGE_BOLD_FONT));
	dc->setBrush(Brush(Color(dc->getSurface(), 0, 0, 0), SOLID_BRUSH_STYLE));
	dc->DrawRectangle(Rect(p, Size(200, 20)));

	std::ostringstream os;
	os.str("");
	os << "cH : " << clientHeight << " / T : " << totalHeight << " / cSY : " << currentScrollY << "  [" << firstItemY << ":" << lastItemY << "]";
	dc->DrawText(os.str(), p + Size(20, 2));	*/
}

void ScrollBar::setClientHeight(const Uint16 height) {
	BOOST_ASSERT(height >= 12);

	clientHeight = height - 12;
}

void ScrollBar::setClientTargetHeight(const Uint16 height) {
	clientTargetHeight = height;
}

void ScrollBar::moveUp() {
	targetScrollY -= clientHeight / 40;
}

void ScrollBar::moveDown() {
	targetScrollY += clientHeight / 40;
}

// TODO: Wenn Scrollbereich ausserhalb des Fensters rutscht moechte das Programm verstaendlicherweise neumalen, da es nicht weiss, dass die entsprechenden Eintraege versteckt werden... :-/
void ScrollBar::moveToTop() {
	if(currentScrollY==0)
		return;
	targetScrollY = 0;
}

void ScrollBar::moveToBottom() {
	targetScrollY = 9999;
}
