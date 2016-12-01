#ifndef _SDL_DC_HPP
#define _SDL_DC_HPP

#include <sstream>

#define PRESSED_BRIGHTEN 50
#define PRESSED_DARKEN 130
#define PRESSED_NORMAL 90
#define NOT_PRESSED_DARKEN 60
#define NOT_PRESSED_BRIGHTEN 140

#define DC_MAX_CHANGED_RECTANGLES 200
 
#include <math.h>
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include <geometry/rect.hpp>

#include <guicore/pen.hpp>
#include <guicore/brush.hpp>
#include <guicore/enums/brushstyle.hpp>
#include <guicore/font.hpp>

#include "enums/bitdepth.hpp"

#include <misc/singleton.hpp>

#include <guicore/surface.hpp>

#pragma warning(push, 0)
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>
#pragma warning(pop)

typedef struct tColorRGBA {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} tColorRGBA;

typedef struct tColorY {
	Uint8 y;
} tColorY;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define SDL_rmask 0xff000000
#define SDL_gmask 0x00ff0000
#define SDL_bmask 0x0000ff00
#define SDL_amask 0x00000000
#else
#define SDL_rmask 0x000000ff
#define SDL_gmask 0x0000ff00
#define SDL_bmask 0x00ff0000
#define SDL_amask 0x00000000
#endif


class DC : public Singleton<DC>
{
	friend class Singleton<DC>;
	public:
		DC();
		~DC();
		bool initSDL(const Size& current_resolution, const eBitDepth bit_depth, const Uint32 nflags, const Uint32 initflags);
		
		static const char* getVersion();

		operator SDL_Surface*() const;
		SDL_Surface* operator->() const;
		SDL_Surface* getSurface() const;

		bool isSurfacePuffered() const;

		const Size getSize() const;
		Uint16 w() const;
		Uint16 h() const;

		bool valid() const;
		Uint32 flags() const;

		bool setResolution(const Size current_resolution);
		bool setBitDepth(const eBitDepth bit_depth);
		bool setScreen(const Size current_resolution, const eBitDepth bit_depth, const Uint32 nflags);

		eBitDepth getBitDepth() const;
		unsigned int getBits() const;

		Uint16 pitch() const;
		void *pixels();
		void const* pixels() const;
		const struct private_hwdata *hwdata() const;

		bool Lock() const { return Surface::Lock(surface); }
		void Unlock() const { Surface::Unlock(surface); }

		bool setColorKey(const Uint32 flag, const Color key) const;
		bool setAlpha(const Uint32 flag, const Uint8 alpha) const;
		void updateScreen();
		
		void Blit(SDL_Surface* src, SDL_Rect& dstrect) const;
		
		void clearScreen();
		
		bool SaveBMP(const std::string& file) const;

		bool setFullScreen(const bool fullscreen = true);
		bool isFullScreen() const;

	
		void setBrush(const boost::shared_ptr<const Brush>& brush);
		void setDarkBrush(const boost::shared_ptr<const Brush>& darkBrush);
		void setBrightBrush(const boost::shared_ptr<const Brush>& brightBrush);
		void setPen(const boost::shared_ptr<const Pen>& pen);
		void setDarkPen(const boost::shared_ptr<const Pen>& darkPen);
		void setBrightPen(const boost::shared_ptr<const Pen>& brightPen);
		void setPressedPen(const boost::shared_ptr<const Pen>& pressedPen);
		void setDarkPressedPen(const boost::shared_ptr<const Pen>& darkPressedPen);
		void setBrightPressedPen(const boost::shared_ptr<const Pen>& brightPressedPen);
		void setTextColor(const boost::shared_ptr<const Color>& textColor);

		void setEndBrush(const boost::shared_ptr<const Brush>& endBrush);
		void setEndDarkBrush(const boost::shared_ptr<const Brush>& endDarkBrush);
		void setEndBrightBrush(const boost::shared_ptr<const Brush>& endBrightBrush);
		void setEndPen(const boost::shared_ptr<const Pen>& endPen);
		void setEndDarkPen(const boost::shared_ptr<const Pen>& endDarkPen);
		void setEndBrightPen(const boost::shared_ptr<const Pen>& endBrightPen);
		void setEndPressedPen(const boost::shared_ptr<const Pen>& endPressedPen);
		void setEndDarkPressedPen(const boost::shared_ptr<const Pen>& endDarkPressedPen);
		void setEndBrightPressedPen(const boost::shared_ptr<const Pen>& endBrightPressedPen);
		void setEndTextColor(const boost::shared_ptr<const Color>& endTextColor);

