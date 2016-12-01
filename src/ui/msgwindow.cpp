#include "msgwindow.hpp"

MessageWindow::MessageWindow( Window* parent_window ) :
	Window( parent_window, MESSAGE_WINDOW_TITLE_STRING, theme.lookUpGlobalRect(MESSAGE_WINDOW), theme.lookUpGlobalMaxHeight(MESSAGE_WINDOW), SCROLLED, NO_AUTO_SIZE_ADJUST, Rect(0, 10, 1280, 1024) ),
	message()
{ }

MessageWindow::~MessageWindow()
{ 
	std::list<Message*>::iterator i = message.begin(); 
	while(i != message.end())
	{
		delete(*i);
		i = message.erase(i);
	}
}

void MessageWindow::process()
{
	if(!isShown()) 
		return;
	if(remainingMessages.size())
	{
		makePufferInvalid();
		for(std::list<std::string>::iterator i = Object::remainingMessages.begin(); i != Object::remainingMessages.end(); )
		{
			Message* my_message = new Message(getScrollBar(), Rect(Point(10, 20  /*message.size() * (FONT_SIZE+5)*/), Size(getClientRectWidth(), FONT_SIZE+5)), 1, *i, 100);
			message.push_front(my_message);
			i = remainingMessages.erase(i);
		}
		resetData();
//	addToProcessArray(this);
//	if(message.size() > 20)
//		message.pop_front();
//	moveScrollbarToBottom();
	}
	Window::process();
	getScrollBar()->checkBoundsOfChildren(getAbsoluteClientRectUpperBound()-15, getAbsoluteClientRectLowerBound());
}

void MessageWindow::draw() const
{
	drawWindow();
	dc->setFont(Object::theme.lookUpFont(LARGE_SHADOW_BOLD_FONT));
	Point point = Point(getRelativeClientRectPosition() + Size(10, getHeight()*11/16));
	dc->setTextForeground(DC::toSDL_Color(70, 70, 100));
	dc->DrawText("Evolution Forge", point);
	Object::draw();
}

void MessageWindow::resetData()
{
	int t =0;
	for(std::list<Message*>::iterator m=message.begin(); m!=message.end(); ++m)
	{
		(*m)->setOriginalRect(Rect(Point(10, 20 + t * (FONT_SIZE+5)), Size(getClientRectWidth(), FONT_SIZE+5)));
		t++;
	}
}

void MessageWindow::reloadOriginalSize()
{
	setOriginalRect(Object::theme.lookUpGlobalRect(MESSAGE_WINDOW));
	setMaxHeight(Object::theme.lookUpGlobalMaxHeight(MESSAGE_WINDOW));
	Window::reloadOriginalSize();
	resetData();
}


