#include "bgentry.hpp"

BoGraphEntry::BoGraphEntry(Object* entry_parent, const Rect bg_rect, const Size distance_bottom_right, const PROGRAM& bg_program, const unsigned int my_number) : // TODO
	Button(entry_parent, bg_rect, distance_bottom_right, (eButtonColorsType)(UNIT_TYPE_0_BUTTON), NULL_BITMAP, BOGRAPH_BUTTON_MODE, NULL_STRING, DO_NOT_ADJUST, SMALL_BOLD_FONT, NOTHING),
	program(bg_program),
	number(my_number)
{ }

BoGraphEntry::~BoGraphEntry()
{ }

void BoGraphEntry::process()
{
	Button::process();
//	if(checkForNeedRedraw())
//		getParent()->setNeedRedrawMoved(); // TODO
}

void BoGraphEntry::draw() const
{
	Button::draw();
}


