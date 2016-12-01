	#ifndef _GUI_BUTTON_HPP
#define _GUI_BUTTON_HPP

#include "statictext.hpp"
#include "bitmapobject.hpp"
#include <guicore/buttoncolors.hpp>
#include <sdlwrap/sdl_object.hpp>

#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)

#include "enums/buttonmode.hpp"

#include <misc/uuid.hpp>

class Radio;

class Button : public Object
{
	public:

		Button(const boost::uuids::uuid id,
				SDL_Object* const button_parent, 
				const Rect& button_rect, 
				const Size& distance_bottom_right,
				const boost::shared_ptr<const ButtonColors>& button_colors, 
				const boost::shared_ptr<const Text>& button_text, 
				const boost::shared_ptr<const Text>& button_tooltip,
				const std::list<std::string>& parameterList,
				const boost::shared_ptr<const Bitmap>& button_bitmap,
				const eButtonMode button_mode,				
				const ePositionMode button_position_mode = DO_NOT_ADJUST, 
				const eAutoSize button_auto_size = NO_AUTO_SIZE);

		Button(SDL_Object* const button_parent, 
				const Rect& button_rect, 
				const Size& distance_bottom_right,
				const boost::shared_ptr<const ButtonColors>& button_colors, 
				const boost::shared_ptr<const Text>& button_text, 
				const boost::shared_ptr<const Text>& button_tooltip,
				const std::list<std::string>& parameterList,
				const boost::shared_ptr<const Bitmap>& button_bitmap,
				const eButtonMode button_mode,				
				const ePositionMode button_position_mode = DO_NOT_ADJUST, 
				const eAutoSize button_auto_size = NO_AUTO_SIZE);

		~Button();
		
		bool isLeftClicked();			// has it been selected (ie clicked on)
		bool isRightClicked();
		bool isCurrentlyPressed() const; // is the button depressed?
		bool isCurrentlyHighlighted() const; // is the mouse over this button?
		bool isCurrentlyActivated() const;
		
		void reloadOriginalSize();																																							
		void doHighlight(const bool high_light = true);	// force button to be highlighted

		void check(const bool is_checked = true);
		void forcePress(const bool click_message = true);	  // force button to get pressed
		void forceUnpress(const bool Rclick_message = true);

		void updateParameters(const std::list<std::string>& parameterList);



		void process(); // process messages, continue animation etc.
		const Object* checkToolTip(const Point& mouse) const;
		SDL_Object* checkHighlight(const Point& mouse);

		void mouseHasMoved();
		void frameReset();
		
		void mouseHasEnteredArea();
		void mouseHasLeftArea();
		void mouseLeftButtonPressed(const Point& mouse);
		void mouseLeftButtonReleased(const Point& mouse);
		void mouseRightButtonPressed(const Point& mouse);
		void mouseRightButtonReleased(const Point& mouse);

		static void resetButton();
		static Button* getCurrentButton();
		static bool isCurrentButtonPressed();
		static bool isCurrentButtonHasAlreadyLeft();
		static const Point& getMouseMovePoint();
		static bool isMoveByMouse();
		static void setMoveByMouse(const bool move_by_mouse = true);
		static void setCurrentButtonPressed(const bool current_button_pressed = true);
		static void setCurrentButtonHasAlreadyLeft(const bool button_has_already_left = true);
		static void setMouseMovePoint(const Point& mouse_move_point);
		static void setCurrentButton(Button* current_button);
		static bool isWasResetted();
		static void setWasResetted(const bool was_resetted = true);

		bool addKey(unsigned int key, unsigned int mod);
		
		void draw(DC* const dc) const;

		Radio* radio;

		void setAllowMoveByMouse(const bool allow_move_by_mouse = true);

		bool isBitmapButton() const;

	protected:
		StaticText* text;

	private:
		void init(const boost::shared_ptr<const Text>& button_text, const boost::shared_ptr<const Text>& button_tooltip, const std::list<std::string>& parameterList, const eButtonMode button_mode, const ePositionMode button_position_mode, const eAutoSize button_auto_size);

