#if 0

#include "init.hpp"

int main(int argc, char *argv[])
{
	Init::instance().init(argc, argv);

	srand(time(NULL));
	std::list<std::string> arguments;
	for(signed int i = 1;i<argc;++i)
		arguments.push_back(argv[i]);

// ------ LOAD CONFIGURATION FILES ------
 
	toInitLog(theme.lookUpString(START_INIT_SDL_STRING));

	if(!Init::chooseDriver(arguments))
		return(EXIT_FAILURE);
	
	if(!Object::initSDL("EVOLUTION FORGE " + CORE_VERSION + " - www.clawsoftware.de"))
		return(EXIT_FAILURE);
		
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));
	
	toInitLog(Object::theme.lookUpString(START_LOAD_CORE_CONFIGURATION_STRING));
	coreConfiguration.loadConfigurationFile();
	
	toInitLog(Object::theme.lookUpString(START_LOAD_EF_CONFIGURATION_STRING));
	efConfiguration.loadConfigurationFile();
// ------ END LOAD CONFIGURATION FILES -------

// ------ PARSING COMMAND LINE ------
	toInitLog(Object::theme.lookUpString(START_COMMANDO_LINE_1_STRING));
	toInitLog(Object::theme.lookUpString(START_COMMANDO_LINE_2_STRING));
	toInitLog(Object::theme.lookUpString(START_COMMANDO_LINE_3_STRING));
	toInitLog(Object::theme.lookUpString(START_COMMANDO_LINE_4_STRING));
	toInitLog(Object::theme.lookUpString(START_COMMANDO_LINE_5_STRING));
	toInitLog(Object::theme.lookUpString(START_COMMANDO_LINE_6_STRING));
	toInitLog(Object::theme.lookUpString(START_PARSE_COMMAND_LINE_STRING));
	
// ------ END PARSING COMMAND LINE ------

// ------- END INIT SDL_TTF -------
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));

	BROODWAR bw;
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));
	STARCRAFT sc;
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));
//	WARCRAFT3 wc3;
//	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));

/*
	Rect::testCommonRect();
	Rect::testConnectRect();
	Rect::testConnectRects();
	Rect::testWithoutRect();
	Rect::testCutFromList();
	return(0);
*/	
// ------- INIT GRAPHIC ENGINE ------
	toInitLog(Object::theme.lookUpString(START_INIT_GRAPHIC_ENGINE_CORE_STRING));
	
	Main m;
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));
	if(!m.initGUI())
		return(EXIT_FAILURE);
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));
	
	toInitLog(Object::theme.lookUpString(START_SYSTEM_READY_STRING));
	SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));

// ------ END INIT GRAPHIC ENGINE ------


	bool sound_not_initialized = true;
	bool done = false;
	SDL_Event event;

	SDL_SetCursor(Object::theme.lookUpCursor(ARROW_CURSOR, 0));
