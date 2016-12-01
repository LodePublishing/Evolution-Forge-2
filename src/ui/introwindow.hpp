#ifndef _UI_INTRO_WINDOW_HPP
#define _UI_INTRO_WINDOW_HPP

#include <gui/window.hpp>
#include <gui/longtext.hpp>

class IntroWindow : public Window
{
	public:
		IntroWindow(Object* intro_parent);
		~IntroWindow();
		void process();
		void draw() const;
		void reloadOriginalSize();
		void init();
		const unsigned int getGameType() const;
		const bool isDone() const;
	private:
		bool was_initialized;
		LongText* text;
		Button* doneButton;
		unsigned int gameType;
		bool done;
};

inline const unsigned int IntroWindow::getGameType() const {
	return(gameType);
}

inline const bool IntroWindow::isDone() const {
	return(done);
}

#endif

