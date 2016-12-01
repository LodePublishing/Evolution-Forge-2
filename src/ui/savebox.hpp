#ifndef _UI_SAVEBOX_HPP
#define _UI_SAVEBOX_HPP

#include <gui/window.hpp>
#include <gui/editfield.hpp>

// simplified window class, maybe inheritate Window from SaveBox...
class SaveBox : public Window
{
	public:
		SaveBox(Object* savebox_parent, const eString savebox_text=NULL_STRING, const eString description_text=NULL_STRING, const eString ok_string=SAVE_BOX_OK_STRING, const eString cancel_string=SAVE_BOX_CANCEL_STRING, const std::string& name_proposal="");
		SaveBox(Object* savebox_parent, SaveBoxParameter savebox_parameter);
		~SaveBox();

		void draw() const;
		void process();
		
		Object* checkToolTip();
		Object* checkHighlight();
		
		void reloadOriginalSize();
		
		const bool isCanceled() const;
		const bool isDone() const;
		void forceCancel();
		void forceDone();
		const std::string& getString() const;
	private:
		Button* OK_Button;
		Button* Cancel_Button;
		EditField* editField;

		SaveBox(const SaveBox& object);
		SaveBox& operator=(const SaveBox& object);
};



inline void SaveBox::forceCancel() {
	Cancel_Button->forcePress();
}

inline void SaveBox::forceDone() {
	OK_Button->forcePress();
}

inline const std::string& SaveBox::getString() const {
	return(editField->getText()->getString());
}

#endif

