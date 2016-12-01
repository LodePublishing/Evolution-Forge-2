#include "engine.hpp"

#if defined(_FMOD_SOUND) || defined(_SDL_MIXER_SOUND)

#include <fstream>
#include <sstream>

#define MUSIC_TRANSITION_DURATION 2000

Engine::Engine() :
#ifdef _FMOD_SOUND
	sound(NULL),
	musicChannel(NULL),
#endif
	configurationFile("sounds.cfg")
{
	sounds.;
}

Engine::~Engine()
{
	to_init_log("* " + gui.lookUpString(END_FREEING_SOUNDS_STRING));
	for(unsigned int i = MAX_SOUNDS; i--;)
	{
#ifdef _FMOD_SOUND
		soundList[i]->release();
#elif _SDL_MIXER_SOUND
		Mix_FreeChunk(soundList[i]);
#endif
		soundList[i] = NULL;
	}

	for(unsigned int i = MAX_MUSIC; i--;)
	{
#ifdef _FMOD_SOUND
		musicList[i]->release();
#elif _SDL_MIXER_SOUND
		Mix_FreeMusic(musicList[i]);
#endif
		musicList[i] = NULL;
	}
}


// TODO unload via shared_ptr
#if 0
void Engine::unloadSounds()
{
/*	for(std::list<SoundEntry>::iterator i = loadedSounds.begin(); i!=loadedSounds.end(); ++i)
		if(!i->used)
		{
			for(unsigned int j = MAX_SOUNDS;j--;)
				if(i->sound == soundList[j])
					soundList[j] = NULL;
			i->sound->release();
			i->sound = NULL;
			i->used = true;
		} else if(i->sound!=NULL)
			i->used = false;*/
}
#endif




bool Engine::loadSoundDataFile(const std::string& sound_dir)
{
	std::ifstream pFile((sound_dir + configurationFile).c_str());

	to_init_log("* " + gui.lookUpString(START_LOADING_STRING) + " " + sound_dir + configurationFile);
	
	check_stream_is_open(pFile, "Sound::loadSoundDataFile", sound_dir + configurationFile);

	char line[1024];
	bool loading_sounds = false;
	bool loading_music = false;
	while(pFile.getline(line, sizeof line))
	{
		check_stream_for_failure(pFile, "Sound::loadSoundDataFile", sound_dir + configurationFile);
		
		if(process_line(line, "@MUSIC")) 
		{
			if(!loading_music)
			{
				loading_music = true;
				to_init_log("  - " + gui.lookUpString(START_LOAD_MUSIC_STRING));
			}
			std::map<std::string, std::list<std::string> > block;
			if(!parse_block_map(pFile, block))
			{
				throw MyException("WARNING (Sound::loadSoundDataFile()): No concluding @END for @MUSIC block was found in file " + sound_dir + configurationFile + " => trying to parse what we have so far.");
			}
			for(unsigned int j = 0; j < MAX_MUSIC; j++)
			{
				std::map<std::string, std::list<std::string> >::iterator i;
				if((i = block.find(musicIdentifier[j])) != block.end())
				{
					i->second.pop_front(); // Identifier loeschen
					std::string name = i->second.front();
					if((name.size()<4)||(name[name.size()-4]!='.'))
						name = sound_dir + name + ".mp3";
					else name = sound_dir + name;
					bool found_music = false;
					for(std::list<MusicEntry>::iterator l = loadedMusic.begin(); l!=loadedMusic.end(); ++l)
					// already loaded?
						if(l->name == name)
						{
							found_music = true;
							musicAccessTable[j] = &(*l);
							break;
						}
					if(!found_music)
					{
						MusicEntry entry;
						entry.name = name;
						to_init_log(name);
						entry.music = NULL;
						entry.used = false;
						loadedMusic.push_back(entry);
						musicAccessTable[j] = &(loadedMusic.back());
					}
					block.erase(i);
				}
			}
		// TODO nicht gefundene Eintraege bemaengeln
		} else
		if(index == "@SOUNDS")
		{
			if(!loading_sounds)
			{
				loading_sounds = true;
				to_init_log("  - " + gui.lookUpString(START_LOAD_SOUNDS_STRING));
			}
			std::map<std::string, std::list<std::string> > block;
			if(!parse_block_map(pFile, block))
			{
				throw MyException("WARNING (Sound::loadSoundDataFile()): No concluding @END for @SOUNDS block was found in file " + sound_dir + configurationFile + " => trying to parse what we have so far.");
			}
			for(unsigned int j = 0; j < MAX_SOUNDS; j++)
			{
				std::map<std::string, std::list<std::string> >::iterator i;
				if((i = block.find(soundIdentifier[j])) != block.end())
				{
					i->second.pop_front(); // Identifier loeschen
					std::string name = i->second.front();
					if((name.size()<4)||(name[name.size()-4]!='.')) {
						name = sound_dir + name + ".mp3";
					}
					else {
						name = sound_dir + name;
					}
					bool found_sound = false;
					for(std::list<SoundEntry>::iterator l = loadedSounds.begin(); l!=loadedSounds.end(); ++l)
					// already loaded?
						if(l->name == name)
						{
							found_sound = true;
							soundAccessTable[j] = &(*l);
							break;
						}
					if(!found_sound)
					{
						SoundEntry entry;
						entry.name = name;
						entry.sound = NULL;
						entry.used = false;
						loadedSounds.push_back(entry);
						soundAccessTable[j] = &(loadedSounds.back());
					}
					block.erase(i);
				}
			}
		// TODO nicht gefundene Eintraege bemaengeln
		}
	}
	return true;
}

