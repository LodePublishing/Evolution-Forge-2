#ifndef _GUI_SCROLLBAR_HPP
#define _GUI_SCROLLBAR_HPP

#include "button.hpp"

#include <guicore/windowcolors.hpp>

#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)


#define MAX_SCROLL_VALUE 10000

class Window;

class ScrollBar : public Object
{
	public:
		ScrollBar(SDL_Object* const scroll_parent, /*const Rect& clientrect?*/ 
			const Sint16 start_y, 
			const Uint16 max_height,
			const boost::shared_ptr<const ButtonColors>& up_button_colors,
			const boost::shared_ptr<const ButtonColors>& down_button_colors,
			const boost::shared_ptr<const WindowColors>& window_colors,
			bool scroll_hideable = false);
		~ScrollBar();

		void process(); // process messages, continue animation etc.
		void draw(DC* const dc) const;

		void moveUp();
		void moveDown();
		void moveToTop();
		void moveToBottom();

		void setClientHeight(const Uint16 height);
		void setClientTargetHeight(const Uint16 height);

		void setStartY(const Sint16 start_y);
		
		void setFirstItemY(const Sint16 first_item_y);
		void setLastItemY(const Sint16 last_item_y);
		Sint16 getFirstItemY() const;
		Sint16 getLastItemY() const;

		void checkBoundsOfChildren(const Sint16 upper_bound, const Sint16 lower_bound);

		SDL_Object* checkHighlight(const Point& mouse);
	protected:
	private:
		Sint16 firstItemY;
		Sint16 lastItemY;

		Sint16 startY;
		
		Button* const add;
		Button* const sub;

		const boost::shared_ptr<const WindowColors> windowColors;

		const bool hideable; // hides if total height is smaller maxheight
		const Uint16 maxHeight;

		Sint16 internalScrollY;
		Uint16 internalHeight;
		Sint16 currentScrollY;
		Sint16 targetScrollY;
		Uint16 barHeight;
		
		Uint16 clientHeight;
		Uint16 clientTargetHeight;
		Uint16 totalHeight;		

		ScrollBar& operator=(const ScrollBar& object);
		ScrollBar(const ScrollBar& object);
};

inline void ScrollBar::setStartY(const Sint16 start_y) {
	BOOST_ASSERT(start_y <= MAX_SCROLL_VALUE);
	startY = start_y;
}

inline void ScrollBar::setFirstItemY(const Sint16 first_item_y) 
{
	BOOST_ASSERT(first_item_y <= MAX_SCROLL_VALUE);
	firstItemY = first_item_y;
}

inline void ScrollBar::setLastItemY(const Sint16 last_item_y) 
{
	BOOST_ASSERT(last_item_y <= MAX_SCROLL_VALUE);

	lastItemY = last_item_y;
}

inline Sint16 ScrollBar::getFirstItemY() const 
{
	BOOST_ASSERT(firstItemY <= MAX_SCROLL_VALUE);

	return firstItemY;
}

inline Sint16 ScrollBar::getLastItemY() const 
{
	BOOST_ASSERT(lastItemY <= MAX_SCROLL_VALUE);

	return lastItemY;
}

#endif // _GUI_SCROLLBAR_HPP

