#ifndef _GUI_WINDOW_HPP
#define _GUI_WINDOW_HPP

#include "scrollbar.hpp"
//#include "panel.hpp"
#include "title.hpp"
#include "enums/autoadjust.hpp"
#include "enums/scrolled.hpp"

#include <guicore/windowcolors.hpp>

struct SaveBoxParameter
{
	Text* saveboxText;
	Text* descriptionText;
	Text* okString;
	Text* cancelString;

	std::string inputProposal;
};


class Window : public Object
{
	public:
		Window(SDL_Object* const window_parent, 
				const Rect rect, 
				const Uint16 max_height, 
				const boost::shared_ptr<const Text>& window_title_string, 
				const std::list<std::string>& parameterList,
				const boost::shared_ptr<const WindowColors>& windowColors,
				const eIsScrolled window_is_scrolled = NOT_SCROLLED, 
				const boost::shared_ptr<const ButtonColors>& scroll_up_button_colors = boost::shared_ptr<const ButtonColors>(),
				const boost::shared_ptr<const ButtonColors>& scroll_down_button_colors = boost::shared_ptr<const ButtonColors>(),
				const eIsAutoAdjust win_is_auto_adjust = NO_AUTO_SIZE_ADJUST, 
				const Rect win_client_area = Rect(0, 0, 1280, 1024) // TOO
				);
		~Window();
		// TODO protected machen (->datawindow)

		//Panel* clientPanel;
	
		void updateParameters(const boost::uuids::uuid languageId, const std::list<std::string>& parameterList);

	// returns position and size of the client area
		const Rect& getRelativeClientRect() const;
		const Rect getAbsoluteClientRect() const;
		const Point getRelativeClientRectPosition() const;
		const Point getAbsoluteClientRectPosition() const;
		Uint16 getClientRectHeight() const;
		Uint16 getClientRectWidth() const;
		const Size& getClientRectSize() const;
		Sint16 getRelativeClientRectUpperBound() const;
		Sint16 getRelativeClientRectLeftBound() const;
		Sint16 getRelativeClientRectLowerBound() const;
		Sint16 getRelativeClientRectRightBound() const;
		Sint16 getAbsoluteClientRectUpperBound() const;
		Sint16 getAbsoluteClientRectLeftBound() const;
		Sint16 getAbsoluteClientRectLowerBound() const;
		Sint16 getAbsoluteClientRectRightBound() const;
		Uint16 getClientTargetHeight() const;
		Uint16 getClientTargetWidth() const;

		void setRelativeClientRectPosition(const Point p);

		void process();

		void drawWindow(DC* const dc) const;
		
		void draw(DC* const dc) const;

		const Object* checkToolTip(const Point& mouse) const;
		SDL_Object* checkHighlight(const Point& mouse);

// 		reconfigure rectangles depending on current theme settings
//		void updateRectangles(const Rect rect, const Uint16 max_height);
		
		static bool getChangedFlag();
		static void setChangedFlag(const bool flag = true);
		static void changeAccepted();
		

		static unsigned int rectnumber;
		bool fitItemToRelativeClientRect(const Rect& rectangle, const bool adjust = false);
		bool fitItemToAbsoluteClientRect(const Rect& rectangle, const bool adjust = false);

		ScrollBar* getScrollBar() const;
		void setScrollBarPosition(const Point p);
		Uint16 getMaxHeight() const;

		void setMaxHeight(const Uint16 max_height);

		void wheelUp();
		void wheelDown();
		void moveScrollBarToTop();
		void moveScrollBarToBottom();

		void reloadOriginalSize();
//		static signed int gotoHelpChapter;
//		void addHelpButton(eHelpChapter help_chapter);

		static bool needSaveBox;
		static bool saveBoxCanceled;
		static bool saveBoxDone;
		static std::string saveBoxString;
		static SaveBoxParameter saveBoxParameter;

	protected:
		Window& operator=(const Window& object);
		Window(const Window& object);

	private:
	// do windows size changes smoothly		
		void adjustClientRect();
		Uint16 filledHeight;
		const boost::shared_ptr<const WindowColors> windowColors;
		bool doAdjustments;

// no set/get for title as this is unique and does not change
		Title* const title;
		
// client area
		Rect clientRect;
		Rect clientStartRect;
		Rect clientTargetRect;
// rectangle for max size of client area

		Rect originalClientRect;

		Uint16 maxHeight;

		void calculateClientRect();
//		void drawToolTip(DC* const dc, const Point p, const std::string* tip) const;

		eIsAutoAdjust isAutoAdjust;
// has this window a ScrollBar?
		eIsScrolled isScrollable;

		bool highlighted;

		static bool changedFlag; 
		
// this windows may have a scroll bar		
		ScrollBar* const scrollBar;
//		Button* helpButton;
//		eHelpChapter helpChapter;
	
};
		
inline void Window::setScrollBarPosition(const Point p) {
	scrollBar->setPosition(p);
}
		
inline void Window::setRelativeClientRectPosition(const Point p) 
{
	clientRect.setTopLeft(p);
	scrollBar->setStartY(p.getY());
}

inline Uint16 Window::getMaxHeight() const {
	return maxHeight;
}

inline ScrollBar* Window::getScrollBar() const {
	return scrollBar;
}

inline const Rect& Window::getRelativeClientRect() const {
	return clientRect;
}

inline const Point Window::getRelativeClientRectPosition() const {
	return clientRect.getTopLeft();
}

inline const Point Window::getAbsoluteClientRectPosition() const {
	return clientRect.getTopLeft()+getAbsolutePosition();
}

inline const Size& Window::getClientRectSize() const {
	return clientRect.getSize();
}

inline const Rect Window::getAbsoluteClientRect() const {
	return Rect(getAbsoluteClientRectPosition(), getClientRectSize());
}

inline Uint16 Window::getClientRectHeight() const {
	
	return clientRect.getHeight();
}

inline Uint16 Window::getClientRectWidth() const {
	return clientRect.getWidth();
}

inline Sint16 Window::getRelativeClientRectUpperBound() const {
	return clientRect.getTop();
}

inline Sint16 Window::getRelativeClientRectLeftBound() const {
	return clientRect.getLeft();
}

inline Sint16 Window::getRelativeClientRectLowerBound() const {
	return clientRect.getBottom();
}

inline Sint16 Window::getRelativeClientRectRightBound() const {
	return clientRect.getRight();
}

inline Sint16 Window::getAbsoluteClientRectUpperBound() const {
	return getAbsoluteClientRectPosition().getY();
}

inline Sint16 Window::getAbsoluteClientRectLeftBound() const {
	return getAbsoluteClientRectPosition().getX();
}

inline Sint16 Window::getAbsoluteClientRectLowerBound() const {
	return getAbsoluteClientRectPosition().getY() + getClientRectHeight() - 1; // TODO?
}

inline Sint16 Window::getAbsoluteClientRectRightBound() const {
	return getAbsoluteClientRectPosition().getX() + getClientRectWidth() - 1;
}

inline Uint16 Window::getClientTargetWidth() const {
	return clientTargetRect.getWidth();
}

inline Uint16 Window::getClientTargetHeight() const {
	return clientTargetRect.getHeight();
}

inline void Window::setChangedFlag(const bool flag) {
	changedFlag = flag;
}

inline bool Window::getChangedFlag() {
	return changedFlag;
}

inline void Window::changeAccepted() {
	changedFlag = false;
}

inline void Window::setMaxHeight(const Uint16 max_height) {
	maxHeight = max_height;
}




#endif // _GUI_WINDOW_HPP

