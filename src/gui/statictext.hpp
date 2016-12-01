#ifndef _GUI_STATICTEXT_HPP
#define _GUI_STATICTEXT_HPP

#include "basictext.hpp"
#include <guicore/font.hpp>
#include <guicore/color.hpp>

class StaticText : public BasicText
{
	public:
		StaticText(SDL_Object* const st_parent, 
				const Rect& st_pos, 
				const Size& distance_bottom_right, 
				const boost::shared_ptr<const Color>& st_color, 
				const boost::shared_ptr<const Font>& st_font, 
				const boost::shared_ptr<const Text>& st_text,
				const std::list<std::string>& parameterList,
				const ePositionMode position_mode = HORIZONTALLY_CENTERED);
		~StaticText();
		
		const Object* checkToolTip(const Point& mouse) const;
		SDL_Object* checkHighlight(const Point& mouse);
			
		void draw(DC* const dc) const;
		void process();

		void setEndTextColor(const boost::shared_ptr<const Color>& endTextColor);
		void setGradient(const unsigned int gradient);

	protected:
		void updateText(const std::string& text);
	
	private:
		const boost::shared_ptr<const Font> font;
		const boost::shared_ptr<const Color> color;
		boost::shared_ptr<const Color> endTextColor;
		unsigned int gradient;

		StaticText& operator=(const StaticText& object);
		StaticText(const StaticText& object);
};


inline void StaticText::setEndTextColor(const boost::shared_ptr<const Color>& endTextColor) {
	this->endTextColor = endTextColor;
}

inline void StaticText::setGradient(const unsigned int gradient) {
	this->gradient = gradient;
}

inline SDL_Object* StaticText::checkHighlight(const Point& mouse) {
	return SDL_Object::checkHighlight(mouse);
}

#endif // _GUI_STATICTEXT_HPP

