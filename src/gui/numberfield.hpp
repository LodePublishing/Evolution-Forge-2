#ifndef _GUI_NUMBERFIELD_HPP
#define _GUI_NUMBERFIELD_HPP

#include "button.hpp"
#include "group.hpp"

#include "propertyfield.hpp"

class NumberField : public PropertyField
{
	public:
		NumberField(SDL_Object* const numberfield_parent, 
				const Rect& field_rect, 
				const Size distance_bottom_right, 
				const ePositionMode position_mode, 
				unsigned int number_min, 
				unsigned int number_max, 
				const boost::shared_ptr<const Text>& txt, 
				const boost::shared_ptr<const Text>& numberFormatText,
				const boost::shared_ptr<const Text>& tool_tip, 
				const boost::shared_ptr<const Color>& text_color,
				const boost::shared_ptr<const Font>& font,
				const boost::shared_ptr<const ButtonColors>& add_button_colors,
				const boost::shared_ptr<const ButtonColors>& sub_button_colors,
				unsigned int number_steps = 1, 
				unsigned int number = 0, 
				bool shift_right = false);
		~NumberField();
		const Object* checkToolTip(const Point& mouse) const;
		
		bool addClicked();
		bool subClicked();
		bool addRightClicked();
		bool subRightClicked();

		void reloadOriginalSize();
		
		unsigned int getNumber() const;
		void updateNumber(const unsigned int num);
		void process();
		void draw(DC* const dc) const;

		SDL_Object* checkHighlight(const Point& mouse);

	private:
		Button* const addButton;
		Button* const subButton;
		unsigned int number;
		const unsigned int min;
		const unsigned int max;
		const unsigned int steps;
		bool shiftRight;

		void updateNumberText(const std::string& text, const Size& size);

		NumberField& operator=(const NumberField& object);
		NumberField(const NumberField& object);
};

inline unsigned int NumberField::getNumber() const {
	return number;
}

inline bool NumberField::addClicked() {
	return addButton->isLeftClicked();
}

inline bool NumberField::subClicked() {
	return subButton->isLeftClicked();
}

inline bool NumberField::addRightClicked() {
	return addButton->isRightClicked();
}

inline bool NumberField::subRightClicked() {
	return subButton->isRightClicked();
}

#endif // _GUI_NUMBERFIELD_HPP

