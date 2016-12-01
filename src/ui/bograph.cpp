#include "bograph.hpp"

#if 0

BoGraphEntry::BoGraphEntry(const BoGraphEntry& object) :
	Button((Button)object),
	program(object.program)
{ }

BoGraphEntry& BoGraphEntry::operator=(const BoGraphEntry& object)
{
	((Button)*this) = (Button)object;
	program = object.program;
	return *this;
}

BoGraphEntry::BoGraphEntry(Object* entry_parent, const Rect bg_rect, const Size distance_bottom_right, const PROGRAM& bg_program) : // TODO
	Button(entry_parent, bg_rect, distance_bottom_right, "", (eButtonColorsType)(UNIT_TYPE_0_BUTTON), BOGRAPH_BUTTON_MODE, DO_NOT_ADJUST, SMALL_BOLD_FONT, NOTHING),
	program(bg_program)
{ }

BoGraphEntry::~BoGraphEntry()
{ }

void BoGraphEntry::process()
{
	Button::process();
}

void BoGraphEntry::draw(DC* const dc) const
{
	Button::draw(dc);
}

#endif