		void setFont(const boost::shared_ptr<const Font>& font);

		Color getBrushColor() const;
		Color getDarkBrushColor() const;
		Color getBrightBrushColor() const;
		Color getPenColor() const;
		Color getDarkPenColor() const;
		Color getBrightPenColor() const;
		Color getPressedPenColor() const;
		Color getDarkPressedPenColor() const;
		Color getBrightPressedPenColor() const;
		Color getTextColor() const;

		const Size getTextExtent(const std::string& text) const;
		
		void DrawText(const std::string& text, const Point& p) const;			
		void DrawBitmap(const SDL_Surface* bitmap, const Point& p) const;		
		void DrawBitmap(const SDL_Surface* bitmap, const Point& p, const Rect& clip_rect) const;
		void DrawEmptyRectangle(const Rect& rect) const;
		void DrawEmptyRectangle(const Point& p, const Size& s) const;		
		void DrawRectangle(const Rect& rect) const; 
		void DrawRectangle(const Point& p, const Size& s) const;
		void DrawTabRectangle(const Rect& rect) const; 
		void DrawTabRectangle(const Point& p, const Size& s) const;
		void DrawSpline(const unsigned int c, const Point* p) const;
		void DrawSpline(const unsigned int c, const Point* p, const Point s) const;
		void DrawLine(const Point& p1, const Point& p2) const;		
		void DrawVerticalLine(const Point& p, const Uint16 height) const;
		void DrawHorizontalLine(const Point& p, const Uint16 width) const;		
		void DrawRoundedRectangle(const Point& p, const Size& s, const Uint16 radius) const;
		void DrawRoundedRectangle(const Rect& rect, const Uint16 radius) const;
		void DrawEdgedRoundedRectangle(const Point& p, const Size& s, const Uint16 radius) const;
		void DrawEdgedRoundedRectangle(const Rect& rect, const Uint16 radius) const;
		void DrawEmptyEdgedRoundedRectangle(const Point& p, const Size& s, const Uint16 radius) const;
		void DrawEmptyEdgedRoundedRectangle(const Rect& rect, const Uint16 radius) const;
		
		
	
		void setPressedRectangle(const bool pressed = true);

		void addRectangle(const Rect& rect);

		void switchToSurface(SDL_Surface* temp_surface);
		void switchToOriginalSurface();

		void drawFromPoint(const Point& p);
		Uint16 getMaxX() const;
		Uint16 getMaxY() const;

		void setBrightness(const signed int brightness);
		void resetBrightness();

		void setGradient(const unsigned int gradient);
		void resetGradient();

	private:

		static const char* dcVersion;

		unsigned int changedRectangles;
		SDL_Rect changedRectangle[DC_MAX_CHANGED_RECTANGLES];
		Uint16 max_x;
		Uint16 max_y;

		SDL_Surface* surface;
		SDL_Surface* oldSurface;
		void setSurface(SDL_Surface* sdl_surface) {
			if(surface) {
				SDL_FreeSurface(surface);
			}
			surface = sdl_surface;
		}

		bool pressedRectangle;


		Point dp;
		
		boost::shared_ptr<const Brush> brush;
		boost::shared_ptr<const Brush> darkBrush;
		boost::shared_ptr<const Brush> brightBrush;
		boost::shared_ptr<const Pen> pen;
		boost::shared_ptr<const Pen> darkPen;
		boost::shared_ptr<const Pen> brightPen;
		boost::shared_ptr<const Pen> pressedPen;
		boost::shared_ptr<const Pen> darkPressedPen;
		boost::shared_ptr<const Pen> brightPressedPen;
		boost::shared_ptr<const Color> textColor;

		boost::shared_ptr<const Brush> endBrush;
		boost::shared_ptr<const Brush> endDarkBrush;
		boost::shared_ptr<const Brush> endBrightBrush;
		boost::shared_ptr<const Pen> endPen;
		boost::shared_ptr<const Pen> endDarkPen;
		boost::shared_ptr<const Pen> endBrightPen;
		boost::shared_ptr<const Pen> endPressedPen;
		boost::shared_ptr<const Pen> endDarkPressedPen;
		boost::shared_ptr<const Pen> endBrightPressedPen;
		boost::shared_ptr<const Color> endTextColor;

