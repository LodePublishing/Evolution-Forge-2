#include "init.hpp"

#include <misc/exceptions.hpp>
#include <misc/log.hpp>

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#define MUSIC_TRANSITION_DURATION 2000
#endif 

#ifdef _FMOD_SOUND
	#include <fmod.hpp>
	#include <fmod_errors.h>
#endif


#include <lang/languagestorage.hpp>

Init::Init(int argc, char *argv[]) {
	
	std::list<std::string> arguments;
	for(signed int i = 1;i<argc;++i) {
		arguments.push_back(argv[i]);
	}

	std::string current_driver;
	if(getenv("SDL_VIDEODRIVER")!=NULL) {
		current_driver = getenv("SDL_VIDEODRIVER");
	}	

	/*
	const std::list<std::string>& parameter_list, const std::string& window_title) : 
	Configuration(IO:getDirectory(boost::assign::list_of("data")("base")("settings")) + "ui.cfg"),
	dc(NULL),
#ifdef _FMOD_SOUND
	soundEngine(NULL),
	musicChannel(NULL),
#endif
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	soundInitialized(true),
#endif
{
// ------ INIT SDL AND WINDOW ------
*/
	toInfoLog("* " + LanguageStorage::instance().get(START_INIT_SDL_IDENTIFIER));
	toInfoLog("* " + LanguageStorage::instance().get(START_AVAILABLE_GRAPHIC_DRIVERS_IDENTIFIER));

	std::ostringstream os;
	os << "* " << LanguageStorage::instance().get(START_AVAILABLE_GRAPHIC_DRIVERS_IDENTIFIER);
	std::list<std::string> s = DC::getAvailableDrivers();
	for(std::list<std::string>::const_iterator i = s.begin(); i!=s.end(); i++) {
		os << *i << " ";
	}
	toInfoLog(os.str());


	std::string selected_driver;
	bool no_vo_argument = false;
	for(std::list<std::string>::const_iterator i = parameter_list.begin(); i != parameter_list.end(); ++i) {
		if((*i) == "-vo")
		{
			i++;
			if(i == parameter_list.end()) {
				no_vo_argument = true;
			}
			else {
				selected_driver = *i;
			}
			break;
		}
	}

	std::string chosen_driver;
	switch(DC::chooseDriver(chosen_driver, selected_driver))
	{
		case DRIVER_SUCCESS:toInfoLog("* " + LanguageStorage::instance().get(START_SDL_USING_DRIVER_IDENTIFIER)->, chosen_driver));break;
		case NO_VIDEO_DRIVERS_AVAILABLE:throw SDLException("* " + LanguageStorage::instance().get(START_ERROR_NO_DRIVER_AVAILABLE_IDENTIFIER));
		case SDL_DRIVER_NOT_SUPPORTED:throw SDLException("* " + lookUpFormattedString("START_ERROR_DRIVER_NOT_SUPPORTED_IDENTIFIER, chosen_driver));
	}

	Uint32 flags = SDL_HWSURFACE|SDL_ASYNCBLIT|SDL_HWACCEL|SDL_HWPALETTE|SDL_SRCCOLORKEY|SDL_RLEACCEL|SDL_SRCALPHA|SDL_PREALLOC|SDL_DOUBLEBUF;

	toInfoLog("* " + LanguageStorage::instance().get(isFullScreen() ? "START_SET_FULLSCREEN_MODE_IDENTIFIER : "START_SET_WINDOW_MODE_IDENTIFIER));
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

	dc = new DC(chosen_driver.c_str());
	BOOST_ASSERT(dc);
	try {
		dc->initSDL(resolution_size, bit_depth, flags, nflags);
	} catch(...) {
		delete dc;
		dc = NULL;
		throw SDLException(LanguageStorage::instance().get("START_UNABLE_TO_INIT_SDL_IDENTIFIER) + " [SDL ERROR: \"" + SDL_GetError() + "\"]");
	}
	
	if ( !dc->valid() ) {
		delete dc;
		dc = NULL;
		throw SDLException(LanguageStorage::instance().get("START_ERROR_SETTING_VIDEO_MODE_IDENTIFIER) + " [SDL ERROR: \"" + SDL_GetError() + "\"]");
	}

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	toInfoLog(printHardwareInformation());
	toInfoLog("* " + LanguageStorage::instance().get("START_CREATED_SURFACE_IDENTIFIER) + " " + printSurfaceInformation(dc));
// ------ END INIT SDL AND WINDOW ------

	SDL_WM_SetCaption(window_title.c_str(),"");

// ------ INIT SDL_TTF ------
	toInfoLog("* " + LanguageStorage::instance().get("START_INIT_SDL_TRUETYPE_FONTS_IDENTIFIER));
	if(TTF_Init()==-1) {
		delete dc;
		dc = NULL;
		throw SDLException(LanguageStorage::instance().get("START_INIT_SDL_TTF_ERROR_IDENTIFIER) + " [\"" + TTF_GetError() + "\"]");
	}
	atexit(TTF_Quit); 
// ------ END INIT SDL_TTF ------

// ------ INIT SOUND ENGINE -------
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	if(isSound() || isMusic())
	{
		try {
			initSoundEngine();
		} catch(SDLException e) {
			setSound(false);
			setMusic(false);
			soundInitialized = false;
		}
	} else {
		toInfoLog(LanguageStorage::instance().get("START_INIT_NOSOUND_IDENTIFIER));
	}
#endif
// ------ END INIT SOUND ENGINE -------
}



Init::~Init()
{
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	releaseSoundEngine();
#endif

//	toInfoLog("* " + LanguageStorage::instance().get("END_RESET_MOUSE_CURSOR_IDENTIFIER));
//	SDL_SetCursor(defaultCursor);

// TODO: Jeder Mauszeiger der benutzt wurde verursacht bei SDL_FreeCursor einen segfault :/ (bzw. 'wurde schon geloescht' Fehler der glibc
//	for(unsigned int i = MAX_CURSORS; i--;)
//		for(unsigned int j = 2; j--;)
//	SDL_FreeCursor(cursorList[ARROW_CURSOR][0]);
//	SDL_FreeCursor(cursorList[HAND_CURSOR][0]);
//	SDL_FreeCursor(cursorList[CLOCK_CURSOR][0]);
//	SDL_FreeCursor(cursorList[CLOCK_CURSOR][1]);

/*	toInfoLog("* " + LanguageStorage::instance().get(END_FREEING_COLORS_BRUSHES_PENS_IDENTIFIER));
	for(unsigned int i = MAX_COLOR_THEMES;i--;)
	{
		for(unsigned int j = MAX_COLORS;j--;)
			delete colorList[i][j];
		for(unsigned int j = MAX_BRUSHES;j--;)
			delete brushList[i][j];
		for(unsigned int j = MAX_PENS;j--;)
			delete penList[i][j];
	}

	toInfoLog("* " + LanguageStorage::instance().get(END_FREEING_BITMAPS_IDENTIFIER));
	for(std::list<BitmapEntry>::iterator l = loadedBitmaps.begin(); l!=loadedBitmaps.end();++l) {
		SDL_FreeSurface(l->bitmap);
	}

#ifdef USE_SMPEG
	toInfoLog("* " + LanguageStorage::instance().get(END_FREEING_ANIMATIONS_IDENTIFIER));
	for(std::list<AnimationEntry>::iterator l = loadedAnimations.begin(); l!=loadedAnimations.end();++l)
		if(l->animation)
			SMPEG_delete(l->animation);
#endif

	toInfoLog("* " + LanguageStorage::instance().get(END_FREEING_COORDINATES_IDENTIFIER));
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

	toInfoLog("* " + LanguageStorage::instance().get(END_FREEING_BUTTONS_IDENTIFIER));
	for(unsigned int i=MAX_BUTTON_COLORS_TYPES;i--;)
		delete buttonColorsList[i];

	toInfoLog("* " + LanguageStorage::instance().get(END_FREEING_FONTS_IDENTIFIER));
	for(unsigned int i = MAX_RESOLUTIONS;i--;)
//		for(unsigned int j = MAX_LANGUAGES;j--;)
			for(unsigned int k = MAX_FONTS;k--;)
				delete fontList[i][k];
*/
}

void Init::addMessage(const std::string& msg)
{
	remainingMessages.push_back(msg);
}



std::string Init::printHardwareInformation()
{
	// TODO: uebersetzen bzw. dem Aufrufer nur Daten uebergeben
	SDL_Rect **modes;
	std::ostringstream os;
	os.str("");
	modes = SDL_ListModes(NULL, SDL_SWSURFACE);
	if(modes == (SDL_Rect **)0) {
		os << "* " << LanguageStorage::instance().get("START_SDL_NO_MODES_AVAILABLE_IDENTIFIER) << std::endl;
	}
	else
	{
		if(modes == (SDL_Rect **)-1) {
			os << "* " << LanguageStorage::instance().get("START_SDL_ALL_RESOLUTIONS_AVAILABLE_IDENTIFIER) << std::endl;
		} else
		{
			os << "* " << LanguageStorage::instance().get("START_SDL_AVAILABLE_MODES_IDENTIFIER);
			for(unsigned int i=0; modes[i]; ++i) {
				os << "  " << modes[i]->w << " x " << modes[i]->h;
			}
			os << std::endl;
		}
	}
	const SDL_VideoInfo* hardware = SDL_GetVideoInfo();
	os << " - " << LanguageStorage::instance().get("START_SDL_MAX_COLOR_DEPTH_IDENTIFIER) << (unsigned int)hardware->vfmt->BitsPerPixel;
//	if(hardware->hw_available) os << "\n- " << LanguageStorage::instance().get("START_SDL_HARDWARE_SURFACES_POSSIBLE_IDENTIFIER);
	if(hardware->wm_available) os << "\n - " << LanguageStorage::instance().get("START_SDL_WINDOW_MANAGER_AVAILABLE_IDENTIFIER);
	if(hardware->blit_hw) os << "\n - " << LanguageStorage::instance().get("START_SDL_HARDWARE_TO_HARDWARE_BLITS_ACCELERATED_IDENTIFIER);
	if(hardware->blit_hw_CC) os << "\n - " << LanguageStorage::instance().get("START_SDL_HARDWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_IDENTIFIER);
	if(hardware->blit_hw_A) os << "\n - " << LanguageStorage::instance().get("START_SDL_HARDWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_IDENTIFIER);
	if(hardware->blit_sw) os << "\n - " << LanguageStorage::instance().get("START_SDL_SOFTWARE_TO_HARDWARE_BLITS_ACCELERATED_IDENTIFIER);
	if(hardware->blit_sw_CC) os << "\n - " << LanguageStorage::instance().get("START_SDL_SOFTWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_IDENTIFIER);
	if(hardware->blit_sw_A)	os << "\n - " << LanguageStorage::instance().get("START_SDL_SOFTWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_IDENTIFIER);
	if(hardware->blit_fill)	os << "\n - " << LanguageStorage::instance().get("START_SDL_COLOR_FILLS_ACCELERATED_IDENTIFIER);
	if(hardware->video_mem>0) os << "\n - " << lookUpFormattedString("START_SDL_TOTAL_VIDEO_MEMORY_IDENTIFIER, hardware->video_mem);
//	Total amount of video memory: " << hardware->video_mem << "kb";
	return os.str();
}





// after a bit-depth change
/*void Init::updateColors(SDL_Surface* surface)
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



std::string Init::printSurfaceInformation(DC* surface)
{
	std::ostringstream os; os.str("");
	os << surface->getSurface()->w << " x " << surface->getSurface()->h << " @ " << (unsigned int)(surface->getSurface()->format->BitsPerPixel);
	if (surface->flags() & SDL_SWSURFACE) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_STORED_IN_SYSTEM_MEMORY_IDENTIFIER);
	//Surface is stored in system memory";
	else if(surface->flags() & SDL_HWSURFACE) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_STORED_IN_VIDEO_MEMORY_IDENTIFIER);
//			Surface is stored in video memory";
	if(surface->flags() & SDL_ASYNCBLIT) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_USES_ASYNCHRONOUS_BLITS_IDENTIFIER);
	//urface uses asynchronous blits if possible";
	if(surface->flags() & SDL_ANYFORMAT) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_ALLOWS_ANY_PIXEL_FORMAT_IDENTIFIER);
	if(surface->flags() & SDL_HWPALETTE) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_HAS_EXCLUSIVE_PALETTE_IDENTIFIER);
	if(surface->flags() & SDL_DOUBLEBUF) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_IS_DOUBLE_BUFFERED_IDENTIFIER);
	if(surface->flags() & SDL_OPENGL) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_HAS_OPENGL_CONTEXT_IDENTIFIER);
	if(surface->flags() & SDL_OPENGLBLIT) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_SUPPORTS_OPENGL_BLITTING_IDENTIFIER);
	if(surface->flags() & SDL_RESIZABLE) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_IS_RESIZABLE_IDENTIFIER);
	if(surface->flags() & SDL_HWACCEL) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_BLIT_USES_HARDWARE_ACCELERATION_IDENTIFIER);
	//Surface blit uses hardware acceleration";
	if(surface->flags() & SDL_SRCCOLORKEY) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_USES_COLORKEY_BLITTING_IDENTIFIER);
	//Surface use colorkey blitting";
	if(surface->flags() & SDL_RLEACCEL) os << "\n- " << LanguageStorage::instance().get("START_SDL_COLORKEY_BLITTING_RLE_ACCELERATED_IDENTIFIER);
	//Colorkey blitting is accelerated with RLE";
	if(surface->flags() & SDL_SRCALPHA) os << "\n- " << LanguageStorage::instance().get("START_SDL_BLIT_USES_ALPHA_BLENDING_IDENTIFIER);
//	Surface blit uses alpha blending";
	if(surface->flags() & SDL_PREALLOC) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_USES_PREALLOCATED_MEMORY_IDENTIFIER);
	if(SDL_MUSTLOCK(surface->getSurface())) os << "\n- " << LanguageStorage::instance().get("START_SDL_SURFACE_NEEDS_LOCKING_IDENTIFIER);
	return os.str();
}



//void Init::animateWaitCursor();

void Init::loadConfigurationFile()
{
	// TODO sound?
	toInfoLog(LanguageStorage::instance().get("START_LOAD_CONFIGURATION_IDENTIFIER));
	Configuration::loadConfigurationFile();
	if(hasScreenChanged()) {
		BOOST_ASSERT(dc);
		dc->setScreen(Configuration::getResolutionSize(), Configuration::getBitDepth(), dc->flags() | SDL_FULLSCREEN);
	}
	// TODO load string files...
}



bool Init::setResolutionSize(const Size& size) {
	if(!dc) {
		return Configuration::setResolutionSize(size);
	}
	Configuration::setResolutionSize(size);
	return dc->setResolution(size);
}

bool Init::setBitDepth(const eBitDepth bit_depth) {
	if(!dc) {
		return Configuration::setBitDepth(bit_depth);
	}
	Configuration::setBitDepth(bit_depth);
	return dc->setBitDepth(bit_depth);
}

bool Init::setFullScreen(const bool full_screen) {
	if(!dc) {
		return Configuration::setFullScreen(full_screen);
	}
	Configuration::setFullScreen(full_screen);
	return dc->setFullScreen(full_screen);
}



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







Music* Init::loadMusic(const std::string file_name) const
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);
	FMOD::Sound* music_data;
	FMOD_RESULT result = soundEngine->createSound(file_name.c_str(), FMOD_LOOP_NORMAL | FMOD_SOFTWARE, 0, &music_data);
	if(!ERRCHECK(result)) {
		return NULL;
	}
//		throw SDLException("ERROR (Init::loadMusic()): Could not load " + file_name + ".");
//	}
#elif _SDL_MIXER_SOUND
	Mix_Music* music_data = Mix_LoadMUS(file_name.c_str());
	if(!music_data) 
	{
		return NULL;
//		std::ostringstream os;
//		os << "ERROR (Init::loadMusic()): Could not load " << file_name << " : " << Mix_GetError();
//		throw SDLException(os.str());
	}
#endif
	return new Music(music_data);
}

Sound* Init::loadSound(const std::string file_name) const
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);
	FMOD::Sound* sound_data;
	FMOD_RESULT result = soundEngine->createSound(file_name.c_str(), FMOD_SOFTWARE, 0, &sound_data);
	if(!ERRCHECK(result)) {
		return NULL;
		//throw SDLException("ERROR (Init::loadSound()): Could not load " + file_name + ".");
	}
#elif _SDL_MIXER_SOUND
	Mix_Chunk* sound_data = Mix_LoadWAV(file_name.c_str());
	if(!sound_data) 
	{
		return NULL;
//		std::ostringstream os;
//		os << "ERROR (Init::loadSound()): Could not load " << file_name << " : " << Mix_GetError();
//		throw SDLException(os.str());
	}
#endif
	return new Sound(sound_data);
}




void Init::releaseSoundEngine()
{
#ifdef _FMOD_SOUND
	if(musicChannel) {
		musicChannel->stop();
	}

	if(soundEngine) {
		toInfoLog("* " + LanguageStorage::instance().get("END_CLOSING_SOUND_ENGINE_IDENTIFIER));
		soundEngine->close();
		toInfoLog("* " + LanguageStorage::instance().get("END_RELEASING_SOUND_ENGINE_IDENTIFIER));
		soundEngine->release();
		delete soundEngine;
		soundEngine = NULL;
	}
#elif _SDL_MIXER_SOUND
	Mix_HaltMusic();
	toInfoLog("* " + LanguageStorage::instance().get("END_CLOSING_SOUND_ENGINE_IDENTIFIER));
	Mix_CloseAudio();
#endif
	soundInitialized = false;
}



void Init::printSoundInformation() const
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
		os << "ERROR (Init::printSoundInformation()): " << Mix_GetError();
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
	Init::transitionMusic();
}

void soundChannelDone(int channel)
{
	Init::soundChannelDone(channel);
}

// callback function
void Init::transitionMusic(void)
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
				os << "ERROR (Init::playMusic()): " << Mix_GetError();
				throw SDLException(os.str());
			}
#endif*/
		}
	}
}

void Init::soundChannelDone(int channel)
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


void Init::initSoundEngine()
{
	// TODO start a 'watchdog' thread (FMOD waits indefinitely if the sound is currently used!)
	toInfoLog(LanguageStorage::instance().get("START_INIT_SOUND_IDENTIFIER));

#ifdef _FMOD_SOUND
	unsigned int version;
	
	if(!ERRCHECK(FMOD::System_Create(&soundEngine))) { 
		throw SDLException(LanguageStorage::instance().get("START_INIT_FMOD_SYSTEM_CREATE_ERROR_IDENTIFIER));
	}

	BOOST_ASSERT(soundEngine);
	if(!ERRCHECK(soundEngine->getVersion(&version))) {
		throw SDLException(LanguageStorage::instance().get("START_INIT_FMOD_GET_VERSION_ERROR_IDENTIFIER));
	}

	if (version < FMOD_VERSION)
    {
		std::ostringstream os;
		os << LanguageStorage::instance().get("START_INIT_FMOD_VERSION_ERROR_IDENTIFIER) << "[" << version << " < " << FMOD_VERSION << "]";
		throw SDLException(os.str());
	}

	printSoundInformation();

	if(!ERRCHECK(soundEngine->init(32, FMOD_INIT_NORMAL, 0))) {
		throw SDLException(LanguageStorage::instance().get("START_INIT_FMOD_SYSTEM_INIT_ERROR_IDENTIFIER));
	}
#elif _SDL_MIXER_SOUND
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048)==-1) 
	{
		std::ostringstream os;
		os << "ERROR (Init::initSoundEngine()): " << Mix_GetError();
		throw SDLException(os.str());
	}		
	Mix_ChannelFinished(::soundChannelDone);
#endif
	soundInitialized = true;
}




void Init::processSoundChannels()
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
				os << "ERROR (Init::processSoundChannels()): " << Mix_GetError();
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



void Init::stopMusic()
{
	playMusic(NULL);
}



void Init::clearSoundChannels()
{
	soundChannel.clear();
}

void Init::clearSoundsToPlay()
{
	soundsToPlay.clear();
}


void Init::playSound(Sound* play_sound, const unsigned int x)
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(soundEngine);
#endif
	soundsToPlay.push_back(std::pair<Sound*, float>(play_sound, 2*((float)(2*x) - (float)getMaxX())/(float)(3*getMaxX())));
}



void Init::playMusic(Music* play_music, const bool loop)
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
		os << "ERROR (Init::playMusic()): " << Mix_GetError();
		toErrorLog(os.str());
		//throw MyException(os.str());
	}
#endif
}

std::list<int> Init::soundChannel;
Mix_Music* Init::currentMusic;
Mix_Music* Init::nextMusic;
#endif

// ------------------ SOUND AND MUSIC END -----------------------


std::string Init::GVERSION = "2.00";
