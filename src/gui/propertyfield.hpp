#ifndef _GUI_PROPERTYFIELD_HPP
#define _GUI_PROPERTYFIELD_HPP

#include "object.hpp"
#include "statictext.hpp"

class PropertyField : public Object
{
	public:
		PropertyField(SDL_Object* const propertyfield_parent, 
				const Rect& field_rect, 
				const Size distance_bottom_right, 
				const ePositionMode position_mode,
				const unsigned int fieldDistance,
				const boost::shared_ptr<const Text>& propertyText, 
				const boost::shared_ptr<const Text>& valueFormatText,
				const std::list<std::string>& valueList,
				const boost::shared_ptr<const Text>& tool_tip, 
				const boost::shared_ptr<const Color>& text_color,
				const boost::shared_ptr<const Font>& font);
		~PropertyField();

		const Object* checkToolTip(const Point& mouse) const;
				
		void process();
		void draw(DC* const dc) const;

		SDL_Object* checkHighlight(const Point& mouse);

		void showValue(const bool show);

		void updateValueParameters(const std::list<std::string>& valueList);

	protected:
		StaticText* const propertyText;
		StaticText* const valueText;
	private:

//		bool shiftRight;?

		PropertyField& operator=(const PropertyField& object);
		PropertyField(const PropertyField& object);
};

#endif // _GUI_PROPERTYFIELD_HPP