		boost::shared_ptr<const Font> font;
		
		eBitDepth bitDepth;
		unsigned int bits;
		signed int brightness;
		unsigned int gradient;
		Size resolution;

		void (DC::*Draw_HLine)(const Sint16 x0, const Sint16 y0, const Sint16 x1) const;
		void Draw_HLine_8bit(const Sint16 x0, const Sint16 y0, const Sint16 x1) const;
		void Draw_HLine_16bit(const Sint16 x0, const Sint16 y0, const Sint16 x1) const;
		void Draw_HLine_24bit(const Sint16 x0, const Sint16 y0, const Sint16 x1) const;
		void Draw_HLine_32bit(const Sint16 x0, const Sint16 y0, const Sint16 x1) const;


		void (DC::*Draw_VLine)(const Sint16 x0, const Sint16 y0, const Sint16 y1) const;
		void Draw_VLine_8bit(const Sint16 x0, const Sint16 y0, const Sint16 y1) const;
		void Draw_VLine_16bit(const Sint16 x0, const Sint16 y0, const Sint16 y1) const;
		void Draw_VLine_24bit(const Sint16 x0, const Sint16 y0, const Sint16 y1) const;
		void Draw_VLine_32bit(const Sint16 x0, const Sint16 y0, const Sint16 y1) const;


