#include "guiinstance.hpp"

#include <misc/exceptions.hpp>
#include <misc/log.hpp>
#include <lang/text_storage.hpp>

// TODO SDL_NOFRAME for intro picture!

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#define MUSIC_TRANSITION_DURATION 2000
#endif 

#ifdef _FMOD_SOUND
#include <fmod.hpp>
#include <fmod_errors.h>
#endif

Gui::Gui(const boost::uuids::uuid id, const std::string& title, const boost::shared_ptr<const GuiConfiguration> guiConfiguration):
	UUID<Gui>(id),
	title(title),
	guiConfiguration(guiConfiguration),
	dc(new DC()),
#ifdef _FMOD_SOUND
	soundEngine(NULL),
	musicChannel(NULL),
#endif
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	soundInitialized(false),
#endif
	defaultCursor(SDL_GetCursor())
{
	init();
}

Gui::Gui(const std::string& title, const boost::shared_ptr<const GuiConfiguration> guiConfiguration):
	UUID<Gui>(),
	title(title),
	guiConfiguration(guiConfiguration),
	dc(new DC()),
#ifdef _FMOD_SOUND
	soundEngine(NULL),
	musicChannel(NULL),
#endif
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	soundInitialized(false),
#endif
	defaultCursor(SDL_GetCursor())
{
	init();
}


void Gui::init() {
	// ------ INIT SDL AND WINDOW ------

	toInfoLog("* " + TextStorage::instance().get(textMap[START_INIT_SDL_TEXT_ID])->getText());
	toInfoLog("* " + TextStorage::instance().get(textMap[isFullScreen() ? START_SET_FULLSCREEN_MODE_TEXT_ID:START_SET_WINDOW_MODE_TEXT_ID])->getText());
	
	Uint32 flags = SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_HWPALETTE|SDL_SRCCOLORKEY|SDL_RLEACCEL|SDL_SRCALPHA|SDL_PREALLOC|SDL_DOUBLEBUF;
	if(isFullScreen()) {
		flags |= SDL_FULLSCREEN;
	}
	Uint32 nflags = SDL_INIT_NOPARACHUTE | SDL_INIT_VIDEO | SDL_INIT_TIMER;
#ifdef _SDL_MIXER_SOUND
	nflags |= SDL_INIT_AUDIO;
#endif 
	// need to be called before initialization of dc
	Size resolution_size = getResolutionSize();
	eBitDepth bit_depth = getBitDepth();

	try {
		dc->initSDL(resolution_size, bit_depth, flags, nflags);
	} catch(...) {
		delete dc;
		dc = NULL;
		throw SDLException(TextStorage::instance().get(textMap[START_UNABLE_TO_INIT_SDL_TEXT_ID])->getText() + " [SDL ERROR: \"" + SDL_GetError() + "\"]");
	}

	if ( !dc->valid() ) {
		delete dc;
		dc = NULL;
		throw SDLException(TextStorage::instance().get(textMap[START_ERROR_SETTING_VIDEO_MODE_TEXT_ID])->getText() + " [SDL ERROR: \"" + SDL_GetError() + "\"]");
	}

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	toInfoLog(printHardwareInformation());
	toInfoLog("* " + TextStorage::instance().get(textMap[START_CREATED_SURFACE_TEXT_ID])->getText() + " " + printSurfaceInformation(dc));
	// ------ END INIT SDL AND WINDOW ------

	SDL_WM_SetCaption(title.c_str(),"");

	// ------ INIT SDL_TTF ------
	toInfoLog("* " + TextStorage::instance().get(textMap[START_INIT_SDL_TRUETYPE_FONTS_TEXT_ID])->getText());
	if(TTF_Init()==-1) {
		delete dc;
		dc = NULL;
		throw SDLException(TextStorage::instance().get(textMap[START_INIT_SDL_TTF_ERROR_TEXT_ID])->getText() + " [\"" + TTF_GetError() + "\"]");
	}
	atexit(TTF_Quit); 
	// ------ END INIT SDL_TTF ------

	// ------ INIT SOUND ENGINE -------
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	if(isSound() || isMusic())
	{
		soundInitialized = true;
		try {
			initSoundEngine();
		} catch(SDLException e) {
			setSound(false);
			setMusic(false);
			soundInitialized = false;
		}
	} else {
		toInfoLog(TextStorage::instance().get(textMap[START_INIT_NOSOUND_TEXT_ID])->getText());
	}
#endif
	// ------ END INIT SOUND ENGINE -------
}

