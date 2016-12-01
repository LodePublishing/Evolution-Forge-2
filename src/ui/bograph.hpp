#ifndef _UI_BOGRAPHENTRY_HPP
#define _UI_BOGRAPHENTRY_HPP

#if 0

#include <sdl/dc.hpp>
#include <ui/button.hpp>

#include "../core/program.hpp"


class BoGraphEntry : public Button
{
	public:
		BoGraphEntry(Object* entry_parent, const Rect bg_rect, const Size distance_bottom_right, const PROGRAM& bg_program);
		BoGraphEntry(const BoGraphEntry& object);
		BoGraphEntry& operator=(const BoGraphEntry& object);
		~BoGraphEntry();
		
		void process();
		void draw(DC* const dc) const;
		PROGRAM program;
	private:
};

#endif

#endif // _UI_BOGRAPHENTRY_HPP

