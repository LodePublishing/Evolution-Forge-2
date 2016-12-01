#ifndef _UI_MESSAGE_HPP
#define _UI_MESSAGE_HPP

#include <gui/statictext.hpp>

class Message : public StaticText
{
	public:
		Message(Object* msg_parent, const Rect& rect, const unsigned int msg_type, const std::string& msg_string, const unsigned int color);
		~Message();
		void draw() const;
		void process();
		unsigned int type;
		unsigned int col;
};

#endif

