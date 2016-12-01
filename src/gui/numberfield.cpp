#include "numberfield.hpp"

#pragma warning(push, 0)  
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)
// TODO: ui_objects arrangen! es nur in button zu benutzen bringt wenig...


// std::string&
	NumberField::NumberField(SDL_Object* const numberfield_parent, 
		const Rect& rect, 
		const Size distance_bottom_right, 
		const ePositionMode position_mode, 
		unsigned int number_min, 
		unsigned int number_max, 
		const boost::shared_ptr<const Text>& text,
		const boost::shared_ptr<const Text>& numberFormatText,
		const boost::shared_ptr<const Text>& tool_tip, 
		const boost::shared_ptr<const Color>& text_color,
		const boost::shared_ptr<const Font>& font,
		const boost::shared_ptr<const ButtonColors>& add_button_colors,
		const boost::shared_ptr<const ButtonColors>& sub_button_colors,
		unsigned int number_steps, 
		unsigned int number, 
		bool shift_right) :
	PropertyField(numberfield_parent, rect, distance_bottom_right, position_mode, 110, text, numberFormatText, boost::assign::list_of(boost::lexical_cast<std::string>(number)), tool_tip, text_color, font),
	addButton(new Button(this, Rect(Point(140, 1), Size(8, 8)), Size(0, 0), add_button_colors, boost::shared_ptr<const Text>(), boost::shared_ptr<const Text>(), std::list<std::string>(), boost::shared_ptr<const Bitmap>(), PRESS_BUTTON_MODE)),
	subButton(new Button(this, Rect(Point(150, 1), Size(8, 8)), Size(0, 0), sub_button_colors, boost::shared_ptr<const Text>(), boost::shared_ptr<const Text>(), std::list<std::string>(), boost::shared_ptr<const Bitmap>(), PRESS_BUTTON_MODE)),
	number(number),
	min(number_min),
	max(number_max),
	steps(number_steps),
	shiftRight(shift_right)
{
	updateNumber(number);
	reloadOriginalSize();

	valueText->connect(boost::bind(&NumberField::updateNumberText, this, _1, _2));
}

NumberField::~NumberField()
{
	delete addButton;
	delete subButton;
}

const Object* NumberField::checkToolTip(const Point& mouse) const
{
	if(isShown() && (addButton->getAbsoluteRect().isTopLeftCornerInside(mouse) || subButton->getAbsoluteRect().isTopLeftCornerInside(mouse))) {
		(Object*)this;
	}
	return PropertyField::checkToolTip(mouse);		
}

void NumberField::reloadOriginalSize()
{
	/*setOriginalSize(Size(gui.lookUpButtonWidth(LARGE_BUTTON_WIDTH), text->getTextSize().getHeight()));
		
	addButton->setOriginalPosition(Point(gui.lookUpButtonWidth(STANDARD_BUTTON_WIDTH) + 40, 1));
	subButton->setOriginalPosition(Point(gui.lookUpButtonWidth(STANDARD_BUTTON_WIDTH) + 50, 1));
	numberText->setOriginalPosition(Point(addButton->getRelativeLeftBound() - numberText->getTextSize().getWidth() - 5, 0));*/
	//TODO
	PropertyField::reloadOriginalSize();
}


void NumberField::updateNumber(const unsigned int num)
{
	if(number == num) {
		return;
	}
	number = num;
	valueText->updateParameters(boost::assign::list_of(boost::lexical_cast<std::string>(number)));
}

SDL_Object* NumberField::checkHighlight(const Point& mouse) {
	return PropertyField::checkHighlight(mouse);
}

void NumberField::process()
{
	if(!isShown()) {
		return;
	}

	PropertyField::process();

	if(subClicked())
	{
		if(number > min+(signed int)steps) {
			number-=steps;
		} else {
			number = min;
		}
		updateNumber(number);
	}

	if(addClicked())
	{
		if(number < max-(signed int)steps) {
			number += steps;
		} else {
			number = max;
		}
		updateNumber(number);
	}

	if(subRightClicked())
	{
		if(number > min + 10*(signed int)steps) {
			number -= 10*steps;
		} else {
			number = min;
		}
		updateNumber(number);
	}

	if(addRightClicked())
	{
		if((number < max - 10 * (signed int)steps) && (max > 10 * steps)) {
			number += 10*steps;
		} else {
			number = max;
		}
		updateNumber(number);
	}

	

//	if(/*(numberText->checkForNeedRedraw())||((text)&&(text->checkForNeedRedraw())))||*/(addButton->checkForNeedRedraw())||(subButton->checkForNeedRedraw()))
//	if(checkForNeedRedraw())
//		setNeedRedrawMoved(); TODO
}

void NumberField::draw(DC* const dc) const
{
	PropertyField::draw(dc);
	
	//if(shiftRight) {
	//	dc->DrawBitmap(gui.lookUpBitmap(LIST_BITMAP), Point());
	//} TODO
	
/*	dc->SetBrush(*gui.lookUpBrush(TRANSPARENT_BRUSH));
	dc->SetPen(*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
	Rect edge;
	edge.SetTopLeft(getAbsolutePosition()+Size(115,0));
	edge.SetWidth(58);
	edge.SetHeight(12);
	dc->DrawRoundedRectangle(edge, 2);*/
}

void NumberField::updateNumberText(const std::string& text, const Size& size) {
	valueText->setOriginalPosition(Point(addButton->getRelativeLeftBound() - size.getWidth() - 5, 0));
	//	setNeedRedrawMoved();
	//	adjustPositionAndSize(ADJUST_AFTER_CHILD_SIZE_WAS_CHANGED, numberText->getTextSize()); // TODO
}
