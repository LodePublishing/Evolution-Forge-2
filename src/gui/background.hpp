#ifndef _GUI_BACKGROUND_HPP
#define _GUI_BACKGROUND_HPP

#include "object.hpp"
#include <guicore/bitmap.hpp>
#include <gui/statictext.hpp>

class BackGround : public Object
{
	public:
		BackGround(const boost::shared_ptr<const Bitmap>& bitmap, const boost::shared_ptr<const Text>& text);
		~BackGround();

		void updateParameters(std::list<std::string> parameter);

		void reloadOriginalSize();
		void process();
		void draw(DC* const dc) const;

		void updateBitmap(const boost::shared_ptr<const Bitmap>& bitmap);
		boost::uuids::uuid getBitmapId() const;

	private:
		boost::shared_ptr<const Bitmap> bitmap;
		boost::scoped_ptr<StaticText> text;
};

inline boost::uuids::uuid BackGround::getBitmapId() const {
	return bitmap->getId();
}

#endif // _GUI_BACKGROUND_HPP

