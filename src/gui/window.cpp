#include "window.hpp"

Window::Window(SDL_Object* const window_parent, 
		const Rect rect, 
		const Uint16 max_height,
		const boost::shared_ptr<const Text>& window_title_string, 
		const std::list<std::string>& parameterList,
		const boost::shared_ptr<const WindowColors>& windowColors,
		const eIsScrolled window_is_scrollable, 
		const boost::shared_ptr<const ButtonColors>& scroll_up_button_colors,
		const boost::shared_ptr<const ButtonColors>& scroll_down_button_colors,
		const eIsAutoAdjust window_is_auto_adjust, 
		const Rect clientRect) :
	Object(window_parent, rect, Size()),
	filledHeight(0),
	doAdjustments(false),
	clientRect(clientRect),
	clientStartRect(),
	clientTargetRect(),
	originalClientRect(), // TODO 
	maxHeight(max_height),
	isAutoAdjust(window_is_auto_adjust), //?
	isScrollable(window_is_scrollable), // TODO
	highlighted(false),
	//helpButton(NULL),
	//helpChapter(INDEX_CHAPTER),
	windowColors(windowColors),
	title(new Title(this, window_title_string, parameterList, windowColors)),
	scrollBar(isScrollable != NOT_SCROLLED?new ScrollBar(this, getRelativeClientRectUpperBound(), getMaxHeight(), scroll_up_button_colors, scroll_down_button_colors, windowColors):NULL)
{
	
//			StaticText(this, window_title_string, Rect(Point(2, 3), Size()), Size(), window_colors->getTextColor(), window_colors->getFont());
// TODO title parameter
//	dc->setFont(gui.lookUpFont(SMALL_BOLD_FONT));
//	dc->setTextForeground(*gui.lookUpColor(TITLE_COLOR));

//	dc->setBrush(*gui.lookUpBrush(WINDOW_FOREGROUND_BRUSH));
//	dc->setPen(*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN)); Kasten hinter Title... TODO StaticText



// ------ PROCESSING
	calculateClientRect();


//	filledHeight=clientRect.getHeight();
// ------ Buttons, ScrollBars etc.
}

Window::~Window()
{
	delete scrollBar;
	delete title;
	//delete helpButton;
}

/*void Window::addHelpButton(eHelpChapter help_chapter)
{
	helpButton = new Button(this, Rect(Point(0,10), Size(13, 14)), Size(5 + (isScrollable==SCROLLED?8:0),10), HELP_BUTTON, HELP_BITMAP, PRESS_BUTTON_MODE, NULL_STRING, TOP_RIGHT);
	helpChapter = help_chapter;	
}
*/
void Window::calculateClientRect()
{
	Rect oldClientRect = clientRect;
	clientRect.setSize(getTargetRect().getSize());
	
	if(clientRect.getLeft() < 5) {
		clientRect.setLeft(5);
	}

	if(clientRect.getLeft() > ((signed int)getWidth()) - 5) {
		clientRect.setLeft(((signed int)getWidth()) -5);
	}
	
	if(clientRect.getTop() < 5) {
		clientRect.setTop(5);
	}

	if(clientRect.getTop() > ((signed int)getHeight()) - 5) {
		clientRect.setTop(((signed int)getHeight()) - 5);
	}

	if(clientRect.getBottom() > ((signed int)getHeight()) - 5) {
		clientRect.setBottom(((signed int)getHeight()) - 5);
	}

	if(clientRect.getRight() > ((signed int)getWidth()) - 5) {
		clientRect.setRight(((signed int)getWidth()) - 5);
	}

	originalClientRect = clientRect;
	clientStartRect = oldClientRect;
	clientTargetRect = clientRect;
	if(scrollBar) {
		scrollBar->setStartY(getRelativeClientRectUpperBound());
	}
}

void Window::reloadOriginalSize()
{
	setRect(getOriginalRect());
	//adjustRelativeRect(getOriginalRect());
	clientRect.setSize(getOriginalRect().getSize());
	calculateClientRect();
	adjustClientRect();
	Object::reloadOriginalSize();
}


const Object* Window::checkToolTip(const Point& mouse) const
{
//	if(!(isMouseInside())) {
//		return NULL;
//  }
	return Object::checkToolTip(mouse);
}

SDL_Object* Window::checkHighlight(const Point& mouse)
{
	if(!getAbsoluteRect().isTopLeftCornerInside(mouse) && 
	   ( scrollBar == NULL || !Rect(getAbsolutePosition() + Point(getWidth(), 0), Size(12, getHeight())).isTopLeftCornerInside(mouse))) { 
		return NULL;
	}
	return Object::checkHighlight(mouse);
}

