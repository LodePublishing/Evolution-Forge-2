#include "menuentry.hpp"

MenuEntry::MenuEntry(SDL_Object* const menuentry_parent, 
						   const Rect& rect, 
						   const boost::shared_ptr<const ButtonColors>& button_colors, 
						   const boost::shared_ptr<const Text>& menuText) :
	Button(menuentry_parent, rect, Size(4, 2), button_colors, menuText, std::list<std::string>(), boost::shared_ptr<const Text>(), PRESS_BUTTON_MODE, DO_NOT_ADJUST, AUTO_HEIGHT_CONST_WIDTH)
{ }


//MenuEntry::MenuEntry(SDL_Object* const menuentry_parent, const Rect rect, const eButtonColorsType button) :
//	Button(menuentry_parent, rect, Size(4, 2), button, NULL_BITMAP, PRESS_BUTTON_MODE, NULL_STRING"), // TODO
//	color(NULL_COLOR)
//{}

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
	Button::draw(dc);
}
