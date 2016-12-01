#ifndef _GUICORE_BITMAP_HPP
#define _GUICORE_BITMAP_HPP

#pragma warning(push, 0)  
#include <SDL.h>
#include <SDL_image.h>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include <string>

class Bitmap : public UUID<Bitmap>
{
public:
	Bitmap(const boost::uuids::uuid id, const std::string& fileName);
	Bitmap(const std::string& fileName);
	~Bitmap();

	operator SDL_Surface*() const;
	SDL_Surface* operator->() const;

	bool equals(SDL_Surface* surface) const;

	const std::string& getFileName() const;

private:

	const std::string fileName;

	SDL_Surface *const bitmap;

	/*		bool scale;
	bool used;
	bool solid;*/

	static const std::string BITMAP_DIRECTORY;
};

inline const std::string& Bitmap::getFileName() const {
	return fileName;
}

inline Bitmap::operator SDL_Surface*() const { 
	return bitmap;
}

inline SDL_Surface* Bitmap::operator->() const {
	return bitmap;
}

#endif // _GUICORE_BITMAP_HPP