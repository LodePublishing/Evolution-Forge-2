#include "progressbar.hpp"

#if 0

#include <gui/object.hpp>

void ProgressBar::draw(DC* const dc, const unsigned int dp)
{
	if(dp > 90)
		p = dp;
	else
		p += dp;

    dc->SetPen(Pen(Color(dc->GetSurface(), 50, 60, 155), 1, SOLID_PEN_STYLE));
    dc->SetBrush(Brush(Color(dc->GetSurface(), 30, 40, 100), SOLID_BRUSH_STYLE));

    dc->DrawEdgedRoundedRectangle(Rect(bar.GetLeft(), bar.GetTop(), bar.GetWidth() * p/ 100, bar.GetHeight()), 8);
	dc->updateScreen();
}

void ProgressBar::draw(DC* const dc, const unsigned int dp, const eString text)
{
    //dc->SetPen(Pen(Color(dc->GetSurface(), 255, 255, 255), 1, TRANSPARENT_PEN_STYLE));
  //  dc->SetBrush(Brush(Color(dc->GetSurface(), 0, 0, 0), SOLID_BRUSH_STYLE));
//    dc->DrawRectangle(Rect(bar.GetLeft(), bar.GetTop()+bar.GetHeight()+40+h*20, 350, 50));
    dc->SetFont(Object::theme.lookUpFont(MIDDLE_BOLD_FONT));
	dc->SetTextForeground(*Object::theme.lookUpColor(BRIGHT_TEXT_COLOR));
	dc->DrawText(Object::theme.lookUpString(text), Point(bar.GetLeft(), bar.GetTop()+bar.GetHeight()+50+h*20));
	dc->SetTextForeground(*Object::theme.lookUpColor(FORCE_TEXT_COLOR));
//	dc->DrawEmptyRectangle(bar.GetLeft()-2, bar.GetTop()+bar.GetHeight()+46+h*20, 425, 18);
	dc->DrawText("OK", Point(bar.GetLeft()+400, bar.GetTop()+bar.GetHeight()+50+h*20));
	draw(dc, dp);
	toLog(Object::theme.lookUpString(text));
	++h;
}

#endif