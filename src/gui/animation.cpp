#include "animation.hpp"

#if 0
#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)

// TODO problem: einzelne Resource? Was wenn mehrmals auf dem Schirm dasselbe Video gespielt wird?

Animation::Animation(SDL_Object* const parent, 
				const Rect& rect,
				const Size& distance_bottom_right, 
				const boost::shared_ptr<const Animation>& animation,
				const boost::shared_ptr<const Bitmap>& staticBitmap,
				const boost::shared_ptr<const Color>& color,
				const boost::shared_ptr<const Font>& font,
				const boost::shared_ptr<const Text>& text,
				const std::list<std::string>& parameterList,
				const Surface* surface,				
				bool border,
				const ePositionMode position_mode) :
	Object(parent, rect,  distance_bottom_right, position_mode, NO_AUTO_SIZE),
	animation(animation),
	staticBitmap(staticBitmap),
	text(new StaticText(this, Rect(Point(0,-10),Size()), Size(), color, font, text, parameterList)),
	border(border),
	animationSurface(NULL),
	currentSurface(NULL),
	loop(false),
	
	wasStarted(false)	
{
//	animationText->Hide();

//	if(isLocked(id)) {
//		return false;
//	}
//	lockAnimation(false);
	//this->animation = animation;

//	lockAnimation(true);
	if(animationSurface != NULL) { // TODO exception?
		SDL_FreeSurface(animationSurface);
		animationSurface = NULL;
	}
	setSize(Size(static_cast<Uint16>((animation->getInfo().width), static_cast<Uint16>((animation->getInfo().height)));	
	setDrawType(SOLID_OBJECT);
}

void Animation::updateParameters(const std::list<std::string>& parameterList) {
	text->updateParameters(parameterList);
}

Animation::~Animation()
{
//      SMPEG_stop(movie);
//	  SMPEG_delete(movie);
//	  movie = NULL;

	delete text;
//	lockAnimation(false);
}

//void Animation::lockAnimation(const bool lock)
//{
//	SMPEG* temp = gui.lookUpAnimation(id);
//	BOOST_ASSERT(temp);
	//??? TODO

//}


void update(SDL_Surface *screen)
{
	// TODO observer erstellen...
// => process
}


bool Animation::isPlaying() const
{
	bool status = false;
	status = SMPEG_status(*animation) == SMPEG_PLAYING;
	return status;
}

bool Animation::isDone() const
{
	return !isPlaying() && wasStarted;
}

void Animation::play()
{
	if(!isPlaying())
	{
		if(!wasStarted)
		{
			wasStarted = true;
			SMPEG_play(*animation);
		}
	}
}

void Animation::pause()
{
	if(isPlaying()) {
		SMPEG_pause(*animation);
	}
}

/*			  // Toggle filtering on/off
			  if ( bilinear_filtering ) {
			    SMPEG_Filter *filter = SMPEGfilter_null();
			    filter = SMPEG_filter( mpeg, filter );
			    filter->destroy(filter);
			    bilinear_filtering = 0;
			  } else {
			    SMPEG_Filter *filter = SMPEGfilter_bilinear();
			    filter = SMPEG_filter( mpeg, filter );
			    filter->destroy(filter);
			    bilinear_filtering = 1;
			  }*/

//			    SMPEG_skip(mpeg, 50);
//			  SMPEG_setvolume(mpeg, volume);
		  
/*case SDL_VIDEORESIZE: {
                        SDL_Surface *old_screen = screen;
                        SMPEG_pause(mpeg);
                        screen = SDL_SetVideoMode(event.resize.w, event.resize.h, screen->format->BitsPerPixel, screen->flags);
			if ( old_screen != screen ) {
                            SMPEG_setdisplay(mpeg, screen, NULL, update);
                        }
                        SMPEG_scaleXY(mpeg, screen->w, screen->h);
                        SMPEG_pause(mpeg);
                    } break;
*/


void Animation::reloadOriginalSize()
{
//	setOriginalSize(getBitmapSize());
	Object::reloadOriginalSize();
//	adjustSize(CHILD_WAS_CHANGED); // TODO
}

/*
void Animation::setBrightness(const unsigned int bitmap_brightness) 
{
	if(brightness != bitmap_brightness)
	{
		brightness = bitmap_brightness;
		makePufferInvalid();
//		setNeedRedrawAllThatOverlaps(getRelativeRect());
//		toErrorLog(brightness);
	}
}*/
// hoechstens bei update aufrufen...
	

// Render button.  How it draws exactly depends on it's current state.
void Animation::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

            // Play the movie
   //         SMPEG_play( movie );
 
            // Draw the movie surface to the main screen at 0,0
      //      DrawIMG( movieSurface, 0, 0 );


//	if(clipRect != Rect())
//		dc->DrawBrightenedBitmap(gui.lookUpBitmap(checked?(eBitmap)(bitmap+1):bitmap), Point(), clipRect, brightness);
//	else
//		dc->DrawBrightenedBitmap(gui.lookUpBitmap(checked?(eBitmap)(bitmap+1):bitmap), Point(), brightness);
	Object::draw(dc);
		
	// leeres / letztes Bild evtl

/*	if(border)
	{
		dc->setBrush(*gui.lookUpBrush(TRANSPARENT_BRUSH));
		dc->setPen(*gui.lookUpPen(INNER_BORDER_PEN));
		dc->DrawEdgedRoundedRectangle(getRelativeRect(), 4);
		dc->setPen(*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
		dc->DrawEdgedRoundedRectangle(Rect(getRelativePosition() + Size(3,3), getSize() - Size(6,6)), 4);
	}*/


	if(isPlaying()) {
//		text->Show();
		staticBitmap->Hide();
	} else if(wasStarted && !isPlaying()) {
		staticBitmap->Show();
	}

	if(animationSurface != NULL) {
		SDL_Rect dest = DC::createRect(getAbsoluteRect());
		SDL_BlitSurface(animationSurface, NULL, dc->getSurface(), &dest);
		SDL_UpdateRect(dc->getSurface(), dest.x, dest.y, dest.w, dest.h);
	}


	//TODO?
//		Object::addNewRectToList(getAbsoluteRect(), getZ());

}

const Object* Animation::checkToolTip(const Point& mouse) const {
	if( !isShown() || !getAbsoluteRect().isTopLeftCornerInside(mouse)) {
		return NULL;
	}
	return (Object*)this;
}

SDL_Object* Animation::checkHighlight(const Point& mouse)
{
	if(!isShown()) {
		return NULL;
	}
	return Object::checkHighlight(mouse);
}

void Animation::process()
{
	Object::process();
	if(!isShown()) {
		return;
	}

	if(animationSurface == NULL) {
		
	    const SDL_PixelFormat* pixel_format = currentSurface->format;

		SDL_Surface* temp = SDL_CreateRGBSurface( SDL_SWSURFACE, getWidth(), getHeight(), 32, pixel_format->Rmask, pixel_format->Gmask, pixel_format->Bmask, pixel_format->Amask );
		
		animationSurface = SDL_DisplayFormat( temp );
		SDL_FreeSurface(temp);
	
		SMPEG_setdisplay(animation->getSurface(), animationSurface, NULL, NULL);//update);
		SMPEG_scaleXY(animation->getSurface(), getWidth(), getHeight());
		SMPEG_setdisplayregion(animation, 50, 50, 100, 100); // TODO

	      // Set the display region
    /*  SMPEG_setdisplayregion( movie, 0, 0, moveInfo.width, moveInfo.height );
 
      // Loop forever
	  if(loop) {
		SMPEG_loop( movie, 1 );
	  } else {
		  SMPEG_loop(movie, 1);
	  }*/
 
      // SDL_ShowCursor(SDL_DISABLE);mmh...


	/* Enable software bilinear filtering, if desired */
//	if ( bilinear_filtering ) {
//		SMPEG_Filter *filter;
//		filter = SMPEGfilter_bilinear();
///		filter = SMPEG_filter( mpeg, filter );
//		filter->destroy(filter);
//	}

		/* Seek starting position */
//	if(seek) SMPEG_seek(mpeg, seek);

	/* Skip seconds to starting position */
//	if(skip) SMPEG_skip(mpeg, skip);
	}
}

#endif
