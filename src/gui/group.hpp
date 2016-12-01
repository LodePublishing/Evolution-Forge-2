#ifndef _GUI_GROUP_HPP
#define _GUI_GROUP_HPP

#include "title.hpp"
#include "enums/grouptype.hpp"

// simplified window class, maybe inheritate Window from Group...
class Group : public SDL_Object
{
	public:
		Group(SDL_Object* const group_parent, 
				const Rect& initial_rect, 
				const Size bottom_right_distance, 
				const eGroupType group_type, 
				const boost::shared_ptr<const WindowColors>& window_colors,
				const boost::shared_ptr<const Text>& title_text = boost::shared_ptr<const Text>(),
				bool draw_background = false, 
				const ePositionMode position_mode = DO_NOT_ADJUST);
		~Group();

		void draw(DC* const dc) const;
		void process();
		void reloadOriginalSize();

		void alignWidth(const Uint16 width);
		void calculateBoxSize();
	private:
		Title* title;

		unsigned int number;
		bool highlighted;
		eGroupType groupType;
		bool drawBackground;

		const boost::shared_ptr<const Pen> pen;
		const boost::shared_ptr<const Pen> highlightedPen;
		const boost::shared_ptr<const Brush> brush;
	
		Group(const Group& object);
		Group& operator=(const Group& object);
};

#endif // _GUI_GROUP_HPP

