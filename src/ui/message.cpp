#include "message.hpp"

#if 0

Message::Message(Object* msg_parent, const Rect& rect, const unsigned int msg_type, const std::string& msg_string, const unsigned int msg_color) :
	StaticText(msg_parent, msg_string, rect, Size(0,0), WINDOW_TEXT_COLOR, SMALL_BOLD_FONT, DO_NOT_ADJUST), 
	type(msg_type),
	col(msg_color)
{ }

Message::~Message()
{ }


void Message::process()
{
	if(type>0)
	{
		if(col>5) 
		{
			col -= col/5+1;
			makePufferInvalid();
		}
		else col=0;
	}
}

void Message::draw() const
{
	const_cast<Message*>(this)->setTemporaryColor(dc->doColor(col+155, col+155, col+155));
	StaticText::draw();
}

#endif