Gui::~Gui()
{
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	releaseSoundEngine();
#endif



	//	toInfoLog("* " + TextStorage::instance().get(textMap[END_RESET_MOUSE_CURSOR_TEXT_ID])->getText());
	//	SDL_SetCursor(defaultCursor);

	// TODO: Jeder Mauszeiger der benutzt wurde verursacht bei SDL_FreeCursor einen segfault :/ (bzw. 'wurde schon geloescht' Fehler der glibc

	/*	toInfoLog("* " + lookUpString(END_FREEING_COLORS_BRUSHES_PENS_TEXT_ID])->getText());
	for(unsigned int i = MAX_COLOR_THEMES;i--;)
	{
	for(unsigned int j = MAX_COLORS;j--;)
	delete colorList[i][j];
	for(unsigned int j = MAX_BRUSHES;j--;)
	delete brushList[i][j];
	for(unsigned int j = MAX_PENS;j--;)
	delete penList[i][j];
	}

	toInfoLog("* " + lookUpString(END_FREEING_BITMAPS_TEXT_ID])->getText());
	for(std::list<BitmapEntry>::iterator l = loadedBitmaps.begin(); l!=loadedBitmaps.end();++l) {
	SDL_FreeSurface(l->bitmap);
	}

	#ifdef USE_SMPEG
	toInfoLog("* " + lookUpString(END_FREEING_ANIMATIONS_TEXT_ID])->getText());
	for(std::list<AnimationEntry>::iterator l = loadedAnimations.begin(); l!=loadedAnimations.end();++l)
	if(l->animation)
	SMPEG_delete(l->animation);
	#endif

	toInfoLog("* " + lookUpString(END_FREEING_COORDINATES_TEXT_ID])->getText());
	for(unsigned int i = MAX_RESOLUTIONS;i--;)
	{
	for(unsigned int j = MAX_GLOBAL_WINDOWS;j--;)
	delete globalRectList[i][j];
	for(unsigned int j = MAX_COMPARE_GAMES;j--;)
	for(unsigned int k = MAX_COMPARE_GAMES;k--;)
	{
	for(unsigned int l = MAX_GAME_WINDOWS;l--;)
	delete gameRectList[i][j][k][l];
	for(unsigned int l = MAX_PLAYER;l--;)
	for(unsigned int m = MAX_PLAYER;m--;)
	for(unsigned int n = MAX_PLAYER_WINDOWS;n--;)
	delete playerRectList[i][j][k][l][m][n];
	}
	}

	toInfoLog("* " + lookUpString(END_FREEING_BUTTONS_TEXT_ID])->getText());
	for(unsigned int i=MAX_BUTTON_COLORS_TYPES;i--;)
	delete buttonColorsList[i];

	toInfoLog("* " + lookUpString(END_FREEING_FONTS_TEXT_ID])->getText());
	for(unsigned int i = MAX_RESOLUTIONS;i--;)
	//		for(unsigned int j = MAX_LANGUAGES;j--;)
	for(unsigned int k = MAX_FONTS;k--;)
	delete fontList[i][k];
	*/

	delete dc;
}

void Gui::resetWindow()
{
	windowSelected = false;
	currentWindow = NULL;
}


void Gui::addMessage(const std::string& msg)
{
	remainingMessages.push_back(msg);
}



