#include "background.hpp"

#include <guicore/color_storage.hpp>
#include <guicore/font_storage.hpp>
#include <misc/ids.hpp>

BackGround::BackGround(const boost::shared_ptr<const Bitmap>& bitmap, const boost::shared_ptr<const Text>& text) : 
	Object( NULL, Rect(Point(0,0), bitmap->getSize()), Size(), DO_NOT_ADJUST),
	bitmap(bitmap),
	text(new StaticText(this, Rect(), Size(), 
		ColorStorage::instance().get(IDS::FPS_TEXT_COLOR_ID),
		FontStorage::instance().get(IDS::SMALL_FONT_ID),
		text,
		boost::assign::list_of(""),
		BOTTOM_RIGHT))
{
	makePufferInvalid();
}

BackGround::~BackGround()
{ }

void BackGround::updateParameters(std::list<std::string> parameterList) 
{
	text->updateParameters(parameterList);	
}

void BackGround::reloadOriginalSize()
{
//	setOriginalSize(gui.getCurrentResolutionSize());
	setOriginalSize(bitmap->getSize());
	Object::reloadOriginalSize();
	adjustSize(NULL, CHILD_WAS_CHANGED, getSize());
}

void BackGround::updateBitmap(const boost::shared_ptr<const Bitmap>& bitmap) {
	if(this->bitmap != bitmap) {
		this->bitmap = bitmap;
		reloadOriginalSize();
		redrawWholeObject();
	}
}

void BackGround::process()
{
	Object::process();
}

void BackGround::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	dc->setBrightness(getBrightness());

	if(getClipRect() != Rect()) {
		dc->DrawBitmap(*bitmap, Point(), getClipRect());
	}
	else {
		dc->DrawBitmap(*bitmap, Point());
	}
	Object::draw(dc);

	// TODO evtl Versionsnummern an background übergeben!
	/*dc->setFont(gui.lookUpFont(SMALL_FONT));
	Size s = dc->getTextExtent(CORE_VERSION);	
	dc->setTextForeground(DC::toSDL_Color(100, 100, 100));
	dc->DrawText(CORE_VERSION, Point(dc->getMaxX() - s.getWidth() - 10, dc->getMaxY() - s.getHeight() - 2));
	*/	
	//gui.setColorTheme(gui.getTheme().getMainColorTheme());
	
#if 0
// ------ MOUSE DRAWING ------
		if(efConfiguration.isSoftwareMouse())
		{
//			SDL_ShowCursor(SDL_DISABLE);
			Point p = Object::mouse - Size(20,10);//Point(90, 140);
			dc->setFont(gui.lookUpFont(SMALL_ITALICS_BOLD_FONT));
			switch(Object::mouseType)
			{
				case 0://dc->DrawBitmap(*gui.lookUpBitmap(MOUSE_NONE), p);
					break;
				case 1:
//					dc->DrawBitmap(*gui.lookUpBitmap(MOUSE_LEFT), p);
					dc->setTextForeground(DC::toSDL_Color(179,0,0));
					dc->DrawText("Add a unit", p.x-50, p.y+2);
				break;
				case 2:
//					dc->DrawBitmap(*gui.lookUpBitmap(MOUSE_RIGHT), p);
					dc->setTextForeground(DC::toSDL_Color(0,177,188));
					dc->DrawText("Remove a unit", p.x+38, p.y+1);
				break;
				case 3:
//					dc->DrawBitmap(*gui.lookUpBitmap(MOUSE_BOTH), p);
					dc->setTextForeground(DC::toSDL_Color(179,0,0));
					dc->DrawText("Add a unit", p.x-50, p.y+2);
					dc->setTextForeground(DC::toSDL_Color(0,177,188));
					dc->DrawText("Remove a unit", p.x+38, p.y+1);
				break;
				default:toLog("error, mouseType out of range");break;
			}
		}
//		else
//			SDL_ShowCursor(SDL_ENABLE);
// ------ END MOUSE DRAWING ------
#endif
}


