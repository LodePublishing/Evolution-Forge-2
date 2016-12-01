#ifndef _UI_MSGWINDOW_HPP
#define _UI_MSGWINDOW_HPP

#if 0

#include <gui/window.hpp>
#include "message.hpp"

class MessageWindow:public Window
{
	public:
		MessageWindow(Window* parent_window);
		~MessageWindow();
		void resetData();
		void process();
		void draw() const;
		void reloadOriginalSize();
	private:
		std::list<Message*> message;
};

#endif

#endif // _UI_MSGWINDOW_HPP