std::string Gui::printHardwareInformation()
{
	// TODO: uebersetzen bzw. dem Aufrufer nur Daten uebergeben
	SDL_Rect **modes;
	std::ostringstream os;
	os.str("");
	modes = SDL_ListModes(NULL, SDL_SWSURFACE);
	if(modes == (SDL_Rect **)0) {
		os << "* " << TextStorage::instance().get(textMap[START_SDL_NO_MODES_AVAILABLE_TEXT_ID])->getText() << std::endl;
	}
	else
	{
		if(modes == (SDL_Rect **)-1) {
			os << "* " << TextStorage::instance().get(textMap[START_SDL_ALL_RESOLUTIONS_AVAILABLE_TEXT_ID])->getText() << std::endl;
		} else
		{
			os << "* " << TextStorage::instance().get(textMap[START_SDL_AVAILABLE_MODES_TEXT_ID])->getText();
			for(unsigned int i=0; modes[i]; ++i) {
				os << "  " << modes[i]->w << " x " << modes[i]->h;
			}
			os << std::endl;
		}
	}
	const SDL_VideoInfo* hardware = SDL_GetVideoInfo();
	os << " - " << TextStorage::instance().get(textMap[START_SDL_MAX_COLOR_DEPTH_TEXT_ID])->getText() << (unsigned int)hardware->vfmt->BitsPerPixel;
	//	if(hardware->hw_available) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_HARDWARE_SURFACES_POSSIBLE_TEXT_ID])->getText();
	if(hardware->wm_available) os << "\n - " << TextStorage::instance().get(textMap[START_SDL_WINDOW_MANAGER_AVAILABLE_TEXT_ID])->getText();
	if(hardware->blit_hw) os << "\n - " << TextStorage::instance().get(textMap[START_SDL_HARDWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->blit_hw_CC) os << "\n - " << TextStorage::instance().get(textMap[START_SDL_HARDWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->blit_hw_A) os << "\n - " << TextStorage::instance().get(textMap[START_SDL_HARDWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->blit_sw) os << "\n - " << TextStorage::instance().get(textMap[START_SDL_SOFTWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->blit_sw_CC) os << "\n - " << TextStorage::instance().get(textMap[START_SDL_SOFTWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->blit_sw_A)	os << "\n - " << TextStorage::instance().get(textMap[START_SDL_SOFTWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->blit_fill)	os << "\n - " << TextStorage::instance().get(textMap[START_SDL_COLOR_FILLS_ACCELERATED_TEXT_ID])->getText();
	if(hardware->video_mem>0) {
		std::string memoryString = TextStorage::instance().get(textMap[START_SDL_TOTAL_VIDEO_MEMORY_TEXT_ID])->getText();
		std::list<std::string> parameterList;
		parameterList.push_back(boost::lexical_cast<std::string>(hardware->video_mem));
		Misc::formatString(memoryString, parameterList);
		os << "\n - " << memoryString;
	}
	//	Total amount of video memory: " << hardware->video_mem << "kb";
	return os.str();
}





// after a bit-depth change
/*void Gui::updateColors(SDL_Surface* surface)
{
for(unsigned int i = MAX_COLOR_THEMES;i--;)
{
for(unsigned int j = MAX_COLORS;j--;)
if(colorList[i][j]!=NULL)
colorList[i][j]->updateColor(surface);
for(unsigned int j = MAX_BRUSHES;j--;)
if(brushList[i][j]!=NULL)
brushList[i][j]->updateColor(surface);
for(unsigned int j = MAX_PENS;j--;)
if(penList[i][j]!=NULL)
penList[i][j]->updateColor(surface);
}
}*/



std::string Gui::printSurfaceInformation(DC* surface)
{
	std::ostringstream os; os.str("");
	os << surface->getSurface()->w << " x " << surface->getSurface()->h << " @ " << (unsigned int)(surface->getSurface()->format->BitsPerPixel);
	if (surface->flags() & SDL_SWSURFACE) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_STORED_IN_SYSTEM_MEMORY_TEXT_ID])->getText();
	//Surface is stored in system memory";
	else if(surface->flags() & SDL_HWSURFACE) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_STORED_IN_VIDEO_MEMORY_TEXT_ID])->getText();
	//			Surface is stored in video memory";
	if(surface->flags() & SDL_ASYNCBLIT) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_USES_ASYNCHRONOUS_BLITS_TEXT_ID])->getText();
	//urface uses asynchronous blits if possible";
	if(surface->flags() & SDL_ANYFORMAT) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_ALLOWS_ANY_PIXEL_FORMAT_TEXT_ID])->getText();
	if(surface->flags() & SDL_HWPALETTE) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_HAS_EXCLUSIVE_PALETTE_TEXT_ID])->getText();
	if(surface->flags() & SDL_DOUBLEBUF) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_IS_DOUBLE_BUFFERED_TEXT_ID])->getText();
	if(surface->flags() & SDL_OPENGL) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_HAS_OPENGL_CONTEXT_TEXT_ID])->getText();
	if(surface->flags() & SDL_OPENGLBLIT) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_SUPPORTS_OPENGL_BLITTING_TEXT_ID])->getText();
	if(surface->flags() & SDL_RESIZABLE) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_IS_RESIZABLE_TEXT_ID])->getText();
	if(surface->flags() & SDL_HWACCEL) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_BLIT_USES_HARDWARE_ACCELERATION_TEXT_ID])->getText();
	//Surface blit uses hardware acceleration";
	if(surface->flags() & SDL_SRCCOLORKEY) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_USES_COLORKEY_BLITTING_TEXT_ID])->getText();
	//Surface use colorkey blitting";
	if(surface->flags() & SDL_RLEACCEL) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_COLORKEY_BLITTING_RLE_ACCELERATED_TEXT_ID])->getText();
	//Colorkey blitting is accelerated with RLE";
	if(surface->flags() & SDL_SRCALPHA) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_BLIT_USES_ALPHA_BLENDING_TEXT_ID])->getText();
	//	Surface blit uses alpha blending";
	if(surface->flags() & SDL_PREALLOC) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_USES_PREALLOCATED_MEMORY_TEXT_ID])->getText();
	if(SDL_MUSTLOCK(surface->getSurface())) os << "\n- " << TextStorage::instance().get(textMap[START_SDL_SURFACE_NEEDS_LOCKING_TEXT_ID])->getText();
	return os.str();
}



//void Gui::animateWaitCursor();


void Gui::resetScreen()
{
	BOOST_ASSERT(dc);
	dc->setScreen(guiConfiguration->getResolutionSize(), guiConfiguration->getBitDepth(), dc->flags() | SDL_FULLSCREEN);
}



bool Gui::setResolutionSize(const Size& size) {
	return dc->setResolution(size);
}

bool Gui::setBitDepth(const eBitDepth bit_depth) {
	return dc->setBitDepth(bit_depth);
}

bool Gui::setFullScreen(const bool full_screen) {
	return dc->setFullScreen(full_screen);
}


// ------ EVENTS ------

