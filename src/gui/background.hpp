#ifndef _GUI_BACKGROUND_HPP
#define _GUI_BACKGROUND_HPP

#include "object.hpp"

class BackGround : public Object
{
	public:
		BackGround(const Size& size, SDL_Surface* const bitmap = NULL);
		~BackGround();

		void reloadOriginalSize();
		void process();
		void draw(DC* const dc) const;

		void updateBitmap(SDL_Surface* const bitmap);

	private:
		SDL_Surface* bitmap;
};

#endif // _GUI_BACKGROUND_HPP

