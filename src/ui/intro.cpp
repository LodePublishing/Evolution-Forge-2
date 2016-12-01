#include "intro.hpp"

#if 0

Intro::Intro(Object* intro_parent, 
				const Rect& intro_rect,
				const Size distance_bottom_right, 
				const ePositionMode intro_position_mode) :
	Object(intro_parent, intro_rect,  distance_bottom_right, intro_position_mode, NO_AUTO_SIZE),
	clickText(new StaticText(this, INTRO_CLICK_STRING, Rect(), Size(0, 20), BRIGHT_TEXT_COLOR, MIDDLE_SHADOW_BOLD_FONT, BOTTOM_RIGHT)),
	libraryGroup(new Group(this, Rect(), Size(), TWO_LINES_GROUP, false, BOTTOM_CENTER, NULL_STRING)),
	introPhase(MAIN_INTRO),
	wasClicked(false),
	soundPlayed(false)
{
	introAnimation[MAIN_INTRO] = new Animation(this, Rect(), Size(), INTRO_MAIN_ANIMATION, INTRO_MAIN_BITMAP, INTRO_MAIN_STRING, true, TOTAL_CENTERED);
	for(unsigned int i = SDL_INTRO; i < MAX_INTRO_STEPS; ++i)
		introAnimation[i] = new Animation(libraryGroup, Rect(), Size(0,10), (eAnimation)(INTRO_MAIN_ANIMATION + i), (eBitmap)(INTRO_MAIN_BITMAP + i), (eString)(INTRO_MAIN_STRING + i), true);
	
	for(unsigned int i = 0; i < MAX_INTRO_STEPS; ++i)
		introAnimation[i]->Hide();
	
	reloadOriginalSize();
	clickText->Hide();
	Hide();
}

Intro::~Intro()
{
	for(unsigned int i = 0; i < MAX_INTRO_STEPS; ++i)
		delete introAnimation[i];
	delete clickText;
}

void Intro::setWasClicked()
{
	wasClicked = true;
}

const bool Intro::addKey(unsigned int key, unsigned int mod)
{
	setWasClicked();
	return(true);
}

const bool Intro::isDone() const 
{
	return(wasClicked);
}

void Intro::reloadOriginalSize()
{
	Object::reloadOriginalSize();
}

void Intro::draw() const
{
	Object::draw();
}


void Intro::process()
{
	if((!isShown())||isDone())
		return;
	Object::focus = this;
	if(introPhase == MAX_INTRO_STEPS)
		return;


	if(!introAnimation[introPhase]->isDone())
	{
		if((introPhase == MAIN_INTRO)&&(!soundPlayed)&&(Object::theme.lookUpAnimationInfo(INTRO_MAIN_ANIMATION).current_frame>80))
		{
			Object::sound.playSound(INTRO_SOUND, introAnimation[introPhase]->getAbsolutePosition().x + introAnimation[introPhase]->getWidth()/2);
			soundPlayed = true;
		}
		if(!introAnimation[introPhase]->isShown())
		{
			introAnimation[introPhase]->Show();
			introAnimation[introPhase]->play();
			switch(introPhase)
			{
				case MAIN_INTRO:
					break;
				case SDL_INTRO:
				case SDL_TTF_INTRO:
				case SDL_IMAGE_INTRO:
				case GUI_INTRO:
				case SMPEG_INTRO:
#ifdef _FMOD_SOUND
				case FMOD_INTRO:
#elif _SDL_MIXER_SOUND
				case SDL_MIXER_INTRO:
#endif
					Object::sound.playSound(RING_SOUND, introAnimation[introPhase]->getAbsolutePosition().x + introAnimation[introPhase]->getWidth()/2);
					break;
				default:toErrorLog(":(");break;
			}
		}
	} else
	{
		introPhase = (eIntroPhase)(introPhase+1);
		if(introPhase == MAX_INTRO_STEPS)
			clickText->Show();
	}
}

#endif
