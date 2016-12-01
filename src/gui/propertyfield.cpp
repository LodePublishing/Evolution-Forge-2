#include "propertyfield.hpp"

#pragma warning(push, 0)  
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)


PropertyField::PropertyField(SDL_Object* const propertyfield_parent, 
	const Rect& rect, 
	const Size distance_bottom_right, 
	const ePositionMode position_mode, 
	const unsigned int fieldDistance,
	const boost::shared_ptr<const Text>& propertyText,
	const boost::shared_ptr<const Text>& valueFormatText,
	const std::list<std::string>& valueList,
	const boost::shared_ptr<const Text>& tool_tip, 
	const boost::shared_ptr<const Color>& text_color,
	const boost::shared_ptr<const Font>& font) :
Object(propertyfield_parent, rect, distance_bottom_right, position_mode, AUTO_HEIGHT_CONST_WIDTH),
	propertyText(new StaticText(this, Rect(Point(0, 0), Size(0, 0)), Size(0, 0), text_color, font, propertyText, std::list<std::string>(), DO_NOT_ADJUST)),
	valueText(new StaticText(this, Rect(Point(fieldDistance, 0), Size(0, 0)), Size(0, 0), text_color, font, valueFormatText, valueList, DO_NOT_ADJUST))	
{
	if(tool_tip) {
		this->updateToolTip(tool_tip);
	}
	reloadOriginalSize();
}

PropertyField::~PropertyField()
{ 
	delete propertyText;
	delete valueText;
}

const Object* PropertyField::checkToolTip(const Point& mouse) const
{
	if( (!isShown()) || 
		( ((!propertyText)||(!propertyText->getAbsoluteRect().isTopLeftCornerInside(mouse))) && 
		(!valueText->getAbsoluteRect().isTopLeftCornerInside(mouse)))) {
			return NULL;
	}
	return (Object*)this;
}

void PropertyField::showValue(const bool show) {
	valueText->Show(show);
}

void PropertyField::updateValueParameters(const std::list<std::string>& valueList) {
	valueText->updateParameters(valueList);
}

SDL_Object* PropertyField::checkHighlight(const Point& mouse) {

	if(getAbsoluteRect().isTopLeftCornerInside(mouse)) {
		if(propertyText) {
			propertyText->setBrightnessHighlighted();
		}
		valueText->setBrightnessHighlighted();
	}

	return Object::checkHighlight(mouse);
}

void PropertyField::process()
{
	if(!isShown()) {
		return;
	}

	Object::process();
}

void PropertyField::draw(DC* const dc) const
{
	Object::draw(dc);
}
