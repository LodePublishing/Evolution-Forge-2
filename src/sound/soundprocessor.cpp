
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
#define MUSIC_TRANSITION_DURATION 2000
#endif 

#ifdef _FMOD_SOUND
#include <fmod.hpp>
#include <fmod_errors.h>
#endif

#ifdef _FMOD_SOUND
	,soundEngine(NULL),
	musicChannel(NULL)
#endif
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	,soundInitialized(false)
#endif

TODO separate sound processor
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
		toInfoLog(TextStorage::instance().get(IDS::START_INIT_NOSOUND_TEXT_ID)->getText());
	}
#endif
	// ------ END INIT SOUND ENGINE -------



SoundProcessor::~SoundProcessor() {
#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)
	releaseSoundEngine();
#endif
}

void SoundProcessor::process() {
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
			toInfoLog(TextStorage::instance().get(IDS::START_INIT_NOSOUND_TEXT_ID)->getText());
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
		toInfoLog("* " + TextStorage::instance().get(IDS::END_CLOSING_SOUND_ENGINE_TEXT_ID)->getText());
		soundEngine->close();
		toInfoLog("* " + TextStorage::instance().get(IDS::END_RELEASING_SOUND_ENGINE_TEXT_ID)->getText());
		soundEngine->release();
		delete soundEngine;
		soundEngine = NULL;
	}
#elif _SDL_MIXER_SOUND
	Mix_HaltMusic();
	toInfoLog("* " + TextStorage::instance().get(IDS::END_CLOSING_SOUND_ENGINE_TEXT_ID)->getText());
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
	toInfoLog(TextStorage::instance().get(IDS::START_INIT_SOUND_TEXT_ID)->getText());

#ifdef _FMOD_SOUND
	unsigned int version;

	if(!ERRCHECK(FMOD::System_Create(&soundEngine))) { 
		throw SDLException(TextStorage::instance().get(IDS::START_INIT_FMOD_SYSTEM_CREATE_ERROR_TEXT_ID)->getText());
	}

	BOOST_ASSERT(soundEngine);
	if(!ERRCHECK(soundEngine->getVersion(&version))) {
		throw SDLException(TextStorage::instance().get(IDS::START_INIT_FMOD_GET_VERSION_ERROR_TEXT_ID)->getText());
	}

	if (version < FMOD_VERSION)
	{
		std::ostringstream os;
		os << TextStorage::instance().get(IDS::START_INIT_FMOD_VERSION_ERROR_TEXT_ID)->getText() << "[" << version << " < " << FMOD_VERSION << "]";
		throw SDLException(os.str());
	}

	printSoundInformation();

	if(!ERRCHECK(soundEngine->init(32, FMOD_INIT_NORMAL, 0))) {
		throw SDLException(TextStorage::instance().get(IDS::START_INIT_FMOD_SYSTEM_INIT_ERROR_TEXT_ID)->getText());
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



	