void Gui::setMouse(const Point& p, SDL_Object* root_object)
{
	if((p == mouse) && (!Button::isWasResetted())) {
		return;
	}

	Button::setWasResetted(false);
	mouse = p;

	if(Button::isCurrentButtonHasAlreadyLeft())
	{
		if(Button::getCurrentButton() && Button::getCurrentButton()->getAbsoluteRect().isTopLeftCornerInside(p))
		{
			Button::getCurrentButton()->mouseHasEnteredArea();
			Button::setCurrentButtonHasAlreadyLeft(false);
		}
		else {
			return;
		}
	}

	if(Button::getCurrentButton() && !Button::getCurrentButton()->getAbsoluteRect().isTopLeftCornerInside(p))
	{
		Button::getCurrentButton()->mouseHasLeftArea();
		if(!Button::isCurrentButtonPressed()) {
			Button::resetButton();
		}
		else {
			Button::setCurrentButtonHasAlreadyLeft();
		}
	}

	// ignore mousemove if button is still pressed		
	if(Button::getCurrentButton())
	{
		if(Button::isCurrentButtonPressed())
		{
			Button::getCurrentButton()->doHighlight();
			//			Button::getCurrentButton()->mouseHasMoved();
		}
		return;
	}
	if(!Button::isMoveByMouse())
	{
		//		if(SDL_Object::focus==NULL) // TODO
		//		{
		SDL_Object::setHighlighted(root_object->checkHighlight(mouse)); // TODO
		//		} //else
		//		if((!temp_button)&&(Object::editFieldActive()))
		//			temp_button = Object::getEditField()->checkHighlight());
		if(SDL_Object::getHighlighted() && SDL_Object::getHighlighted() != Button::getCurrentButton())
		{
			Button::resetButton();
			Button::setCurrentButton( (Button*)SDL_Object::getHighlighted());
			Button::getCurrentButton()->mouseHasEnteredArea();
			Button::setCurrentButtonHasAlreadyLeft(false);
		}

		if(guiConfiguration->isToolTips())
		{
			// first we have to check the object with checkToolTip.
			// The result is either the object itself or one of its children that owns a tooltip

			const Object* temp = toolTipParent;
			toolTipParent = NULL;

			const Object* temp2 = ((Object*)root_object)->checkToolTip(mouse);
			if(temp2 != NULL) {
				toolTipParent = temp2;
			}
			// toolTipParent changed or tooltip has to be deleted?
			if(((toolTipParent != temp) || (tooltip == NULL)))
			{
				delete tooltip;
				if(!toolTipParent) {
					tooltip = NULL;
				}
				else 
				{	
					//					if(toolTipParent->getToolTipEString()!=NULL_STRING)
					//						tooltip = new ToolTip(root_object, toolTipParent->getToolTipEString());
					//					else
					// TODO!					tooltip = new ToolTip(root_object, toolTipParent->getToolTipString());
				}
			} else if(tooltip) {
				Point tp = mouse + Size(8, 8);
				if(tp.getX() + tooltip->getWidth() + 10 >= getMaxX()) {
					tp.setX(getMaxX() - tooltip->getWidth() - 10);
				}
				if(tp.getY() + tooltip->getHeight() + 10 >= getMaxY()) {
					tp.setY(getMaxY() - tooltip->getHeight() - 10);
				}
				tooltip->setPosition(tp);
			}

		}
	}

	if(!guiConfiguration->isToolTips() && tooltip)
	{
		delete tooltip;
		tooltip = NULL;
	}
}


void Gui::leftDown(const Point& mouse, SDL_Object* root_object)
{
	if(Button::isWasResetted()) {
		return;
	}
	if(Button::getCurrentButton() != NULL)
	{
		Button::getCurrentButton()->mouseLeftButtonPressed(mouse);
		Button::setCurrentButtonPressed();
	} else {
		SDL_Object::resetFocus();
	}
}

void Gui::leftUp(const Point& mouse, SDL_Object* root_object)
{
	if((Button::getCurrentButton()!=NULL)&&(Button::isCurrentButtonPressed())) {
		Button::getCurrentButton()->mouseLeftButtonReleased(mouse);
	}
	Button::setCurrentButtonPressed(false);
	Button::setCurrentButtonHasAlreadyLeft(false);
	setMouse(mouse, root_object);

	if(Button::isMoveByMouse()==true)
	{
		Button::setMoveByMouse(false);
		Button::setMouseMovePoint(Point(0, 0));
	}
	if(!Button::getCurrentButton()) {
		SDL_Object::resetFocus();
	}

}

void Gui::rightDown(const Point& mouse, SDL_Object* root_object)
{
	if(Button::isWasResetted()) {
		return;
	}
	if(Button::getCurrentButton()!=NULL)
	{
		Button::getCurrentButton()->mouseRightButtonPressed(mouse);
		Button::setCurrentButtonPressed();
	}
}

