#include "background.hpp"

BackGround::BackGround(const Size& size, SDL_Surface* const bitmap) : 
	Object( NULL, Rect(Point(0,0), size), Size(), DO_NOT_ADJUST),
	bitmap(bitmap)
{
	makePufferInvalid();
}

BackGround::~BackGround()
{ }

void BackGround::reloadOriginalSize()
{
//	setOriginalSize(gui.getCurrentResolutionSize());
	Object::reloadOriginalSize();
}

void BackGround::updateBitmap(SDL_Surface* const bitmap) {
	if(this->bitmap != bitmap) {
		this->bitmap = bitmap;
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

	Object::draw(dc);
	if(bitmap)
	{
		SDL_Rect rc = Rect::createRect(0, 0, dc->getMaxX(), dc->getMaxY());
		dc->Blit(bitmap, rc);
	}
	else {
		dc->clearScreen();
	}

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


