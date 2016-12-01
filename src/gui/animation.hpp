// g++ -o plaympeg plaympeg.c -I/usr/include/SDL -lSDL -lsmpeg

#if 0
#ifndef _GUI_ANIMATION_HPP
#define _GUI_ANIMATION_HPP

#include "statictext.hpp"
#include <sdlwrap/animation.hpp>
#include <sdlwrap/surface.hpp>
#include <sdlwrap/bitmap.hpp>

// TODO, make boost shared etc.
class Animation : public Object
{
	public:
		Animation(SDL_Object* const parent,
						const Rect& rect,
                        const Size& distance_bottom_right,
						const boost::shared_ptr<const Animation>& animation,
						const boost::shared_ptr<const Bitmap>& staticBitmap,
						const boost::shared_ptr<const Color>& color,
						const boost::shared_ptr<const Font>& font,
						const boost::shared_ptr<const Text>& text,
						const std::list<std::string>& parameterList,
						const Surface* surface,
						bool border = false,
						const ePositionMode position_mode = DO_NOT_ADJUST);

        ~Animation();

        void reloadOriginalSize();
		
		const Object* checkToolTip(const Point& mouse) const;
		SDL_Object* checkHighlight(const Point& mouse);

		void updateParameters(const std::list<std::string>& parameterList);
        
		void process();
        void draw(DC* const dc) const;

		bool isPlaying() const;
		bool isDone() const;
		void play();
		void pause();

	private:
		const boost::shared_ptr<const Animation> animation;
		const bool border;
		StaticText* const text;
		const boost::shared_ptr<const Bitmap> staticBitmap;

		SDL_Surface* animationSurface;	
		SDL_Surface* currentSurface;
		
		bool loop;		
		bool wasStarted;

//		const bool isLocked(const eAnimation id) const;
//		void lockAnimation(const bool lock); TODO
};

#endif // _GUI_ANIMATION_HPP

#endif // TODO
