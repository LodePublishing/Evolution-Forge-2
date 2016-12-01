#ifndef _UI_PROGRESSBAR_HPP
#define _UI_PROGRESSBAR_HPP

#if 0

#include <sdl/dc.hpp>
#include <gui/theme.hpp>

class ProgressBar
{
	public:
		ProgressBar(const Rect& area):bar(area), p(1), h(0) {};
		~ProgressBar() {};
		void draw(DC* const dc, const unsigned int dp);
		void draw(DC* const dc, const unsigned int dp, const eString text);
	private:
		Rect bar;
		unsigned int p;
		unsigned int h;
};

#endif

#endif // _UI_PROGRESSBAR_HPP