#ifdef _FMOD_SOUND
FMOD::Sound* Sound::lookUpMusic(const eMusic id)
#elif _SDL_MIXER_SOUND
Mix_Music* Sound::lookUpMusic(const eMusic id)
#endif
{
#ifdef _FMOD_SOUND
	BOOST_ASSERT(sound);
#endif
	BOOST_ASSERT(id > 0 && id < MAX_MUSIC);

	if(musicList[id] == NULL)
// reload
	{
#ifdef _FMOD_SOUND
		FMOD::Sound* temp = NULL;
#elif _SDL_MIXER_SOUND
		Mix_Music* temp = NULL;
#endif
		if(musicAccessTable[id] == NULL)
		{
			throw MyException("ERROR (Sound::lookUpMusic()): Music was not initialized. Check 'settings/ui/default.ui' and 'data/sounds'."); // TODO sound identifier...
		} else		
		{
#ifdef _FMOD_SOUND
			FMOD_RESULT result;
			result = sound->createSound(musicAccessTable[id]->name.c_str(), FMOD_LOOP_NORMAL | FMOD_SOFTWARE, 0, &temp);
			if(!ERRCHECK(result))
			{
				throw MyException("ERROR (Sound::lookUpMusic()): Could not load " + musicAccessTable[id]->name);
			}
#elif _SDL_MIXER_SOUND
			temp = Mix_LoadMUS(musicAccessTable[id]->name.c_str());
			if(!temp) 
			{
				std::ostringstream os;
				os << "ERROR (Sound::lookUpMusic()): Could not load " << musicAccessTable[id]->name.c_str() << " : " << Mix_GetError();
				throw MyException(os.str());
			}
#endif
			musicAccessTable[id]->music = temp;
			musicList[id] = temp;
		}
	}
	musicAccessTable[id]->used = true;
	return musicList[id];
}

#ifdef _FMOD_SOUND
FMOD::Sound* Sound::lookUpSound(const eSound id)
#elif _SDL_MIXER_SOUND
Mix_Chunk* Sound::lookUpSound(const eSound id)
#endif
{
#ifdef _FMOD_SOUND
	if(!sound)
		return NULL;
#endif

	BOOST_ASSERT(id > 0 && id < MAX_SOUNDS);

	if(soundList[id] == NULL)
// reload
	{
#ifdef _FMOD_SOUND
		FMOD::Sound* temp = NULL;
#elif _SDL_MIXER_SOUND
		Mix_Chunk* temp = NULL;
#endif
		if(soundAccessTable[id]==NULL)
		{
			throw MyException("ERROR (Sound::lookUpSound()): Sound " + soundIdentifier[id] + " was not initialized. Check 'data/sounds/sounds.cfg' and 'data/sounds'.");
		} else		
		{
#ifdef _FMOD_SOUND
			FMOD_RESULT result;
			result = sound->createSound(soundAccessTable[id]->name.c_str(), FMOD_SOFTWARE, 0, &temp);
			if(!ERRCHECK(result))
			{
				throw MyException("ERROR (Sound::lookUpSound()): Could not load " + soundAccessTable[id]->name);
			}
#elif _SDL_MIXER_SOUND
			temp = Mix_LoadWAV(soundAccessTable[id]->name.c_str());
			if(!temp) 
			{
				std::ostringstream os;
				os << "ERROR (Sound::lookUpSound()): Could not load " << soundAccessTable[id]->name.c_str() << " : " << Mix_GetError();
				throw MyException(os.str());
				return NULL;
			}
#endif
			soundAccessTable[id]->sound = temp;
			soundList[id] = temp;
		}
	}
	soundAccessTable[id]->used = true;
	return soundList[id];
}















void Sound::initSoundAndMusicIdentifier()
{
	for(unsigned int i = MAX_SOUNDS; i--;)
		soundIdentifier[i] = "null";
	for(unsigned int i = MAX_MUSIC; i--;)
		musicIdentifier[i] = "null";

	soundIdentifier[NULL_SOUND] = "NULL_SOUND";
	soundIdentifier[MOUSEOVER_SOUND] = "MOUSEOVER_SOUND";
	soundIdentifier[SWISHIN_SOUND] = "SWISHIN_SOUND";
	soundIdentifier[SWISHOUT_SOUND] = "SWISHOUT_SOUND";
	soundIdentifier[SWISHLOCK_SOUND] = "SWISHLOCK_SOUND";
	soundIdentifier[CLICKED_SOUND] = "CLICKED_SOUND";
	soundIdentifier[CLICK_SOUND] = "CLICK_SOUND";
	soundIdentifier[COMPLETE_SOUND] = "COMPLETE_SOUND";
	soundIdentifier[ERROR_SOUND] = "ERROR_SOUND";
	soundIdentifier[RING_SOUND] = "RING_SOUND";
	soundIdentifier[INTRO_SOUND] = "INTRO_SOUND";
	
	musicIdentifier[NULL_MUSIC] = "NULL_MUSIC";
	musicIdentifier[LALA_MUSIC] = "LALA_MUSIC";
	musicIdentifier[DIABLO_MUSIC] = "DIABLO_MUSIC";
}

eMusic Sound::currentMusic = MAX_MUSIC;
#ifdef _SDL_MIXER_SOUND
Mix_Music* Sound::music = NULL;
Mix_Music* Sound::nextMusic = NULL;
std::list<int> Sound::soundChannel;
#endif
#endif