// ----------------------
// ------ MOVEMENT ------
// ----------------------


void Window::adjustClientRect()
{
//CLIENT WINDOW
	Uint16 width = getTargetWidth() + originalClientRect.getWidth();
	Uint16 height = getTargetHeight() + originalClientRect.getHeight();

	if(width < getOriginalRect().getWidth()) {
		width = 0;
	} else {
		width -= getOriginalRect().getWidth();
	}

	if(height < getOriginalRect().getHeight()) {
		height = 0;
	} else {
		height -= getOriginalRect().getHeight();
	}

	if(width!=clientTargetRect.getWidth()) {
		clientStartRect.setWidth(clientRect.getWidth());
	}
	if(height!=clientTargetRect.getHeight()) {
		clientStartRect.setHeight(clientRect.getHeight());
	}

	clientTargetRect.setWidth(width);
	clientTargetRect.setHeight(height);
}

void Window::wheelUp()
{
	if(scrollBar) {
		scrollBar->moveUp();
	}
}

void Window::wheelDown()
{
	if(scrollBar) {
		scrollBar->moveDown();
	}
}

void Window::moveScrollBarToTop()
{
	if(scrollBar) {
		scrollBar->moveToTop();
	}
}

void Window::moveScrollBarToBottom()
{
	if(scrollBar) {
		scrollBar->moveToBottom();
	}
}

void Window::process()
{
	if(!isShown()) {
		return;
	}
	
//	if((getScrollBar())&&(getScrollBar()->isPufferInvalid()))
//		makePufferInvalid(); //?

	adjustClientRect();
	if(doAdjustments == true)
	{
		adjustRelativeRect(Rect(Point(getTargetRect().getTopLeft()), Size(getTargetRect().getWidth(), filledHeight+25))); // TODO!
		adjustClientRect();
		doAdjustments = false;
	}

	calculateClientRect();
	
	if(scrollBar)
	{
		scrollBar->setClientHeight(getClientRectHeight());
		scrollBar->setClientTargetHeight(getClientTargetHeight());
	}

	Object::process();
/*
	if(helpButton != NULL)
	{
		if(gui.isMouseInside(getAbsoluteRect()))
		{
			helpButton->Show();
			if(helpButton->isLeftClicked()) {
				Window::gotoHelpChapter = helpChapter;
			}
		} else {
			helpButton->Hide();
		}
	}
*/	
	
	if(Object::smoothMovements) {
		clientRect.moveSmooth(clientStartRect, clientTargetRect);
	} else {
		clientRect = clientTargetRect;
		clientStartRect = clientRect;
	}

//	if(/*(!Object::windowSelected)&&*/(((gui.isMouseInside(getAbsoluteRect()))||( (scrollBar!=NULL) && (gui.isMouseInside(Rect(getAbsolutePosition() + Point(getWidth(), 0), Size(12, getHeight()))))))))//&&(!isTopItem()))) // => main window! WHY? TODO
/*	{
		bool new_window = false;
		if(gui.getCurrentWindow() != this)
		{
			// current window is inside this window
			if( (gui.getCurrentWindow() == NULL)||
				(!gui.isMouseInside(gui.getCurrentWindow()->getAbsoluteRect()))||
   			    (gui.getCurrentWindow()->getAbsolutePosition() < getAbsolutePosition())||
			    (gui.getCurrentWindow()->getAbsoluteRect().getBottomRight() > getAbsoluteRect().getBottomRight()) ) 
			{
				makePufferInvalid();
				if(gui.getCurrentWindow()) {
					gui.getCurrentWindow()->makePufferInvalid();
				}
				new_window = true;
			}
		} else {
			new_window = true;
		}
		if(new_window)
		{
			gui.setCurrentWindow(this);
			gui.setWindowSelected(true);
		}
	}*/

	filledHeight = 0;
}



