#ifndef _UI_DEBUGWINDOW_HPP
#define _UI_DEBUGWINDOW_HPP

#if 0

#include <gui/window.hpp>
#include <gui/group.hpp>
#include <gui/framerate.hpp>

class DebugWindow : public Window
{
	public:
		DebugWindow(Object* parent_window);
		~DebugWindow();
		void draw() const;
		void process();
		void updateData(const std::list<unsigned int> percent_list, const unsigned int fps, const unsigned int gps);
		void reloadOriginalSize();
	private:
		unsigned int framesPerSecond;
		unsigned int generationsPerSecond;
		std::list<unsigned int> percentList;

		Group* tickGroup;
		StaticText* tickText[MAX_TICK_TYPES];
		
		StaticText* fpsText;
		StaticText* gpsText;
};

#endif

#endif // _UI_DEBUGWINDOW_HPP
