#include "bitmap.hpp"

#include <misc/exceptions.hpp>

Bitmap::Bitmap(const std::string& fileName):
	fileName(fileName),
	bitmap(IMG_Load(fileName.c_str()))
{
	if(!bitmap) {
		throw SDLException("ERROR (Bitmap::Bitmap()): Loading file " + fileName + " (" + IMG_GetError() + ").");
	}
}

Bitmap::Bitmap(const boost::uuids::uuid id, const std::string& fileName):
	UUID<Bitmap>(id),
	fileName(fileName),
	bitmap(IMG_Load(fileName.c_str()))
{
	if(!bitmap) {
		throw SDLException("ERROR (Bitmap::Bitmap()): Loading file " + fileName + " (" + IMG_GetError() + ").");
	}
}

Bitmap::~Bitmap() {
	SDL_FreeSurface(bitmap);
}