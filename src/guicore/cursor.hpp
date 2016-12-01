#ifndef _GUICORE_CURSOR_HPP
#define _GUICORE_CURSOR_HPP

#pragma warning(push, 0)  
#include <SDL.h>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include "bitmap.hpp"

class Cursor : public UUID<Cursor>
{
public:
	Cursor(const boost::uuids::uuid id, const std::string& fileName);
	Cursor(const std::string& fileName);
	~Cursor();
	
	const std::string& getFileName() const;
	operator SDL_Cursor*() const;
private:
	// call not before SDL was initialized!
	static SDL_Cursor* createCursor(SDL_Surface* surface);
	static SDL_PixelFormat& get_neutral_pixel_format();
	const std::string fileName;
	const boost::shared_ptr<const Bitmap> bitmap;
	SDL_Cursor* cursor;
};

inline const std::string& Cursor::getFileName() const {
	return fileName;
}

inline Cursor::operator SDL_Cursor*() const {
	return cursor;
}

#endif // _GUICORE_CURSOR_HPP