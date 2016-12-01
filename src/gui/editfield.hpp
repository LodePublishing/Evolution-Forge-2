#ifndef _GUI_EDITFIELD_HPP
#define _GUI_EDITFIELD_HPP

#include "button.hpp"

// TODO: Editfield aus Button und Text bestehen lassen... wegen Group (die Box) und wegen besserer Uebersicht (damits net immer ein extra STaticText braucht)

class EditField : public Object
{
	public:
		EditField(SDL_Object* const edit_parent, 
				const Rect& edit_rect, 
				const Size& edit_size, 
				const boost::shared_ptr<const Font>& st_font, 
			    const boost::shared_ptr<const Color>& text_color,
			    const boost::shared_ptr<const ButtonColors>& button_colors,
				const boost::shared_ptr<const Text>& formatText,
				const ePositionMode position_mode, 
				const boost::shared_ptr<const Text>& description_text, 
				const std::string& initialText);

		~EditField();

		void draw(DC* const dc) const;
		void process();
		
		const Object* checkToolTip(const Point& mouse) const;
		SDL_Object* checkHighlight(const Point& mouse);
	
		bool addKey(unsigned int key, unsigned int mod);
				
		void addChar(char a);
		void removeCharBackspace();
		void removeCharDelete();
		void enterWasPressed();
		void escapeWasPressed();
		bool done() const;
		bool canceled() const;

		void resetData();

		void moveLeft();
		void moveRight();

	private:
		unsigned int position;
		unsigned int ani;
		bool pressedEnter;
		bool pressedEscape;

		Button* const editField;
		StaticText* const descriptionText;

		std::string text;

		EditField(const EditField& object);
		EditField& operator=(const EditField& object);
};

inline void EditField::enterWasPressed() {
	pressedEnter = true;
}

inline void EditField::escapeWasPressed() {
	pressedEscape = true;
}

inline bool EditField::done() const {
	return pressedEnter;
}

inline bool EditField::canceled() const {
	return pressedEscape;
}

inline const Object* EditField::checkToolTip(const Point& mouse) const {
	return Object::checkToolTip(mouse);
}


#endif // _GUI_EDITFIELD_HPP

