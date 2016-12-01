#include "endrundialog.hpp"
#include "configuration.hpp"

// ISO-LEVEL 2 

EndRunDialog::EndRunDialog(Object* edit_parent, const std::string& name_proposal) :
	EditField(edit_parent, NULL, ENDRUN_DIALOG_TITLE_STRING, ENDRUN_QUESTION_STRING, ENDRUN_SAVE_AND_CONTINUE_STRING, ENDRUN_DONT_SAVE_AND_CONTINUE_STRING, name_proposal),
	autoSaveRuns(new CheckButton(this, Rect(Point(25, 80), Size(200, 15)), Size(5, 5), DO_NOT_ADJUST, SETTING_AUTO_SAVE_RUNS_STRING, SETTING_AUTO_SAVE_RUNS_TOOLTIP_STRING, efConfiguration.isAutoSaveRuns()))
{ }

EndRunDialog::~EndRunDialog()
{
	if(!isCanceled())
	{
		lastString = getString();
		efConfiguration.setAutoSaveRuns ( autoSaveRuns->isChecked() );
	}
	delete autoSaveRuns;
}

EndRunDialog::EndRunDialog(const EndRunDialog& object) :
	EditField((EditField)object),
	autoSaveRuns(new CheckButton(*object.autoSaveRuns))
{ }

EndRunDialog& EndRunDialog::operator=(const EndRunDialog& object)
{
	(EditField)(*this) = (EditField)object;
	delete autoSaveRuns;
	autoSaveRuns = new CheckButton(*object.autoSaveRuns);
	return *this;
}

std::string& EndRunDialog::getLastString()
{
	return lastString;
}

void EndRunDialog::process()
{
	EditField::process();
}

void EndRunDialog::draw(DC* const dc) const
{
	EditField::draw(dc);
}

std::string EndRunDialog::lastString="bo";

