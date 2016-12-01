#include "color.hpp"

#include <misc/exceptions.hpp>

const Color Color::mixColor(const SDL_Surface* const surface, const Color& other)  const
{
	return Color(surface, 
		    (this->r() + other.r())/2,
			(this->g() + other.g())/2,
			(this->b() + other.b())/2);
}

const Color Color::mixColor(const SDL_Surface* const surface, const Color& other, const unsigned int gradient) const
{
#ifdef _SCC_DEBUG
	if(gradient > 100) {
		throw SDLException("ERROR (Color::mixColor()): Parameter gradient is out of range.");
	}
#endif
	return Color(surface, 
		(this->r()*gradient + other.r() * (100 - gradient))/100,
		(this->g()*gradient + other.g() * (100 - gradient))/100,
		(this->b()*gradient + other.b() * (100 - gradient))/100);
}

const Color Color::changeAbsoluteBrightness(const SDL_Surface* const surface, const signed int brightness) const
{
	if(brightness == 0) {
		return *this;
	}
#ifdef _SCC_DEBUG
	if(brightness > 255) {
		throw SDLException("ERROR (Color::changeAbsoluteBrightness()): Parameter brightness is out of range.");
	}
#endif
	int r = this->r() + brightness;
	int g = this->g() + brightness;
	int b = this->b() + brightness;
	if(r > 255) { r = 255;}
	if(g > 255) { g = 255;}
	if(b > 255) { b = 255;}
	return Color(surface, static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b));
}

const Color Color::changeRelativeBrightness(const SDL_Surface* const surface, const unsigned int brightness_percent) const
{
	if(brightness_percent == 100) {
		return *this;
	}
	int r = this->r() * brightness_percent / 100; if(r>255) r = 255;
	int g = this->g() * brightness_percent / 100; if(g>255) g = 255;
	int b = this->b() * brightness_percent / 100; if(b>255) b = 255;
	return Color(surface, static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b));
}
