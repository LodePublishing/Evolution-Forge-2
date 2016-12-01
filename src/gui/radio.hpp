#ifndef _GUI_RADIO_HPP
#define _GUI_RADIO_HPP

#include "group.hpp"
#include "button.hpp"

#include <map>

#include <boost/uuid/uuid.hpp>

class Radio : public Group
{
	public:
		Radio(SDL_Object* const radio_parent,
				const boost::shared_ptr<const WindowColors>& window_colors,
				Rect initial_rect = Rect(0,0,0,0), 
				Size distance_bottom_right = Size(0,0), 
				const eGroupType group_type = ONE_COLOUMN_GROUP, 
				bool draw_background = false, 
				const ePositionMode position_mode = DO_NOT_ADJUST, 
				const boost::shared_ptr<const Text>& radio_title = boost::shared_ptr<const Text>());
		~Radio();
		void addButton(Button* const button);
		void removeButton(const boost::uuids::uuid button_id);
// TODO statictext für Titel...
// eigenes Titelobjekt?
		const boost::uuids::uuid getSelectedItemId() const;

		void leftButtonPressed(const boost::uuids::uuid id);
		void leftButtonReleased(const boost::uuids::uuid id); // allow release?		
//		void rightButtonPressed(const boost::uuids::uuid id);
//		void rightButtonReleased(const boost::uuids::uuid id); // allow release?		

		void process();
		void draw(DC* const dc) const;
		
		void forceUnpressAll();
		void updateIds();

	private:
		boost::uuids::uuid selectedItemId;
		boost::uuids::uuid activatedItemId;

		bool reorder;
		std::map<const boost::uuids::uuid, Button*> buttonMap; // TODO smart_ptr?
		
		Radio& operator=(const Radio& object);
		Radio(const Radio& object);
};

inline const boost::uuids::uuid Radio::getSelectedItemId() const {
	return selectedItemId;
}

inline void Radio::leftButtonPressed(const boost::uuids::uuid id) { // Unpress all except one
	activatedItemId = id;
}

inline void Radio::leftButtonReleased(const boost::uuids::uuid id) { // allow release? TODO
	activatedItemId = id;
}

/*
inline void Radio::rightButtonPressed(const boost::uuids::uuid id) {
//	leftButtonPressed(button);
}

inline void Radio::rightButtonReleased(const boost::uuids::uuid id) { // allow release?
//	leftButtonReleased(button);
}*/

#endif // _GUI_RADIO_HPP

