#ifndef _GUI_OBJECT_HPP
#define _GUI_OBJECT_HPP

#include <sdlwrap/sdl_object.hpp>
#include <sdlwrap/enums/positionmode.hpp>
#include <sdlwrap/enums/autosize.hpp>
#include <sdlwrap/dc.hpp>

#include <lang/text.hpp>

#include <geometry/rect.hpp>
#include <string>
#include <list>

class Object;

class Object : public SDL_Object
{
	public:
		Object(SDL_Object* const parent_object, 
				const Rect& relative_rect = Rect(0, 0, 0, 0), 
				const Size& distance_bottom_right = Size(0, 0), 
				const ePositionMode position_mode = DO_NOT_ADJUST, 
				const eAutoSize auto_size = NOTHING);

		virtual ~Object(); 
		
		void draw(DC* const dc) const;
		
// returns the object the mouse cursor is currently over
		virtual const Object* checkToolTip(const Point& mouse) const;

		void process();
		void resetData();
		
		void updateToolTip(const boost::shared_ptr<const Text>& toolTipText);
		void updateToolTipParameter(const boost::uuids::uuid languageId, const std::list<std::string>& toolTipParameter);

		bool hasToolTip() const;
				
		virtual bool addKey(unsigned int key, unsigned int mod);

		bool isClipped() const;
		const Rect& getClipRect() const;
		void setClipRect(const Rect& rect);
		void setClipped(const bool clipped = true);

		void setBrightness(const signed int brightness);
		void setBrightnessHighlighted();
		signed int getBrightness() const;
		void resetBrightness();

	private:
		boost::shared_ptr<const Text> toolTipText;
		std::list<std::string> toolTipStringList;

		bool clipped;
		Rect clipRect;
		short int brightness;		
};

inline void Object::updateToolTip(const boost::shared_ptr<const Text>& toolTipText) {
	this->toolTipText = toolTipText;
}

inline void Object::setBrightness(const signed int brightness) {
	if(this->brightness != brightness) {
		this->brightness = brightness;
		makePufferInvalid();
	}
}

inline void Object::setBrightnessHighlighted() {
	if(brightness != 128) {
		this->brightness = 128;
		makePufferInvalid();
	}
}

inline void Object::resetBrightness() {
	if(brightness != 0)
	{
		brightness = 0;
		makePufferInvalid();
	}
}

inline signed int Object::getBrightness() const {
	return brightness;
}

inline void Object::setClipped(const bool clipped) {
	this->clipped = clipped;
}

inline bool Object::isClipped() const {
	return clipped;
}

inline const Rect& Object::getClipRect() const {
	return clipRect;
}

inline void Object::setClipRect(const Rect& rect) {
	this->clipRect = rect;
}

inline bool Object::hasToolTip() const {
	return toolTipText;
}


#endif // _GUI_OBJECT_HPP