// MAIN LOOP
	while(!done)
	{
		bool ignore_rest = false;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					done = true;
					break;
					// TODO Mouse & Focus...
				case SDL_MOUSEBUTTONDOWN:
					if(m.click());
					else
					if(event.button.button == SDL_BUTTON_LEFT)
						m.leftDown();
					else if(event.button.button == SDL_BUTTON_RIGHT)
						m.rightDown();
					else if(event.button.button == SDL_BUTTON_WHEELUP)
						m.wheelUp();
					else if(event.button.button == SDL_BUTTON_WHEELDOWN)
						m.wheelDown();
					break;
				case SDL_MOUSEBUTTONUP:
					if(m.click());
					else
					if(event.button.button == SDL_BUTTON_LEFT)
						m.leftUp(Point(event.motion.x, event.motion.y));
					else if(event.button.button == SDL_BUTTON_RIGHT)
						m.rightUp(Point(event.motion.x, event.motion.y));
                                        else if(event.button.button == SDL_BUTTON_WHEELUP)
                                                m.wheelUp();
                                        else if(event.button.button == SDL_BUTTON_WHEELDOWN)
                                                m.wheelDown();
					break;
				case SDL_MOUSEMOTION:
					m.setMouse(Point(event.motion.x, event.motion.y));break;
				case SDL_KEYDOWN:
//						while (SDL_PollEvent(&event));
//						picture_num = 9999;
					if((Object::focus==NULL)||(!Object::focus->addKey(event.key.keysym.sym, event.key.keysym.mod)))
					switch(event.key.keysym.sym)
					{
						case SDLK_r: m.openMenu(OPEN_RACE_MENU);break;
						case SDLK_n: if(event.key.keysym.mod & KMOD_CTRL)
								     m.openMenu(RESTART_CALCULATION);break;
						case SDLK_b: if(event.key.keysym.mod & KMOD_CTRL)
								     m.openMenu(SAVE_BUILD_ORDER);
							     m.openMenu(OPEN_BO_MENU);break;
						case SDLK_g: if(event.key.keysym.mod & KMOD_CTRL)
								     m.openMenu(SAVE_GOAL);
							     else
								     m.openMenu(OPEN_GOAL_MENU);break;
						case SDLK_u: m.openMenu(OPEN_UNIT_MENU);break;
//						case SDLK_a: m.openMenu(ADD_PLAYER);break;
						case SDLK_e: m.openMenu(EDIT_FORCE_LIST);break;
						case SDLK_F1:
						case SDLK_F2:
						case SDLK_F3:
						case SDLK_F4:
//						case SDLK_F5:m.mainWindow->activateTabNumber(event.key.keysym.sym - SDLK_F1);break;
							     
//						case SDLK_F6:m.mainWindow->activateTab(DATABASE_TAB);break;
//						case SDLK_F7:m.mainWindow->activateTab(SETTINGS_TAB);break;
//						case SDLK_F8:m.mainWindow->activateTab(HELP_TAB);break;


						case SDLK_HOME:m.wheelToTop();break;
						case SDLK_END:m.wheelToBottom();break;
							  
						case SDLK_PAGEUP:m.wheelUp();m.wheelUp();m.wheelUp();break;
						case SDLK_PAGEDOWN:m.wheelDown();m.wheelDown();m.wheelDown();break;
						case SDLK_UP:m.wheelUp();break;
						case SDLK_DOWN:m.wheelDown();break;
						case SDLK_LEFT:if(!(event.key.keysym.mod & (KMOD_LALT | KMOD_RALT | KMOD_ALT)))
								       break;
						case SDLK_BACKSPACE:m.goBack();break;							
						case SDLK_TAB:
							//Object::rotateEditField();
							break;
						case SDLK_KP_ENTER:
						case SDLK_RETURN:
							if(event.key.keysym.mod & (KMOD_LALT | KMOD_RALT | KMOD_ALT))
								m.noticeFullscreen();
						break;
						case SDLK_q: 
							if(event.key.keysym.mod & KMOD_CTRL)
								done = true;break;
						case SDLK_ESCAPE:
							if(Object::focus!=NULL)
								Object::focus=NULL;
							else 
								done = true;
							break;
						case SDLK_PAUSE:
								if(m.isAnyOptimizing())
									m.stopAllOptimizing();break;

						case SDLK_SPACE:
//								if(m.isAnyOptimizing())
//									m.stopAllOptimizing();
//								else 
								m.startLastOptimizing();
							break;
//						case SDLK_PRINT:break;
						case SDLK_EQUALS:
							if(Object::setResolution((eResolution)(Object::theme.getResolution() + 1)))
							{
								Button::resetButton();
								m.reloadOriginalSize();
								ignore_rest = true;
							}
							break;
						case SDLK_MINUS:
							if(Object::setResolution((eResolution)(Object::theme.getResolution() - 1)))
							{
								Button::resetButton();
								m.reloadOriginalSize();
								ignore_rest = true;
							}
							break;
						case SDLK_LEFTBRACKET:
							if(Object::setBitDepth((eBitDepth)(Object::dc->getBitDepth()-1)))
								ignore_rest = true;
							break;
						case SDLK_RIGHTBRACKET:
							if(Object::setBitDepth((eBitDepth)(Object::dc->getBitDepth()+1)))
								ignore_rest = true;
					
							break;
							
						default:break;
					}
					break;
				default:break;
			}
			if(ignore_rest)
				while (SDL_PollEvent(&event));
		}
		m.poll(MESSAGE_TICKS);
		
		m.process();
		
		if(m.hasBitDepthChanged()) // TODO
		{
			Object::setBitDepth(Object::theme.getBitDepth());
//			m.needRedraw(); TODO
		}
		if(m.hasResolutionChanged())
		{
			Object::setResolution(Object::theme.getResolution());
			m.reloadOriginalSize();
		}
		if(m.hasFullScreenChanged())
		{
			Object::dc->setFullscreen(uiConfiguration.isFullScreen());
			toInitLog(Object::theme.lookUpString(uiConfiguration.isFullScreen()?START_SET_FULLSCREEN_MODE_STRING:START_SET_WINDOW_MODE_STRING));
		}
		if(m.hasThemeChanged())
		{
//			m.needRedraw(); TODO
		}

		if(m.hasGameTypeChanged())
		{
			SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));
			bool new_game_type = true;
			switch(coreConfiguration.getGameType())
			{
				case 1:sc.init(); 
				       toInitLog("StarCraft");
				       break;
				case 2:bw.init(); 
				       toInitLog("BroodWar");
				       break;
//				case 3:wc3.init();toInitLog("WarCraft");break;
				default:toErrorLog("DEBUG (main()): Game type not initialized."); new_game_type = false;break; // not initialized
			}
			if(new_game_type)
			{
				SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));
			        GAME::initGameStrings();
				GAME::initRaceStrings();
			        if(!GAME::setLanguage(Object::theme.getLanguage()))
			        {
					toErrorLog("GAME::setLanguage failed!");
					toErrorLog(Object::theme.getLanguage());
				}
				SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));
				std::ostringstream harvest_file;
