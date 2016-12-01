#include "menuentry.hpp"

#if 0

MenuEntry::MenuEntry(Object* menuentry_parent, const Rect rect, const eString unit) :
	Button(menuentry_parent, rect, Size(4, 2), unit, ADD_GOAL_BUTTON, PRESS_BUTTON_MODE, DO_NOT_ADJUST, SMALL_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH),
	color(NULL_COLOR)
{ }

MenuEntry::MenuEntry(Object* menuentry_parent, const Rect rect, const std::string& unit) :
	Button(menuentry_parent, rect, Size(4, 2), unit, ADD_GOAL_BUTTON, PRESS_BUTTON_MODE, DO_NOT_ADJUST, SMALL_BOLD_FONT, AUTO_HEIGHT_CONST_WIDTH),
	color(NULL_COLOR)
{ }

MenuEntry& MenuEntry::operator=(const MenuEntry& object)
{
	((Button)(*this)) = ((Button)object);
	color = object.color;
	return *this;
}

MenuEntry::MenuEntry(const MenuEntry& object) :
	Button((Button)object),
	color(object.color)
{ }

MenuEntry::~MenuEntry()
{ }

void MenuEntry::process()
{
	if(!isShown()) {
		return;
	}
	Button::process();
}

void MenuEntry::draw(DC* const dc) const
{
	if(!isShown()) {
		return;
	}
	Button::draw(dc);
}

void MenuEntry::setColor(const eColor entry_color)
{
	color = entry_color;
}

#endif