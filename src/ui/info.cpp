#include "info.hpp"

#if 0

#include <sstream>

InfoWindow& InfoWindow::operator=(const InfoWindow& object)
{
	((Window)(*this)) = ((Window)object);
	bo = object.bo;
	bg = object.bg;
	unit = object.unit;
	delete text;
	text = new StaticText(*object.text);
	program = object.program;
	anarace = object.anarace;
	return(*this);
}

InfoWindow::InfoWindow(const InfoWindow& object) :
	Window((Window)object),
	bo(object.bo),
	bg(object.bg),
	unit(object.unit),
	text(new StaticText(*object.text)),
	program(object.program),
	anarace(object.anarace)
{ }

InfoWindow::InfoWindow(Object* info_parent, ANABUILDORDER* info_anarace):
	Window(info_parent, INFO_WINDOW_TITLE_STRING, theme.lookUpGlobalRect(INFO_WINDOW), theme.lookUpGlobalMaxHeight(INFO_WINDOW), NOT_SCROLLED),
	bo(NULL),
	bg(NULL),
	unit(0),
	text(new StaticText(this, "nothing", getRelativeClientRect(), Size(0,0), BRIGHT_TEXT_COLOR, SMALL_MIDDLE_NORMAL_FONT)),
	program(),
	anarace(info_anarace)
{ }

InfoWindow::~InfoWindow() {
	delete text;
}

void InfoWindow::assignAnarace(ANABUILDORDER* info_anarace) {
	anarace = info_anarace;
}

void InfoWindow::assignBg(const BoGraphEntry* info_bg) {
	bg = info_bg;
}

void InfoWindow::setProgram(const PROGRAM& info_program) {
	program = info_program;
}

void InfoWindow::resetData()
{
	bo = NULL;
	bg = NULL;
}

void InfoWindow::assignBo(const BoEntry* info_bo) {
	bo = info_bo;
}

void InfoWindow::process()
{
	if(!isShown()) 
		return;
	Window::process();
#if 0
//	IP = newIP;
	if(IP>MAX_LENGTH)
		return;
	std::ostringstream os;
	os.str("");
//	os << "$aaaaa$#";
	os << Object::theme.lookUpString(INFO_BUILD_STRING) << " $" 
	   << Object::theme.lookUpString((eString)(UNIT_TYPE_COUNT*anarace->getRace()+unit+UNIT_NULL_STRING)) << "$ "
	   << Object::theme.lookUpString(INFO_AS_SOON_AS_STRING) << " $&"
	   << Object::theme.lookUpString((eString)(anarace->getProgramSuccessType(IP)+SUCCESS_OK_STRING)) << "&$ ";
	if(anarace->getProgramSuccessUnit(IP))
		os << "&$" << Object::theme.lookUpString((eString)(UNIT_TYPE_COUNT*anarace->getRace()+anarace->getProgramSuccessUnit(IP)+UNIT_NULL_STRING)) << "$& " 
  		   << Object::theme.lookUpString(INFO_BECOMES_AVAILIBLE_STRING) << " ";
	// TODO
	os << Object::theme.lookUpString(INFO_AT_STRING) << " $"
		<< (*anarace->getMap())->getLocation(anarace->getProgramLocation(IP))->getName() << "$ "
		<< Object::theme.lookUpString(INFO_WHEN_STRING) << " "
		<< Object::theme.lookUpString(INFO_HAVING_STRING) << " &$" 
		<< (int)(anarace->getIPStatisticsHaveMinerals(IP*2+1)/100) << "$ " 
		<< Object::theme.lookUpString(INFO_MINERALS_STRING) << ",& &$" 
		<< (int)(anarace->getIPStatisticsHaveGas(IP*2+1)/100) << "$ "
		<< Object::theme.lookUpString(INFO_GAS_STRING) << ",& &$" 
		<< anarace->getIPStatisticsNeedSupply(IP*2+1) << "$/$" 
		<< anarace->getIPStatisticsHaveSupply(IP*2+1) << "$ "
		<< Object::theme.lookUpString(INFO_SUPPLY_STRING) << "& &["
		<< Object::theme.lookUpString(INFO_TIME_STRING) << ": $" 
		<< formatTime(anarace->getRealProgramTime(IP)) << "$]& #";
	text->updateText(os.str());
#endif
}

void InfoWindow::draw(DC* dc) const
{
	if(!isShown()) 
		return;
	if(bo)
	{
		dc->SetPen(Pen(*theme.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN)->GetColor(), 2, SOLID_PEN_STYLE));
		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2, 0) - Size(0, 3), bo->getAbsolutePosition() + Size(0, bo->getHeight() / 2) - Size(2, 0));
		dc->SetPen(Pen(*theme.lookUpPen(BIG_BUTTONS_PEN)->GetColor(), 1, SOLID_PEN_STYLE));
		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2+2, 0) - Size(0, 3), bo->getAbsolutePosition() + Size(0, bo->getHeight() / 2+2) - Size(2, 0));
		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2-1, 0) - Size(0, 3), bo->getAbsolutePosition() + Size(0, bo->getHeight() / 2) - Size(2, 1));
	}
	if(bg)
	{
		dc->SetPen(Pen(*theme.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN)->GetColor(), 2, SOLID_PEN_STYLE));
		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2, 0) - Size(0, 3), bg->getAbsolutePosition() + Size(bg->getWidth()/2, bg->getHeight()) - Size(2, 0));
		dc->SetPen(Pen(*theme.lookUpPen(BIG_BUTTONS_PEN)->GetColor(), 1, SOLID_PEN_STYLE));
		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2+2, 0) - Size(0, 3), bg->getAbsolutePosition() + Size(bg->getWidth()/2+2, bg->getHeight()) - Size(2, 0));
		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2+1, 0) - Size(0, 3), bg->getAbsolutePosition() + Size(bg->getWidth()/2, bg->getHeight()) - Size(2, 1));
		
//		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2+2, 0) - Size(0, 3), bo->getAbsolutePosition() + Size(0, bo->getHeight() / 2+2) - Size(2, 0));
//		dc->DrawLine(getAbsolutePosition() + Size(getWidth() / 2-1, 0) - Size(0, 3), bo->getAbsolutePosition() + Size(0, bo->getHeight() / 2) - Size(2, 1));
	}

	Window::draw(dc);
}

#endif