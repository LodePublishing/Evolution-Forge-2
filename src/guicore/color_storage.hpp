#ifndef _GUICORE_STORAGES_COLOR_STORAGE_HPP
#define _GUICORE_STORAGES_COLOR_STORAGE_HPP

#include <misc/singlestorage.hpp>
#include <SDL.h>

#include "color.hpp"

class ColorStorage : public SingleStorage<Color>
{ 
public:
	// call when sdl_surface has changed (e.g. new bit depth)
	static void init(const SDL_Surface* const surface) {
		for(std::map<const boost::uuids::uuid, const boost::shared_ptr<const Color> >::const_iterator i = instance().getItemMap().begin(); i != instance().getItemMap().end(); i++) {
			i->second->init(surface);
		}
	}
};

#endif // _GUICORE_STORAGES_COLOR_STORAGE_HPP
