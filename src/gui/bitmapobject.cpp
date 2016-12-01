#include "bitmapobject.hpp"

BitmapObject::BitmapObject(SDL_Object* const bitmap_parent, 
				const Rect& bitmap_rect,
				const Size distance_bottom_right, 
				const boost::shared_ptr<const Bitmap>& bitmap, 
				const ePositionMode bitmap_position_mode) :
	Object(bitmap_parent, Rect(bitmap_rect.getTopLeft(), Size((*bitmap)->w, (*bitmap)->h)),  distance_bottom_right, bitmap_position_mode, NO_AUTO_SIZE),
	bitmap(bitmap),
	checked(false)
{
	setClipped();
	setDrawType(TRANSPARENT_OBJECT);
}

BitmapObject::~BitmapObject()
{}

void BitmapObject::reloadOriginalSize()
{
	setOriginalSize(getBitmapSize());
	Object::reloadOriginalSize();
	adjustSize(CHILD_WAS_CHANGED);
}

// Render button.  How it draws exactly depends on it's current state.
void BitmapObject::draw(DC* const dc) const
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
}

const Object* BitmapObject::checkToolTip(const Point& mouse) const {
	if( (!isShown()) || (!getAbsoluteRect().isTopLeftCornerInside(mouse))) {
 		return NULL;
	}
	return (Object*)this;
}

SDL_Object* BitmapObject::checkHighlight(const Point& mouse)
{
	if(!isShown()) {
		return NULL;
	}
	return Object::checkHighlight(mouse);
//	return (Object*)this; lol nein!
	
}

void BitmapObject::process()
{
	Object::process();
}

