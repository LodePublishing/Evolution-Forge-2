#ifndef _GUI_MENU_HPP
#define _GUI_MENU_HPP

#include "menuentry.hpp"
#include "enums/menutype.hpp"

#include <guicore/objectsize.hpp>
#include <guicore/windowcolors.hpp>


class Menu : public Object
{
	public:
		// if all items to 'choose_menu' are used then it is a custom menu and reloadOriginalSize, updateItemPositions etc will not be called
		Menu(SDL_Object* const menu_parent, 
				const Rect& rect, 
				const Size distance_bottom_right, 
				const ePositionMode position_mode, 
				bool choose_menu, 
				const boost::shared_ptr<const ObjectSize>& object_size, 
				const boost::shared_ptr<const ButtonColors>& button_colors,
				const boost::shared_ptr<const WindowColors>& window_colors,
				std::vector<boost::shared_ptr<const Text> > strings,
				eMenuType menu_type = CUSTOM_MENU 
				);
		~Menu();
		void process();
		void draw(DC* const dc) const;
		Uint16 getHeight() const;
		signed int getPressedItem();
		signed int getMarkedItem() const;

		void forcePressItem(const unsigned int number);
		void close();
		void open();		
		bool isOpen() const;
		bool menuHasChanged() const;
		void setMenuHasChanged(const bool has_changed = true);
		void updateItemSizes(const Uint16 width);
		void updateItemPositions();
		void reloadOriginalSize();

	protected:
		void setMenuLevel(const unsigned int menu_level);
		std::list<MenuEntry*> menuEntries;
		unsigned int menuLevel;
		signed int pressedItem;
		signed int markedItem;
		Uint16 height;
		bool chooseMenu;

	private:
		Point p1, p2;
		bool menuChanged;
		const boost::shared_ptr<const ButtonColors> buttonColors;
		const boost::shared_ptr<const ObjectSize> objectSize;
		eMenuType menuType;
		const boost::shared_ptr<const WindowColors> windowColors;
	
		Menu& operator=(const Menu& object);
		Menu(const Menu& object);
};

inline bool Menu::menuHasChanged() const {
	return menuChanged;
}
	
inline signed int Menu::getMarkedItem() const {
	return markedItem;
}


#endif // _GUI_MENU_HPP