void Gui::rightUp(const Point& mouse, SDL_Object* root_object)
{
	if((Button::getCurrentButton()!=NULL)&&(Button::isCurrentButtonPressed())) {
		Button::getCurrentButton()->mouseRightButtonReleased(mouse);
	}
	Button::setCurrentButtonPressed(false);
	Button::setCurrentButtonHasAlreadyLeft(false);
	setMouse(mouse, root_object);
}

void Gui::wheelToTop()
{
	if(currentWindow) {
		currentWindow->moveScrollBarToTop();
	}
}

void Gui::wheelToBottom()
{
	if(currentWindow) {
		currentWindow->moveScrollBarToBottom();
	}
}

void Gui::wheelUp()
{
	if(currentWindow) {
		currentWindow->wheelUp();
	}
}

void Gui::wheelDown()
{
	if(currentWindow) {
		currentWindow->wheelDown();
	}
}

/*void Gui::setCursor(Cursor* cursor) {
SDL_SetCursor((SDL_Cursor*)cursor);
}*/

// ------------------ SOUND AND MUSIC BEGIN -----------------------
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#ifdef _FMOD_SOUND
bool ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::ostringstream os;
		os << "FMOD error! ( "<< result << ") " << FMOD_ErrorString(result);
		toErrorLog(os.str());
		return false;
	}
	return true;
}
#endif







Music* Gui::loadMusic(const std::string file_name) const
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);
	FMOD::Sound* music_data;
	FMOD_RESULT result = soundEngine->createSound(file_name.c_str(), FMOD_LOOP_NORMAL | FMOD_SOFTWARE, 0, &music_data);
	if(!ERRCHECK(result)) {
		return NULL;
	}
	//		throw SDLException("ERROR (Gui::loadMusic()): Could not load " + file_name + ".");
	//	}
#elif _SDL_MIXER_SOUND
	Mix_Music* music_data = Mix_LoadMUS(file_name.c_str());
	if(!music_data) 
	{
		return NULL;
		//		std::ostringstream os;
		//		os << "ERROR (Gui::loadMusic()): Could not load " << file_name << " : " << Mix_GetError();
		//		throw SDLException(os.str());
	}
#endif
	return new Music(music_data);
}

Sound* Gui::loadSound(const std::string file_name) const
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);
	FMOD::Sound* sound_data;
	FMOD_RESULT result = soundEngine->createSound(file_name.c_str(), FMOD_SOFTWARE, 0, &sound_data);
	if(!ERRCHECK(result)) {
		return NULL;
		//throw SDLException("ERROR (Gui::loadSound()): Could not load " + file_name + ".");
	}
#elif _SDL_MIXER_SOUND
	Mix_Chunk* sound_data = Mix_LoadWAV(file_name.c_str());
	if(!sound_data) 
	{
		return NULL;
		//		std::ostringstream os;
		//		os << "ERROR (Gui::loadSound()): Could not load " << file_name << " : " << Mix_GetError();
		//		throw SDLException(os.str());
	}
#endif
	return new Sound(sound_data);
}




void Gui::releaseSoundEngine()
{
#ifdef _FMOD_SOUND
	if(musicChannel) {
		musicChannel->stop();
	}

	if(soundEngine) {
		toInfoLog("* " + TextStorage::instance().get(textMap[END_CLOSING_SOUND_ENGINE_TEXT_ID])->getText());
		soundEngine->close();
		toInfoLog("* " + TextStorage::instance().get(textMap[END_RELEASING_SOUND_ENGINE_TEXT_ID])->getText());
		soundEngine->release();
		delete soundEngine;
		soundEngine = NULL;
	}
#elif _SDL_MIXER_SOUND
	Mix_HaltMusic();
	toInfoLog("* " + TextStorage::instance().get(textMap[END_CLOSING_SOUND_ENGINE_TEXT_ID])->getText());
	Mix_CloseAudio();
#endif
	soundInitialized = false;
}



void Gui::printSoundInformation() const
{
#ifdef _FMOD_SOUND
	FMOD_RESULT result;
	int driver_num;
	result = soundEngine->getNumDrivers(&driver_num);
	ERRCHECK(result);

	std::ostringstream os; os << "* Available sound drivers: ";
	for(unsigned int i = driver_num; i--;)
	{
		char driver_name[256];
		result = soundEngine->getDriverInfo(i, driver_name, 256, 0);
		ERRCHECK(result);
		os << driver_name << " ";
	}
	toInfoLog(os.str());
	os.str("");
	int current_driver;
	result = soundEngine->getDriver(&current_driver);
	ERRCHECK(result);

	os << "* Driver used: ";
	if(current_driver == -1)
	{
		os << "Primary or main sound device as selected by the operating system settings";
		if(driver_num == 1)
		{
			char driver_name[256];
			result = soundEngine->getDriverInfo(current_driver, driver_name, 256, 0);
			ERRCHECK(result);
			os << "(probably '" << driver_name << "')";
		}
	}
	else
	{
		char driver_name[256];
		result = soundEngine->getDriverInfo(current_driver, driver_name, 256, 0);
		ERRCHECK(result);
		os << driver_name;
	}
	toInfoLog(os.str());
#elif _SDL_MIXER_SOUND
	int audio_rate, audio_channels;
	Uint16 audio_format;
	int success = Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
	BOOST_ASSERT(success);
	/*#ifdef _SCC_DEBUG
	if(!success) {
	std::ostringstream os;
	os << "ERROR (Gui::printSoundInformation()): " << Mix_GetError();
	throw SDLException(os.str());
	}
	#endif*/
	int bits = audio_format & 0xFF;
	std::ostringstream os; 
	os << "* Opened audio at " << audio_rate << "Hz " << bits << "bit " << ((audio_channels>1)?"stereo":"mono");// << ", " << audio_buffers << " bytes audio buffer";
	toInfoLog(os.str());
#endif
}

