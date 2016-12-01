#ifndef _UI_ENDRUNDIALOG_HPP
#define _UI_ENDRUNDIALOG_HPP

#if 0

#include <string>

#include <ui/editfield.hpp>
#include <ui/checkbutton.hpp>


// simplified window class, maybe inheritate Window from EndRunDialog...
class EndRunDialog : public EditField
{
	public:
		EndRunDialog(Object* edit_parent, const std::string& name_proposal);
		~EndRunDialog();
		EndRunDialog(const EndRunDialog& object);
		EndRunDialog& operator=(const EndRunDialog& object);
		void process();
		void draw(DC* const dc) const;
		static std::string& getLastString();
	private:
		CheckButton* autoSaveRuns;
		static std::string lastString;
};

#endif

#endif // _UI_ENDRUNDIALOG_HPP

