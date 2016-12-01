#include "title.hpp"

#pragma warning(push, 0)
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#pragma warning(pop)

Title::Title(SDL_Object* const parent_object, 
			const boost::shared_ptr<const Text>& text, 
			const std::list<std::string>& parameterList,
			const boost::shared_ptr<const WindowColors>& windowColors):
	Object(parent_object),
	title(new StaticText(parent_object, Rect(0,0,0,0), Size(0,0), windowColors->getTextColor(), windowColors->getFont(), text, parameterList)),
	windowColors(windowColors)
{ 
	title->connect(boost::bind(&Title::updateTextAndSize, this, _1, _2));
}
	
Title::~Title()
{
	delete title;
}

void Title::updateParameters(const std::list<std::string>& parameterList) {
	title->updateParameters(parameterList);
}

void Title::updateTextAndSize(const std::string& text, const Size& size) {
	setSize(size);
}

void Title::draw(DC* const dc) const {
	BOOST_ASSERT(dc);

//		dc->setBrush(*gui.lookUpBrush(WINDOW_FOREGROUND_BRUSH));
//		dc->DrawRoundedRectangle(getAbsolutePosition() - Size(4, 5), getSize(), 4);

	// Point(2, 3)  ?
	Rect titleRect = Rect(Point(0,0), getSize() + Size(5,2));
	dc->setPen(windowColors->getBorderPen());
		//gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
	dc->setBrush(windowColors->getBackgroundBrush());
		//*gui.lookUpBrush(WINDOW_BACKGROUND_BRUSH));
	dc->DrawEdgedRoundedRectangle(titleRect, 2);

	Object::draw(dc);
}
/*
void Window::drawTitle(DC* const dc) const
{
	BOOST_ASSERT(dc);
	if(titleString == NULL) {
		return;
	}
	//TODO
	dc->setBrush(windowColors->getBackgroundBrush());//(WINDOW_FOREGROUND_BRUSH));
	dc->setPen(windowColors->getBorderPen()); //(INNER_BORDER_HIGHLIGHT_PEN));
	dc->setFont(windowColors->getFont());//(SMALL_BOLD_FONT));
	dc->setTextForeground(windowColors->getTextColor());//(TITLE_COLOR));

	std::string text;

// TODO StaticText einfuegen!
	if(titleParameter != "") {
		text = gui.lookUpFormattedString(titleString, titleParameter);
	} else {
		text = gui.lookUpResource(titleString);
	}
	
	Size s = dc->getTextExtent(text);
	Rect titleRect = Rect(Point(), s + Size(5, 0));
	
	dc->DrawRectangle(titleRect);
	titleRect.setTopLeft(titleRect.getTopLeft() + Point(2, 3));
	dc->DrawText(text, titleRect.getTopLeft());
}
*/