#ifdef _SDL_MIXER_SOUND
void transitionMusic(void)
{
	Gui::transitionMusic();
}

void soundChannelDone(int channel)
{
	Gui::soundChannelDone(channel);
}

// callback function
void Gui::transitionMusic(void)
{
	if(currentMusic != NULL)
	{
		Mix_HaltMusic(); // Just in case there was a misunderstanding, halt the music
		Mix_FreeMusic(currentMusic);
		currentMusic = nextMusic;
		nextMusic = NULL;
		if(currentMusic != NULL)
		{
			int success = Mix_FadeInMusic(currentMusic, -1, MUSIC_TRANSITION_DURATION/2);
			BOOST_ASSERT(success == 0);
			/*#ifdef _SCC_DEBUG
			if(success != 0) {
			std::ostringstream os;
			os << "ERROR (Gui::playMusic()): " << Mix_GetError();
			throw SDLException(os.str());
			}
			#endif*/
		}
	}
}

void Gui::soundChannelDone(int channel)
{
	for(std::list<int>::iterator i = soundChannel.begin(); i != soundChannel.end();)
	{
		if(*i == channel) {
			i = soundChannel.erase(i);
		}
		else ++i;
	}
}
#endif


void Gui::initSoundEngine()
{
	// TODO start a 'watchdog' thread (FMOD waits indefinitely if the sound is currently used!)
	toInfoLog(TextStorage::instance().get(textMap[START_INIT_SOUND_TEXT_ID])->getText());

#ifdef _FMOD_SOUND
	unsigned int version;

	if(!ERRCHECK(FMOD::System_Create(&soundEngine))) { 
		throw SDLException(TextStorage::instance().get(textMap[START_INIT_FMOD_SYSTEM_CREATE_ERROR_TEXT_ID])->getText());
	}

	BOOST_ASSERT(soundEngine);
	if(!ERRCHECK(soundEngine->getVersion(&version))) {
		throw SDLException(TextStorage::instance().get(textMap[START_INIT_FMOD_GET_VERSION_ERROR_TEXT_ID])->getText());
	}

	if (version < FMOD_VERSION)
	{
		std::ostringstream os;
		os << TextStorage::instance().get(textMap[START_INIT_FMOD_VERSION_ERROR_TEXT_ID])->getText() << "[" << version << " < " << FMOD_VERSION << "]";
		throw SDLException(os.str());
	}

	printSoundInformation();

	if(!ERRCHECK(soundEngine->init(32, FMOD_INIT_NORMAL, 0))) {
		throw SDLException(TextStorage::instance().get(textMap[START_INIT_FMOD_SYSTEM_INIT_ERROR_TEXT_ID])->getText());
	}
#elif _SDL_MIXER_SOUND
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048)==-1) 
	{
		std::ostringstream os;
		os << "ERROR (Gui::initSoundEngine()): " << Mix_GetError();
		throw SDLException(os.str());
	}		
	Mix_ChannelFinished(::soundChannelDone);
#endif
	soundInitialized = true;
}




void Gui::processSoundChannels()
{
#ifdef _FMOD_SOUND
	for(std::list<FMOD::Channel*>::iterator i = soundChannel.begin(); i!=soundChannel.end();)
	{
		bool is_playing = false;
		(*i)->isPlaying(&is_playing);
		if(!is_playing) {
			i = soundChannel.erase(i);
		}
		else ++i;
	}
	for(std::list<std::pair<Sound*, float> >::iterator i = soundsToPlay.begin(); i != soundsToPlay.end(); ++i)
		if((soundChannel.size() < getSoundChannels()))
		{
			FMOD::Channel* mychannel = NULL;
			soundEngine->playSound(FMOD_CHANNEL_FREE, (FMOD::Sound*)(i->first), 0, &mychannel);
			mychannel->setPan(i->second);
			mychannel->setVolume((float)(getSoundVolume()/100.0));
			soundChannel.push_back(mychannel);
		}
#elif _SDL_MIXER_SOUND
	for(std::list<std::pair<Sound*, float> >::iterator i = soundsToPlay.begin(); i != soundsToPlay.end(); ++i)
		if((soundChannel.size() < getSoundChannels()))
		{
			int mychannel = -1;
			mychannel = Mix_PlayChannel(-1, (Mix_Chunk*)(i->first), 0);
			if(mychannel == -1) {
				std::ostringstream os;
				os << "ERROR (Gui::processSoundChannels()): " << Mix_GetError();
				throw SDLException(os.str());
			} else
			{
				//				mychannel->setPan(i->second);
				//				mychannel->setVolume((float)(getSoundVolume())/100.0);
				soundChannel.push_back(mychannel);
			}
		}
#endif
}



