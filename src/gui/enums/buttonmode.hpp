#ifndef _GUI_ENUMS_BUTTONMODE_HPP
#define _GUI_ENUMS_BUTTONMODE_HPP

enum eButtonMode
{
	NO_BUTTON_MODE,
	STATIC_BUTTON_MODE, // stays in its position
	PRESS_BUTTON_MODE,  // returns to unpressed
	PUSH_BUTTON_MODE,   // calls several messages when being pressed
	TAB_BUTTON_MODE,
	TOP_TAB_BUTTON_MODE,
	CHECK_BUTTON_MODE, // no '3d effect', allows button to be set with 'check'
//	MENU_TAB_BUTTON_MODE,
	BOGRAPH_BUTTON_MODE, // just a rectangle, not rounded
	
	MAX_BUTTON_MODES
};

#endif // _GUI_ENUMS_BUTTONMODE_HPP