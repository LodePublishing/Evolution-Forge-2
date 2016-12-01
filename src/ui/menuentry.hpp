#ifndef _UI_MENUENTRY_HPP
#define _UI_MENUENTRY_HPP

#include <gui/button.hpp>

class MenuEntry : public Button
{
	public:
		MenuEntry(const MenuEntry& object);
		MenuEntry(Object* menuentry_parent, const Rect rect, const eString unit);
		MenuEntry(Object* menuentry_parent, const Rect rect, const std::string& unit);
		~MenuEntry();
		MenuEntry& operator=(const MenuEntry& object);
		void process();
		void draw(DC* const dc) const;
		void setColor(const eColor entry_color);
	private:
		eColor color;
};

#endif // _UI_MENUENTRY_HPP