bool Window::fitItemToRelativeClientRect(const Rect& rect, const bool adjust)
{
	if(scrollBar)
	{
		if(scrollBar->getFirstItemY() == 0) {
			scrollBar->setFirstItemY(rect.getTop());
		}
		if(scrollBar->getLastItemY() < rect.getBottom()) {
			scrollBar->setLastItemY(rect.getBottom());
		}
	}

	if((rect.getLeft() >= getRelativeClientRectRightBound())||
//	   (rect.getTop()>=getRelativeClientRectLowerBound())||
	   (rect.getRight() < getRelativeClientRectLeftBound())||
	   (rect.getBottom() < getRelativeClientRectUpperBound())) {
		return false;
	}
/*		
	if(rect.getLeft()<getRelativeClientRectLeftBound()) 
		rect.setLeft(getRelativeClientRectLeftBound());
	if((rect.getRight()>getRelativeClientRectRightBound()))
		rect.setRight(getRelativeClientRectRightBound());*/
//  if(rect.y<clientArea.y) rect.y=clientArea.y;
//	if(rect.y+rect.height>clientArea.y+clientArea.height) rect.height=clientArea.y+clientArea.height-rect.y;
	if(adjust)
	{
		doAdjustments = true;
		if((rect.getBottom()>0) &&((unsigned int)(rect.getBottom())/*-getRelativeClientRectUpperBound()*/>filledHeight)) {
			filledHeight = rect.getBottom()/*-getRelativeClientRectUpperBound()*/;
		}
		if(filledHeight>getMaxHeight()) {
			filledHeight=getMaxHeight();
		}
	}
	if((rect.getTop() < getRelativeClientRectUpperBound())||
		(rect.getBottom() > getRelativeClientRectLowerBound())) {
		return false;
	}
	else {
		return true;
	}
}

bool Window::fitItemToAbsoluteClientRect(const Rect& rect, const bool adjust)
{
	if(scrollBar)
	{
		if(scrollBar->getFirstItemY() == 0) {
			scrollBar->setFirstItemY(rect.getTop() - getAbsoluteClientRectUpperBound());
		}
		if(scrollBar->getLastItemY() < rect.getBottom() - getAbsoluteClientRectUpperBound()) {
			scrollBar->setLastItemY(rect.getBottom() - getAbsoluteClientRectUpperBound());
		}
	}
	
	if((rect.getLeft() >= getAbsoluteClientRectRightBound())||
	   (rect.getTop() >= getAbsoluteClientRectLowerBound())||
	   (rect.getRight() < getAbsoluteClientRectLeftBound())||
	   (rect.getBottom() < getAbsoluteClientRectUpperBound())) {
		return false;
	}
/*	if(rect.getLeft() < getAbsoluteClientRectLeftBound()) 
		rect.setLeft(getAbsoluteClientRectLeftBound());
		
	if(rect.getRight() > getAbsoluteClientRectRightBound())
		rect.setRight(getAbsoluteClientRectRightBound());*/
//  if(rect.y<clientArea.y) rect.y=clientArea.y;
  //	  if(rect.y+rect.height>clientArea.y+clientArea.height) rect.height=clientArea.y+clientArea.height-rect.y;
	if(adjust)
	{

//		client als Panelklasse oder so machen

		doAdjustments = true;
		if((rect.getBottom() > getAbsoluteClientRectUpperBound())&&((unsigned int)(rect.getBottom() - getAbsoluteClientRectUpperBound()) > filledHeight)) {
			filledHeight = (unsigned int) (rect.getBottom() - getAbsoluteClientRectUpperBound());
		}
		if(filledHeight > getMaxHeight()) {
			filledHeight = getMaxHeight();
		}
	}
	if((rect.getTop() < getAbsoluteClientRectUpperBound())||
		(rect.getBottom() > getAbsoluteClientRectLowerBound())) {
		return false;
	}
	else {
		return true;
	}
}



void Window::drawWindow(DC* const dc) const
{
	BOOST_ASSERT(dc);

// draw outer border:
	dc->setPen(windowColors->getOuterBorderPen());//*gui.lookUpPen(OUTER_BORDER_PEN));
	dc->setBrush(windowColors->getBackgroundBrush());


	dc->DrawEdgedRoundedRectangle(Point(1, 1), getSize() - Size(2, 2), 6);
	
// draw inner border:
//	if(gui.getCurrentWindow() == this) {
		dc->setPen(windowColors->getHighlightedBorderPen());//*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
//	} else {
//		dc->setPen(windowColors->getBorderPen());//*gui.lookUpPen(INNER_BORDER_PEN));
//	} TODO

	dc->DrawEmptyEdgedRoundedRectangle(Point(3, 3), getSize() - Size(6, 6), 6);
}

void Window::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	drawWindow(dc);	
	Object::draw(dc);
}


bool Window::changedFlag=false;
//signed int Window::gotoHelpChapter=-1;

bool Window::needSaveBox = false;
bool Window::saveBoxCanceled = false;
bool Window::saveBoxDone = false;
std::string Window::saveBoxString = "";
SaveBoxParameter Window::saveBoxParameter;

