#ifndef _UI_HELP_WINDOW_HPP
#define _UI_HELP_WINDOW_HPP

#if 0

#include <gui/window.hpp>
#include <gui/longtext.hpp>


class HelpWindow : public Window
{
	public:
		HelpWindow(Object* parent_window);
		~HelpWindow();
		void process();
		void draw() const;
		void reloadOriginalSize();
		void gotoChapter(unsigned int chapter);
		void goBack();
	private:
		eHelpChapter helpChapter; // ~~
		LongText* text;
		Button* indexButton;
		Button* backButton;
		std::list<eHelpChapter> lastChapter;
};

#endif

#endif // _UI_HELP_WINDOW_HPP

