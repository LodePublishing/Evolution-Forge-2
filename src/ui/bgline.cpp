#include "bgline.hpp"

#if 0

BoGraphLine::BoGraphLine(Object* bg_parent, const Rect& initial_rect, const unsigned int bg_race, const unsigned int bg_facility, const unsigned int bg_line_height, const unsigned int bg_lines) :
	Object(bg_parent, initial_rect),
	boGraphList(),
	firstAvailible(0),
	race(bg_race),
	facility(bg_facility),
	lineHeight(bg_line_height),
	lines(bg_lines),
	facilityChanged(false),
	facilityName(new StaticText(this, GAME::lookUpUnitStringID(race, facility), Rect(2,2,0,0), Size(), BRIGHT_TEXT_COLOR, SMALL_SHADOW_BOLD_FONT, DO_NOT_ADJUST))
{
	if(lineHeight == 0)
		toErrorLog(" :`-(");
}

BoGraphLine::~BoGraphLine()
{
	delete facilityName;
	std::list<BoGraphEntry*>::iterator i = boGraphList.begin();
	while(i != boGraphList.end())
	{	
		delete(*i);
		i = boGraphList.erase(i);
	}
}

void BoGraphLine::resetData()
{
	facility = 0;
	lineHeight = 0;
	lines = 0;
	race = 0;
}

void BoGraphLine::process()
{
	if(facilityChanged)
	{
		facilityChanged = false;
		facilityName->updateText(GAME::lookUpUnitString(race, facility));
	}
	Object::process();
}

void BoGraphLine::draw() const
{
	if(firstAvailible > 0)
	{
		dc->setPen(*theme.lookUpPen(NULL_PEN));
		dc->setBrush(*theme.lookUpBrush(WINDOW_BACKGROUND_BRUSH));
		dc->DrawRectangle(Rect(Point(), Size(firstAvailible, getHeight())));
//			for(std::list<Not_Availible>::const_iterator i = notAvailibleList.begin(); i != notAvailibleList.end(); ++i)
//				dc->DrawRectangle(Rect(getAbsolutePosition() + Size(i->begin, 0), Size(i->end - i->begin, getHeight())));
	}
	dc->setPen(*theme.lookUpPen(INNER_BORDER_PEN));
	dc->setBrush(*theme.lookUpBrush(TRANSPARENT_BRUSH));
	dc->DrawRectangle(Rect(Point(), getSize()));

//	facilityName->Hide(); // TODO
	Object::draw();
//	facilityName->Show();
//	facilityName->draw();
}

void BoGraphLine::checkSelected(const unsigned int selected)
{
	for(std::list<BoGraphEntry*>::iterator entry = boGraphList.begin(); entry!=boGraphList.end(); ++entry)
		if((*entry)->getNumber() == selected)
		{
			(*entry)->resetGradient();
			return;
		}
}

/*	std::list<BoGraphEntry*>::iterator j = boGraphList.begin();
		while(j != boGraphList.end())
		{
			delete(*j);
			j = boGraphList.erase(j);
		}
*/

#endif