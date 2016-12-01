#ifndef _GUI_MENUENTRY_HPP
#define _GUI_MENUENTRY_HPP

#include "button.hpp"

class MenuEntry : public Button
{
	public:
		MenuEntry(SDL_Object* const menuentry_parent, 
			const Rect& rect, 
			const boost::shared_ptr<const ButtonColors>& button_colors, 
			const boost::shared_ptr<const Text>& menuText);
//TODO bitmaps... + Text
		~MenuEntry();
		void process();
		void draw(DC* const dc) const;

	private:
		MenuEntry& operator=(const MenuEntry& object);
		MenuEntry(const MenuEntry& object);
};

#endif // _GUI_MENUENTRY_HPP