		static bool doClickedSound;
		static bool doClickSound;
		void setPressDepth(const unsigned int press);
		bool allowMoveByMouse;

		static bool wasResetted;
		static Point mouseMovePoint;
		static bool moveByMouse;
		static bool currentButtonPressed;
		static bool currentButtonHasAlreadyLeft;
		static Button* currentButton;
		static bool doMouseEnterSound;

		bool moved; // did this item move one pixel down (pressed)
		bool isOriginalPosition; // always false (not pressed) for non-static buttons
		bool wasPressed;

		unsigned int pressdepth;
		
		const boost::shared_ptr<const ButtonColors> buttonColors;	
		BitmapObject* const bitmap;
		
		unsigned int statusFlags;
		unsigned int frameNumber;
		unsigned int gradient;
		unsigned int oldGradient;
// Button flags

		static const unsigned int BF_DOWN = 1;
		static const unsigned int BF_JUST_PRESSED = 2;
		static const unsigned int BF_JUST_RELEASED = 4;
		static const unsigned int BF_LEFT_CLICKED = 8;
		static const unsigned int BF_RIGHT_CLICKED = 16;
		static const unsigned int BF_DOUBLE_CLICKED = 32;
		static const unsigned int BF_HIGHLIGHTED = 64;  // button is not highlighted (ie mouse is not above the item)
		static const unsigned int BF_JUST_HIGHLIGHTED = 128;  // button has just been highlighted, true for 1 frame
		static const unsigned int BF_REPEATS = 256;
		static const unsigned int BF_STATIC = 512;
		static const unsigned int BF_STATIC_PRESSED = 1024;
		static const unsigned int BF_NOT_CLICKABLE = 2048;
		static const unsigned int BF_IS_TAB = 4096;
		static const unsigned int BF_WAS_PRESSED = 8192; // button will be DOWN again, wenn mouse gets over button, without pressing the button again
		static const unsigned int BF_IS_RECTANGLE = 16384;
		static const unsigned int BF_IS_CHECKBUTTON = 32768; // no '3d effect', allows to be 'checked'
		static const unsigned int BF_IS_TOP_TAB = 65536; 
		// TODO irgendwie mit Zeit machen, dass z.B. nach 100ms die Taste automatisch losgelassen wird
	
		void updateText(const std::string& text, const Size& size);

	
		Button& operator=(const Button& object);		
		Button(const Button& object);
		eButtonAnimationPhase animationPhase;
};

inline bool Button::isWasResetted() {
	return wasResetted;
}

inline void Button::setWasResetted(const bool was_resetted) {
	wasResetted = was_resetted;
}

inline bool Button::isBitmapButton() const {
	return bitmap != NULL;
}

inline void Button::setAllowMoveByMouse(const bool allow_move_by_mouse) {
	allowMoveByMouse = allow_move_by_mouse;
}

inline Button* Button::getCurrentButton() {
	return currentButton;
}

inline bool Button::isCurrentButtonPressed() {
	return currentButtonPressed;
}

inline bool Button::isCurrentButtonHasAlreadyLeft() {
	return currentButtonHasAlreadyLeft;
}

inline void Button::setCurrentButtonPressed(const bool current_button_pressed) {
	currentButtonPressed = current_button_pressed;
}

inline void Button::setCurrentButtonHasAlreadyLeft(const bool button_has_already_left) {
	currentButtonHasAlreadyLeft = button_has_already_left;
}

inline const Point& Button::getMouseMovePoint() {
	return mouseMovePoint;
}

inline void Button::setMouseMovePoint(const Point& mouse_move_point) {
	mouseMovePoint = mouse_move_point;
}

inline bool Button::isMoveByMouse() {
	return moveByMouse;
}

inline void Button::setMoveByMouse(const bool move_by_mouse) {
	moveByMouse = move_by_mouse;
}

inline void Button::setCurrentButton(Button* current_button) {
	currentButton = current_button;
}
	
#endif // _GUI_BUTTON_HPP

