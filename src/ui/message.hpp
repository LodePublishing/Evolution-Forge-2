#ifndef _UI_MESSAGE_HPP
#define _UI_MESSAGE_HPP

#if 0

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

#endif // _UI_MESSAGE_HPP

