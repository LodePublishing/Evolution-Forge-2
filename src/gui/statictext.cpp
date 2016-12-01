#include "statictext.hpp"
#include <sstream>

#pragma warning(push, 0)  
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)

// TODO KASTEN UM STATICTEXT
	//	dc->setBrush(*gui.lookUpBrush(WINDOW_FOREGROUND_BRUSH));
//	dc->setPen(*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN)); Kasten hinter Title... TODO StaticText
//	Size s = dc->getTextExtent(text);
//	Rect titleRect = Rect(Point(), s + Size(5, 0));
	
//	dc->DrawRectangle(titleRect);
//	titleRect.setTopLeft(titleRect.getTopLeft() + Point(2, 3));
//	dc->DrawText(text, titleRect.getTopLeft());


StaticText::StaticText(SDL_Object* const st_parent,
							 const Rect& st_pos, 
							 const Size& distance_bottom_right, 
							 const boost::shared_ptr<const Color>& color, 
							 const boost::shared_ptr<const Font>& font, 
							 const boost::shared_ptr<const Text>& text,
							 const std::list<std::string>& parameterList,
							 const ePositionMode position_mode) :
	BasicText(st_parent, st_pos, distance_bottom_right, text, parameterList, position_mode),
	color(color),
	font(font),
	endTextColor(color),
	gradient(0)
{ 
	text->connect(boost::bind(&StaticText::updateText, this, _1));
}

StaticText::~StaticText()
{ }

// register this in the text object signal
void StaticText::updateText(const std::string& text) {
	drawText = text;
	makePufferInvalid();
	setSize(font->getTextExtent(text) + Size(1+font->getSize()/6, font->getSize()/6)); // if it has shadow...

	sig(text, getSize());
}

const Object* StaticText::checkToolTip(const Point& mouse) const {
	if(isShown() && getAbsoluteRect().isTopLeftCornerInside(mouse)) {
		return (Object*)this;
	}
	return NULL;
}

void StaticText::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);
	BOOST_ASSERT(font);

	dc->setFont(font);

	dc->setGradient(gradient);
	dc->setTextColor(color);
	dc->setEndTextColor(endTextColor);
	dc->setBrightness(getBrightness());

		Point p = Point(0,3);
		/*bool done = false;
		for(unsigned int i = 0; i < text.size(); i++)
			// Schatten oder so? TODO
			if(text[i] == '&')
			{
				if(i > 0) {
					dc->DrawText(text.substr(0, i), p);
				}
				dc->setTextForeground(*gui.lookUpColor(FORCE_TEXT_COLOR));
				if(i + 1 < text.size()) {
					dc->DrawText(text.substr(i+1, 1), p + Size(dc->getTextExtent(text.substr(0,i)).getWidth(),0));
				}

//				if(highlight)
//					dc->setTextForeground(highlighted);
//				else
					dc->setTextForeground(normal);
				if((i+2) < text.size()) {
					dc->DrawText(text.substr(i+2, text.size() - i - 2), p + Size(dc->getTextExtent(text.substr(i+1, 1)).getWidth() + dc->getTextExtent(text.substr(0,i)).getWidth(), 0));	
				}
				done = true;
				break;
			}
		if(!done) {*/
			dc->DrawText(drawText, p);
		//}
	
	
	BasicText::draw(dc);
}

void StaticText::process()
{
	BasicText::process();

//	if( (isShown()) && (Rect(getAbsolutePosition(), getTextSize()).Inside(mouse )) )
//		setNeedRedrawMoved(); ??
}
