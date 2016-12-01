#ifndef _GUI_TOOLTIP_HPP
#define _GUI_TOOLTIP_HPP

#include "multilinetext.hpp"

#include <guicore/objectsize.hpp>
#include <guicore/font.hpp>
#include <guicore/color.hpp>


class ToolTip : public MultiLineText
{
	public:
		ToolTip(SDL_Object* const parent_object, 
			const boost::shared_ptr<const Text>& text, 
			const std::list<std::string>& parameterList,
			const boost::shared_ptr<const WindowColors>& window_colors, 
			const boost::shared_ptr<const ObjectSize>& object_size);
		~ToolTip();
	
		void reloadOriginalSize();
		void object_info();
		void draw(DC* const dc) const;
		void process();

	private:
		Rect boxSize;
		boost::shared_ptr<const ObjectSize> objectSize;
	
		ToolTip& operator=(const ToolTip& object);
		ToolTip(const ToolTip& object);
};

#endif // _GUI_TOOLTIP_HPP

