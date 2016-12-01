#ifndef _GUI_BITMAPOBJECT_HPP
#define _GUI_BITMAPOBJECT_HPP

#include "object.hpp"
#include <guicore/bitmap.hpp>

class BitmapObject : public Object
{
	public:
		BitmapObject(SDL_Object* const bitmap_parent, 
				const Rect& bitmap_rect, 
				const Size distance_bottom_right,
				const boost::shared_ptr<const Bitmap>& bitmap,
				const ePositionMode bitmap_position_mode = DO_NOT_ADJUST);
		~BitmapObject();
		
		void reloadOriginalSize();
		void process();
		const Object* checkToolTip(const Point& mouse) const;
		SDL_Object* checkHighlight(const Point& mouse);
		void object_info();
		void draw(DC* const dc) const;
		Uint16 getBitmapWidth() const;
		Uint16 getBitmapHeight() const;
		const Size getBitmapSize() const;

		void setChecked(const bool bitmap_checked = true);  // for buttons... 
		void setBitmap(const boost::shared_ptr<const Bitmap> bitmap);
		const boost::uuids::uuid getBitmapId() const;
	private:
		boost::shared_ptr<const Bitmap> bitmap;
		// TODO weiteres Bitmap* Feld für checked-Bitmaps!
		bool checked;
};

inline const boost::uuids::uuid BitmapObject::getBitmapId() const {
	return bitmap->getId();
}

inline void BitmapObject::setChecked(const bool bitmap_checked) {
	checked = bitmap_checked;
}

inline Uint16 BitmapObject::getBitmapWidth() const {
	return static_cast<Uint16>((*bitmap)->w);
}

inline Uint16 BitmapObject::getBitmapHeight() const {
	return static_cast<Uint16>((*bitmap)->h);
}

inline const Size BitmapObject::getBitmapSize() const {
	return Size(getBitmapWidth(), getBitmapHeight());
}

#endif // _GUI_BITMAP_HPP