void Gui::stopMusic()
{
	playMusic(NULL);
}



void Gui::clearSoundChannels()
{
	soundChannel.clear();
}

void Gui::clearSoundsToPlay()
{
	soundsToPlay.clear();
}


void Gui::playSound(Sound* play_sound, const unsigned int x)
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);
#endif
	soundsToPlay.push_back(std::pair<Sound*, float>(play_sound, 2*((float)(2*x) - (float)getMaxX())/(float)(3*getMaxX())));
}



void Gui::playMusic(Music* play_music, const bool loop)
{

#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);

	if(musicChannel) {
		musicChannel->stop();
	}
	soundEngine->playSound(FMOD_CHANNEL_FREE, (FMOD::Sound*)play_music, 0, &musicChannel);

#elif _SDL_MIXER_SOUND

	int success = -1;

	// music currently playing?
	if(currentMusic != NULL)
	{
		// new music?
		if(play_music != NULL) {
			if(loop) {
				nextMusic = currentMusic;
			} else {
				nextMusic = NULL;
			}
			// transition between both music plays
			Mix_HookMusicFinished(::transitionMusic);
			success = Mix_FadeOutMusic(MUSIC_TRANSITION_DURATION/2);
		} else 
			// empty music => Stop music, just fade out
		{
			success = Mix_FadeOutMusic(MUSIC_TRANSITION_DURATION);
		}
	} else 
		// no music was playing
	{
		if(play_music != NULL)
		{
			currentMusic = (Mix_Music*)play_music;
			if(loop) {
				nextMusic = currentMusic;
			} else {
				nextMusic = NULL;
			}

			Mix_HookMusicFinished(::transitionMusic);
			success = Mix_FadeInMusic(currentMusic, -1, MUSIC_TRANSITION_DURATION);
		} else {
			// no music played, no music to play
			success = 0;
		}
	}
	if(success != 0) {
		std::ostringstream os;
		os << "ERROR (Gui::playMusic()): " << Mix_GetError();
		toErrorLog(os.str());
		//throw MyException(os.str());
	}
#endif
}

std::list<int> Gui::soundChannel;
Mix_Music* Gui::currentMusic;
Mix_Music* Gui::nextMusic;
#endif

// ------------------ SOUND AND MUSIC END -----------------------


void Gui::process() {
	if(!windowSelected) {
		currentWindow = NULL;
	}

	BOOST_ASSERT(dc);
	SDL_Object::processAll();
	SDL_Object::redrawnObjects = 0;
	SDL_Object::updateAreasToUpdate();
	SDL_Object::drawAll(dc);
	dc->updateScreen();
	// frameRateControl.updateConfiguration(); TODO
	//inline void Gui::poll(const eTicks etick) {
	//	frameRateControl.poll(etick);
	//}

	// ------ SOUND ENGINE -------
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	if((isSound() || isMusic()) && (!soundInitialized))
	{
		try {
			initSoundEngine();
		} catch(MyException e) {
			setSound(false);
			setMusic(false);
			soundInitialized = false;
			toInfoLog(TextStorage::instance().get(textMap[START_INIT_NOSOUND_TEXT_ID])->getText());
		}
	} else if(!isSound() && !isMusic() && soundInitialized) {
		releaseSoundEngine();
	} else 
		if(!soundInitialized) {
			if(!isMusic()) {
				stopMusic();
			}

			if(isSound()) {
				processSoundChannels();
			} else {
				clearSoundChannels();
			}
#ifdef _FMOD_SOUND
			soundEngine->update();
#endif
		}
		clearSoundsToPlay();
#endif		
		//		m.poll(SOUND_TICKS); TODO
		// ------ END SOUND ENGINE -------
}