		void (DC::*Draw_Line)(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const;
		void Draw_Line_8bit(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const;
		void Draw_Line_16bit(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const;
		void Draw_Line_24bit(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const;
		void Draw_Line_32bit(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const;
		
		void (DC::*DrawFilledRound)(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledRound_8bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledRound_16bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledRound_24bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledRound_32bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
	
		void (DC::*DrawTab)(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawTab_8bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawTab_16bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawTab_24bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawTab_32bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		
		void (DC::*DrawFilledEdgedRound)(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedRound_8bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedRound_16bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedRound_24bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedRound_32bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		
		void (DC::*DrawEmptyEdgedRound)(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyEdgedRound_8bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyEdgedRound_16bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyEdgedRound_24bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyEdgedRound_32bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		
		void (DC::*DrawEmptyRound)(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyRound_8bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyRound_16bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyRound_24bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawEmptyRound_32bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		
		void (DC::*DrawFilledEdgedBorderRound)(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedBorderRound_8bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedBorderRound_16bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedBorderRound_24bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;
		void DrawFilledEdgedBorderRound_32bit(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 corner) const;

		void DrawText(const std::string& text, const Sint16 x, const Sint16 y) const;
		void DrawBitmap(const SDL_Surface* bitmap, const Sint16 x, const Sint16 y) const;
		void DrawBitmap(const SDL_Surface* bitmap, const Sint16 x, const Sint16 y, const Rect& clip_rect) const;
		void DrawEmptyRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawTabRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height) const;
		void DrawLine(const Sint16 x0, const Sint16 y0, const Sint16 x1, const Sint16 y1) const;
		void DrawVerticalLine(const Sint16 x0, const Sint16 y0, const Sint16 y1) const;
		void DrawHorizontalLine(const Sint16 x0, const Sint16 y0, const Sint16 x1) const;
		void DrawRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 radius) const;
		void DrawEdgedRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 radius) const;
		void DrawEmptyEdgedRoundedRectangle(const Sint16 x, const Sint16 y, const Uint16 width, const Uint16 height, const Uint16 radius) const;

		DC(const DC& other);
		DC &operator=(const DC& other);
};

inline void DC::setGradient(const unsigned int gradient) {
	this->gradient = gradient;
}

inline void DC::setBrightness(const signed int brightness) {
	this->brightness = brightness;
}

inline void DC::resetBrightness() {
	this->brightness = 100;
}

inline bool DC::isFullScreen() const {
	BOOST_ASSERT(surface);
	return ((surface->flags) & SDL_FULLSCREEN) == SDL_FULLSCREEN;
}


inline const char* DC::getVersion() {
	return dcVersion;
}

inline void DC::drawFromPoint(const Point& p) {
	dp = p;
}

inline void DC::setPressedRectangle(const bool pressed) {
	pressedRectangle = pressed;
}

inline DC& DC::operator=(const DC& other) {
	//if(*this != other) {
		setSurface(other.surface);
	//}
	return *this;
}

inline DC::operator SDL_Surface*() const { 
	return surface;
}
		
inline SDL_Surface* DC::operator->() const {
	return surface;
}
		
inline SDL_Surface* DC::getSurface() const {
	return surface;
}
		
inline bool DC::valid() const {
	return surface != NULL;
}
		
inline Uint32 DC::flags() const {
	BOOST_ASSERT(surface);
	return getSurface()->flags;
}

inline const Size DC::getSize() const {
	return Size(w(), h());
}
		
inline Uint16 DC::w() const {
	BOOST_ASSERT(surface);
	return static_cast<Uint16>(getSurface()->w);
}
		
inline Uint16 DC::h() const {
	BOOST_ASSERT(surface);
	return static_cast<Uint16>(getSurface()->h);
}
		
inline Uint16 DC::pitch() const {
	BOOST_ASSERT(surface);
	return surface->pitch;
}
		
inline void* DC::pixels() { 
	BOOST_ASSERT(surface);
	return surface->pixels; 
}
		
inline const void* DC::pixels() const {
	BOOST_ASSERT(surface);
	return surface->pixels;
}
		
inline const struct private_hwdata* DC::hwdata() const {
	BOOST_ASSERT(surface);
	return surface->hwdata;
}
		
inline bool DC::SaveBMP(const std::string& file) const {
	if(file.size() == 0) {
		return false;// TODO SaveBMP(file.c_str()); 
	}
	else {
		return true;
	}
}

inline void DC::DrawLine(const Point& p1, const Point& p2) const {
	Point tp1 = dp + p1;
	Point tp2 = dp + p2;
	DrawLine(tp1.getX(), tp1.getY(), tp2.getX(), tp2.getY());
}

inline void DC::DrawText(const std::string& text, const Point& p) const {
	if(text.empty()) {
		return;
	}
	Point tp = dp + p;
	DrawText(text, tp.getX(), tp.getY());
}

inline void DC::DrawRoundedRectangle(const Point& p, const Size& s, const Uint16 radius) const {
	Point tp = dp + p;
	DrawRoundedRectangle(tp.getX(), tp.getY(), s.getWidth(), s.getHeight(), radius);
}
			
inline void DC::DrawRoundedRectangle(const Rect& rect, const Uint16 radius) const {
	Point tp = dp + rect.getTopLeft();
	DrawRoundedRectangle(tp.getX(), tp.getY(), rect.getWidth(), rect.getHeight(), radius);
}

inline void DC::DrawEdgedRoundedRectangle(const Point& p, const Size& s, const Uint16 radius) const {
	Point tp = dp + p;
	DrawEdgedRoundedRectangle(tp.getX(), tp.getY(), s.getWidth(), s.getHeight(), radius);
}
		
inline void DC::DrawEdgedRoundedRectangle(const Rect& rect, const Uint16 radius) const {
	Point tp = dp + rect.getTopLeft();
	DrawEdgedRoundedRectangle(tp.getX(), tp.getY(), rect.getWidth(), rect.getHeight(), radius);
}

inline void DC::DrawEmptyEdgedRoundedRectangle(const Point& p, const Size& s, const Uint16 radius) const {
	Point tp = dp + p;
	DrawEmptyEdgedRoundedRectangle(tp.getX(), tp.getY(), s.getWidth(), s.getHeight(), radius);
}
		
inline void DC::DrawEmptyEdgedRoundedRectangle(const Rect& rect, const Uint16 radius) const {
	Point tp = dp + rect.getTopLeft();
	DrawEmptyEdgedRoundedRectangle(tp.getX(), tp.getY(), rect.getWidth(), rect.getHeight(), radius);
}


inline void DC::setTextColor(const boost::shared_ptr<const Color>& textColor) {
	this->textColor = textColor;
}

// evtl sowohl gradient als auch gradient TODO
inline Color DC::getBrushColor() const {
	if(gradient != 0) {
		return brush->getColor()->mixColor(surface, *endBrush->getColor(), gradient);
	} else {
		return brush->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getDarkBrushColor() const{
	if(gradient != 0) {
		return darkBrush->getColor()->mixColor(surface, *endDarkBrush->getColor(), gradient);
	} else {	
		return darkBrush->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getBrightBrushColor() const{
	if(gradient != 0) {
		return brightBrush->getColor()->mixColor(surface, *endBrightBrush->getColor(), gradient);
	} else {	
		return brightBrush->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getPenColor() const{
	if(gradient != 0) {
		return pen->getColor()->mixColor(surface, *endPen->getColor(), gradient);
	} else {	
		return pen->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getDarkPenColor() const{
	if(gradient != 0) {
		return darkPen->getColor()->mixColor(surface, *endDarkPen->getColor(), gradient);
	} else {	
		return darkPen->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getBrightPenColor() const{
	if(gradient != 0) {
		return brightPen->getColor()->mixColor(surface, *endBrightPen->getColor(), gradient);
	} else {	
		return brightPen->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getPressedPenColor() const{
	if(gradient != 0) {
		return pressedPen->getColor()->mixColor(surface, *endPressedPen->getColor(), gradient);
	} else {	
		return pressedPen->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getDarkPressedPenColor() const{
	if(gradient != 0) {
		return darkPressedPen->getColor()->mixColor(surface, *endDarkPressedPen->getColor(), gradient);
	} else {	
		return darkPressedPen->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getBrightPressedPenColor() const{
	if(gradient != 0) {
		return brightPressedPen->getColor()->mixColor(surface, *endBrightPressedPen->getColor(), gradient);
	} else {	
		return brightPressedPen->getColor()->changeRelativeBrightness(surface, brightness);
	}
}

inline Color DC::getTextColor() const{
	if(gradient != 0) {
		return textColor->mixColor(surface, *endTextColor, gradient);
	} else if(brightness != 0) {
		return textColor->changeRelativeBrightness(surface, brightness);
	}
}






inline void DC::setBrush(const boost::shared_ptr<const Brush>& brush) {
	this->brush = brush;
}

inline void DC::setDarkBrush(const boost::shared_ptr<const Brush>& darkBrush) {
	this->darkBrush = darkBrush;
}

inline void DC::setBrightBrush(const boost::shared_ptr<const Brush>& brightBrush) {
	this->brightBrush = brightBrush;
}

inline void DC::setPen(const boost::shared_ptr<const Pen>& pen) {
	this->pen = pen;
}

inline void DC::setDarkPen(const boost::shared_ptr<const Pen>& darkPen) {
	this->darkPen = darkPen;
}

inline void DC::setBrightPen(const boost::shared_ptr<const Pen>& brightPen) {
	this->brightPen = brightPen;
}

inline void DC::setPressedPen(const boost::shared_ptr<const Pen>& pressedPen) {
	this->pressedPen = pressedPen;
}

inline void DC::setDarkPressedPen(const boost::shared_ptr<const Pen>& darkPressedPen) {
	this->darkPressedPen = darkPressedPen;
}

inline void DC::setBrightPressedPen(const boost::shared_ptr<const Pen>& endrightPressedPen) {
	this->brightPressedPen = brightPressedPen;
}


inline void DC::setEndBrush(const boost::shared_ptr<const Brush>& endBrush) {
	this->endBrush = endBrush;
}

inline void DC::setEndDarkBrush(const boost::shared_ptr<const Brush>& endDarkBrush) {
	this->endDarkBrush = endDarkBrush;
}

inline void DC::setEndBrightBrush(const boost::shared_ptr<const Brush>& endBrightBrush) {
	this->endBrightBrush = endBrightBrush;
}

inline void DC::setEndPen(const boost::shared_ptr<const Pen>& endPen) {
	this->endPen = endPen;
}

inline void DC::setEndDarkPen(const boost::shared_ptr<const Pen>& endDarkPen) {
	this->endDarkPen = endDarkPen;
}

inline void DC::setEndBrightPen(const boost::shared_ptr<const Pen>& endBrightPen) {
	this->endBrightPen = endBrightPen;
}

inline void DC::setEndPressedPen(const boost::shared_ptr<const Pen>& endPressedPen) {
	this->endPressedPen = endPressedPen;
}

inline void DC::setEndDarkPressedPen(const boost::shared_ptr<const Pen>& endDarkPressedPen) {
	this->endDarkPressedPen = endDarkPressedPen;
}

inline void DC::setEndBrightPressedPen(const boost::shared_ptr<const Pen>& endBrightPressedPen) {
	this->endBrightPressedPen = endBrightPressedPen;
}

inline void DC::setEndTextColor(const boost::shared_ptr<const Color>& endTextColor) {
	this->endTextColor = endTextColor;
}

inline bool DC::isSurfacePuffered() const {
	return oldSurface != NULL;
}
		
inline void DC::DrawBitmap(const SDL_Surface* bitmap, const Point& p) const {
	Point tp = dp + p;
	DrawBitmap(bitmap, tp.getX(), tp.getY());
}

inline void DC::DrawBitmap(const SDL_Surface* bitmap, const Point& p, const Rect& clip_rect) const {
	Point tp = dp + p;
	DrawBitmap(bitmap, tp.getX(), tp.getY(), clip_rect);
}	

inline void DC::DrawEmptyRectangle(const Rect& rect) const	{
	Point tp = dp + rect.getTopLeft();
	DrawEmptyRectangle(tp.getX(), tp.getY(), rect.getWidth(), rect.getHeight());
}
		
inline void DC::DrawEmptyRectangle(const Point& p, const Size& s) const {
	Point tp = dp + p;
	DrawEmptyRectangle(tp.getX(), tp.getY(), s.getWidth(), s.getHeight());
}
		
inline void DC::DrawRectangle(const Rect& rect) const { 
	Point tp = dp + rect.getTopLeft();
	DrawRectangle(tp.getX(), tp.getY(), rect.getWidth(), rect.getHeight());
}
		
inline void DC::DrawRectangle(const Point& p, const Size& s) const { 
	Point tp = dp + p;
	DrawRectangle(tp.getX(), tp.getY(), s.getWidth(), s.getHeight());
}

inline void DC::DrawTabRectangle(const Rect& rect) const { 
	Point tp = dp + rect.getTopLeft();
	DrawTabRectangle(tp.getX(), tp.getY(), rect.getWidth(), rect.getHeight());
}
		
inline void DC::DrawTabRectangle(const Point& p, const Size& s) const { 
	Point tp = dp + p;
	DrawTabRectangle(tp.getX(), tp.getY(), s.getWidth(), s.getHeight());
}

inline bool DC::setColorKey(const Uint32 flag, const Color key) const {
	BOOST_ASSERT(surface);
	return SDL_SetColorKey(surface, flag, key) == 0;
}

inline bool DC::setAlpha(const Uint32 flag, const Uint8 alpha) const {
	BOOST_ASSERT(surface);
	return SDL_SetAlpha(surface, flag, alpha) == 0;
}



inline void DC::clearScreen() {
	BOOST_ASSERT(surface);
	SDL_Rect rc = Rect::createRect(0, 0, max_x, max_y);
	SDL_FillRect(surface, &rc, 1);
}

inline void DC::Blit(SDL_Surface* src, SDL_Rect& dstrect) const {
	BOOST_ASSERT(surface);
	SDL_BlitSurface(src, NULL, surface, &dstrect);
}

inline void DC::DrawVerticalLine(const Point& p, const Uint16 height) const {
	Point tp = dp + p;
	DrawVerticalLine(tp.getX(), tp.getY(), tp.getY() + height);
}

inline void DC::DrawHorizontalLine(const Point& p, const Uint16 width) const {
	Point tp = dp + p;
	DrawHorizontalLine(tp.getX(), tp.getY(), tp.getX() + width);
}

inline bool DC::setBitDepth(const eBitDepth bit_depth) {
	BOOST_ASSERT(surface);
	return setScreen(resolution, bit_depth, surface->flags);
}

inline bool DC::setResolution(const Size current_resolution) {
	BOOST_ASSERT(surface);
	return setScreen(current_resolution, bitDepth, surface->flags);
}

inline const Size DC::getTextExtent(const std::string& text) const {
	return font->getTextExtent(text);
}

inline Uint16 DC::getMaxX() const {
	return max_x;
}

inline Uint16 DC::getMaxY() const {
	return max_y;
}

inline unsigned int DC::getBits() const {
	return bits;
}

inline eBitDepth DC::getBitDepth() const {
	return bitDepth;
}

inline void DC::setFont(const boost::shared_ptr<const Font>& font) {
	this->font = font;
}

#endif // _SDL_DC_HPP


