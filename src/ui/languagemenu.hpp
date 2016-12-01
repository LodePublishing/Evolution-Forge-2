#ifndef _UI_LANGUAGEMENU_HPP
#define _UI_LANGUAGEMENU_HPP

#if 0

#include "menu.hpp"

class LanguageMenu : public Menu
{
	public:
		LanguageMenu(Object* language_parent, const Rect language_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~LanguageMenu();
		void reloadOriginalSize();
		void process();
		void draw(DC* const dc) const;
};

#endif

#endif // _UI_LANGUAGEMENU_HPP