#ifdef __linux__
				harvest_file << GAME::gameDirectory << "/" << "harvest.hvt";
#elif WIN32
				harvest_file << GAME::gameDirectory << "\\" << "harvest.hvt";
#endif 
				if(!FILES::loadHarvestFile(harvest_file.str()))
				{
					toInitLog("Generating harvest data...");
					GAME::initResources();
					FILES::saveHarvestFile(harvest_file.str());
				}

				
				SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));
					
				if(!m.initCore())
					return(EXIT_FAILURE);
				SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 0));
				m.initializeGame(0);
				SDL_SetCursor(Object::theme.lookUpCursor(CLOCK_CURSOR, 1));
				toInitLog(Object::theme.lookUpString(START_MAIN_INIT_COMPLETE_STRING));
			}
			SDL_SetCursor(Object::theme.lookUpCursor(ARROW_CURSOR, 0));
			Object::sound.playMusic(LALA_MUSIC); 
		}

		m.resetDataChange();

		m.poll(PROCESS_TICKS);

// ------ SOUND ENGINE -------
		if(((uiConfiguration.isSound())||(uiConfiguration.isMusic()))&&(sound_not_initialized))
		{
			toInitLog(Object::theme.lookUpString(START_INIT_SOUND_STRING)); 
			if(!Object::sound.init())
			{
				uiConfiguration.setSound(false);
				uiConfiguration.setMusic(false);
			} else
			{
				sound_not_initialized = false;
//				if(uiConfiguration.isMusic()) 
//					Object::sound.playMusic(LALA_MUSIC); TODO

//				- NO_FACILITY checken... evtl orders darueber pruefen...
				
			}
		} 
		else 
		if((!uiConfiguration.isSound()) && (!uiConfiguration.isMusic()) && (!sound_not_initialized))
		{
			Object::sound.releaseSoundEngine();
			sound_not_initialized = true;
		} else
		if(!sound_not_initialized)
		{
			if(!uiConfiguration.isMusic())
				Object::sound.stopMusic();
			if(uiConfiguration.isSound())
				Object::sound.processChannels();
			else Object::sound.clearChannels();
			Object::sound.update();
		}
		Object::sound.clearSoundsToPlay();
		
		m.poll(SOUND_TICKS);

// ------ END SOUND ENGINE -------

// ------ DRAWING AND PROCESSING ------
	
		m.draw();
//		if(uiConfiguration.isUnloadGraphics())
//			Object::theme.unloadGraphics();
//			


/// ------ END DRAWING ------

// ------ END SCREENCAPTURE -----
		m.poll(DRAW_TICKS);
// ------ FRAMERATE AND CALCULATION ------
		m.newGeneration();
// ------ END FRAMERATE AND CALCULATION 
		Object::clearAllFlags();
	}
	toInitLog("* " + Object::theme.lookUpString(END_CLOSING_SDL_STRING));
	exitInfo.smoothExit = true;
	return(EXIT_SUCCESS);
}				

#endif