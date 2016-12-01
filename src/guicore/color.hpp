#ifndef _GUICORE_COLOR_HPP
#define _GUICORE_COLOR_HPP

#pragma warning(push, 0)  
#include <SDL.h>
#pragma warning(pop)

#include <misc/uuid.hpp>


class Color : public UUID<Color>
{
public:
	Color(const SDL_Surface* const surface, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha = 255);
	Color(const SDL_Surface* const surface, const SDL_Color scolor);
	Color(const boost::uuids::uuid id, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha = 255);
	~Color();

	void init(const SDL_Surface* const surface) const {
		ucol = SDL_MapRGB(surface->format, scol.r, scol.g, scol.b);
	}

	operator SDL_Color() const;
	operator Uint32() const;

	Uint8 r() const;
	Uint8 g() const;
	Uint8 b() const;
	Uint8 a() const;

	const Color mixColor(const SDL_Surface* const surface, const Color& other) const;
	const Color mixColor(const SDL_Surface* const surface, const Color& other, const unsigned int gradient) const;
	const Color changeAbsoluteBrightness(const SDL_Surface* const surface, const signed int brightness) const;
	const Color changeRelativeBrightness(const SDL_Surface* const surface, const unsigned int brightness_percent) const;

	static const SDL_Color toSDL_Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a = 255);
private:	

	mutable Uint32 ucol; // TODO
	const SDL_Color scol;
};

inline Color::Color(const SDL_Surface* const surface, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha):
        ucol(SDL_MapRGB(surface->format, red, green, blue)),
        scol(toSDL_Color(red, green, blue, alpha))
{ }

inline Color::Color(const SDL_Surface* const surface, const SDL_Color scolor):
        ucol(SDL_MapRGB(surface->format, scolor.r, scolor.g, scolor.b)),
        scol(scolor)
{ }

inline Color::Color(const boost::uuids::uuid id, const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha):
        UUID<Color>(id),
        ucol(),
        scol(toSDL_Color(red, green, blue, alpha))
{ }



inline Color::~Color() { }


inline Color::operator SDL_Color() const {
	return scol;
}

inline Color::operator Uint32() const {
	return ucol;
}

inline Uint8 Color::r() const {
	return scol.r;
}

inline Uint8 Color::g() const {
	return scol.g;
}

inline Uint8 Color::b() const {
	return scol.b;
}

inline Uint8 Color::a() const {
	return scol.unused;
}

inline const SDL_Color Color::toSDL_Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
	SDL_Color scol;
	scol.r = r;
	scol.g = g;
	scol.b = b;
	scol.unused = a;
	return scol;
}

#endif // _GUICORE_COLOR_HPP