std::map<const eTextId, const boost::uuids::uuid> Gui::initTextMap() {
	std::map<const eTextId, const boost::uuids::uuid> text_map;
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_SDL_TEXT_ID, Misc::uuid("e438cdf0-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SET_FULLSCREEN_MODE_TEXT_ID, Misc::uuid("e81f08d0-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SET_WINDOW_MODE_TEXT_ID, Misc::uuid("eaf4be10-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_UNABLE_TO_INIT_SDL_TEXT_ID, Misc::uuid("ed5ee040-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_ERROR_SETTING_VIDEO_MODE_TEXT_ID, Misc::uuid("f4d74290-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_CREATED_SURFACE_TEXT_ID, Misc::uuid("f82227d0-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_SDL_TRUETYPE_FONTS_TEXT_ID, Misc::uuid("fe0e1dc0-4b5b-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_SDL_TTF_ERROR_TEXT_ID, Misc::uuid("00eb4d10-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_LOAD_CONFIGURATION_TEXT_ID, Misc::uuid("036bb660-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_RESET_MOUSE_CURSOR_TEXT_ID, Misc::uuid("05d4a010-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_FREEING_COLORS_BRUSHES_PENS_TEXT_ID, Misc::uuid("080ba450-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_FREEING_BITMAPS_TEXT_ID, Misc::uuid("0a8c82d0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_FREEING_ANIMATIONS_TEXT_ID, Misc::uuid("0ddf3040-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_FREEING_COORDINATES_TEXT_ID, Misc::uuid("10600ec0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_FREEING_BUTTONS_TEXT_ID, Misc::uuid("138e6b50-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_FREEING_FONTS_TEXT_ID, Misc::uuid("16265440-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_NO_MODES_AVAILABLE_TEXT_ID, Misc::uuid("18ecee50-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_ALL_RESOLUTIONS_AVAILABLE_TEXT_ID, Misc::uuid("1b3cf8d0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_AVAILABLE_MODES_TEXT_ID, Misc::uuid("1d8d5170-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_MAX_COLOR_DEPTH_TEXT_ID, Misc::uuid("1fbbf140-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_HARDWARE_SURFACES_POSSIBLE_TEXT_ID, Misc::uuid("222ec600-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_WINDOW_MANAGER_AVAILABLE_TEXT_ID, Misc::uuid("24a2d340-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SOFTWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID, Misc::uuid("26f74a90-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SOFTWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID, Misc::uuid("29525190-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SOFTWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID, Misc::uuid("2bd971a0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_HARDWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID, Misc::uuid("2e3a6c10-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_HARDWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID, Misc::uuid("30923ec0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_HARDWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID, Misc::uuid("32d81010-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_COLOR_FILLS_ACCELERATED_TEXT_ID, Misc::uuid("35024310-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_TOTAL_VIDEO_MEMORY_TEXT_ID, Misc::uuid("38e0dcd0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_STORED_IN_SYSTEM_MEMORY_TEXT_ID, Misc::uuid("3b90ba90-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_STORED_IN_VIDEO_MEMORY_TEXT_ID, Misc::uuid("3dbfcf90-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_USES_ASYNCHRONOUS_BLITS_TEXT_ID, Misc::uuid("42b5f3d0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_ALLOWS_ANY_PIXEL_FORMAT_TEXT_ID, Misc::uuid("452bd5d0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_HAS_EXCLUSIVE_PALETTE_TEXT_ID, Misc::uuid("47718010-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_IS_DOUBLE_BUFFERED_TEXT_ID, Misc::uuid("49a43e90-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_HAS_OPENGL_CONTEXT_TEXT_ID, Misc::uuid("4bb914d0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_SUPPORTS_OPENGL_BLITTING_TEXT_ID, Misc::uuid("4e671dd0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_IS_RESIZABLE_TEXT_ID, Misc::uuid("50817250-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_BLIT_USES_HARDWARE_ACCELERATION_TEXT_ID, Misc::uuid("5350bef0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_USES_COLORKEY_BLITTING_TEXT_ID, Misc::uuid("56552550-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_COLORKEY_BLITTING_RLE_ACCELERATED_TEXT_ID, Misc::uuid("58db8210-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_BLIT_USES_ALPHA_BLENDING_TEXT_ID, Misc::uuid("5b80ff90-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_USES_PREALLOCATED_MEMORY_TEXT_ID, Misc::uuid("5dcdfcd0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_SDL_SURFACE_NEEDS_LOCKING_TEXT_ID, Misc::uuid("600cf050-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_RELEASING_SOUND_ENGINE_TEXT_ID, Misc::uuid("62a6d510-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(END_CLOSING_SOUND_ENGINE_TEXT_ID, Misc::uuid("64d06bd0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_SOUND_TEXT_ID, Misc::uuid("66fac5e0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_FMOD_SYSTEM_CREATE_ERROR_TEXT_ID, Misc::uuid("6966e3e0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_FMOD_GET_VERSION_ERROR_TEXT_ID, Misc::uuid("6ba9f610-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_FMOD_VERSION_ERROR_TEXT_ID, Misc::uuid("6de2cf10-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_FMOD_SYSTEM_INIT_ERROR_TEXT_ID, Misc::uuid("70b4b3c0-4b5c-11e0-b8af-0800200c9a66")));
	text_map.insert(std::pair<const eTextId, const boost::uuids::uuid>(START_INIT_NOSOUND_TEXT_ID, Misc::uuid("73009f90-4b5c-11e0-b8af-0800200c9a66")));
	return text_map;
}

std::string Gui::GVERSION = "2.00";
std::map<const eTextId, const boost::uuids::uuid> Gui::textMap = Gui::initTextMap();
