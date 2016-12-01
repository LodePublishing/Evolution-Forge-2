#include "multilinetext.hpp"

#pragma warning(push, 0)  
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)

// boxed string!
MultiLineText::MultiLineText(SDL_Object* const mlt_parent, 
				const Rect& mlt_pos,
				const boost::shared_ptr<const Text>& text,
				const std::list<std::string>& parameterList,
				const boost::shared_ptr<const WindowColors> window_colors):
	BasicText(mlt_parent, mlt_pos, Size(), text, parameterList),
	windowColors(windowColors)
{
//	setDrawType(ANTI_ALIASED_OBJECT);
    text->connect(boost::bind(&MultiLineText::updateText, this, _1));
	reloadOriginalSize();
}

MultiLineText::~MultiLineText()
{ }

void MultiLineText::process() {
	BasicText::process();
}

void MultiLineText::updateText(const std::string& text) {
	drawText = text;
	makePufferInvalid();
	reloadOriginalSize();

	sig(text, getSize());
}

void MultiLineText::reloadOriginalSize() {
	Point p = Point(0,3);
	
	int width = 0;
	int index = 0;
	int old_index = 0;
	linebreaks.clear();
	linebreaks.push_back(std::pair<int, int>(0, 0));
	for(unsigned int i = 0; i < drawText.length(); i++) {
		int new_index = drawText.find_first_of(" ", old_index);
		Size text_size = windowColors->getFont()->getTextExtent(drawText.substr(index, new_index - index));
		if(text_size.getWidth() > getWidth()) {
			p.setY(p.getY() + text_size.getHeight() + 1);
			index = old_index;
			linebreaks.push_back(std::pair<int, int>(index, p.getY()));
		} else {
			old_index = new_index;
		}
	}
	setHeight(p.getY());
}


void MultiLineText::draw(DC* const dc) const {
	dc->setPen(windowColors->getBorderPen());
	dc->setBrush(windowColors->getBackgroundBrush());
	dc->DrawRectangle(Rect(Point(0,0), Size(6 + getWidth(), 6 + getHeight())));

	dc->setFont(windowColors->getFont());
	dc->setTextColor(windowColors->getTextColor());

	Point p = Point(0,3);
	
	for(std::vector<std::pair<int, int> >::const_iterator i = linebreaks.begin(); i != linebreaks.end(); ) {
		std::vector<std::pair<int, int> >::const_iterator j = i;
		i++;
		int index_end = i == linebreaks.end()?std::string::npos:i->first;
		p.setY(j->second);
		dc->DrawText(drawText.substr(j->first, i->first - j->first), p);
	}


	BasicText::draw(dc);
}
