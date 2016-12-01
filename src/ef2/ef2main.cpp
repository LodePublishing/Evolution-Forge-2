#include <misc/log.hpp>
#include <gui/guiinstance.hpp>
#include <misc/ids.hpp>
#include <gui/gui_storage.hpp>
#include <sdlwrap/framerate.hpp>
#include <main/mainconfiguration.hpp>
#include <main/mainconfiguration_storage.hpp>
#include <lang/text_storage.hpp>
#include <main/main_directories.hpp>
#include <guicore/bitmap_storage.hpp>
#include <gui/guiprocessor.hpp>
#include <gui/statictext.hpp>
#include <guicore/font_storage.hpp>
#include <guicore/color_storage.hpp>

int main(int argc, char *argv[])
{	
	std::list<std::string> arguments;
	for(signed int i = 1;i<argc;++i) {
		arguments.push_back(argv[i]);
	}
	MainDirectories::init();
	const boost::shared_ptr<const MainConfiguration> mainConfiguration = MainConfigurationStorage::instance().get(IDS::DEFAULT_MAIN_CONFIGURATION_ID);
	TextStorage::updateLanguage(mainConfiguration->getLanguageId());
	const boost::shared_ptr<const Gui> gui = GuiStorage::instance().get(mainConfiguration->getGuiId());


	

// ------ INTRO PICTURE ------
//	SDL_Surface* progress = SDL_LoadBMP("data/bitmaps/bar.bmp");
//	Bitmap claw("data/bitmaps/clawsoftware.bmp");
//	screen->DrawBitmap(progress, (resoluton.GetWidth() - progress->w)/2, (resolution.GetHeight() - progress->h)/2-60);
//	screen->DrawBitmap(claw, resolution.GetWidth() - claw->w, resolution.GetHeight() - claw->h);
//	screen->SetPen(Pen(Color(screen->GetSurface(), 255, 255, 255), 1, SOLID_PEN_STYLE));
//	screen->SetBrush(Brush(Color(screen->GetSurface(), 100, 150, 255), SOLID_BRUSH_STYLE));
// ------ END INTRO PICTURE -------

// ------ CAP FRAMERATE ------
	boost::scoped_ptr<FrameRate> fps(new FrameRate(gui->getGuiConfiguration()->getDesiredFramerate(), gui->getGuiConfiguration()->getDesiredCPU()));
// ------ END CAP FRAMERATE


// ------- INIT GRAPHIC ENGINE ------
	//toInfoLog(TextStorage::instance().get(IDS::START_INIT_GRAPHIC_ENGINE_CORE_TEXT_ID));
//	Main m(screen);

	unsigned int screenshot = 100;
	unsigned int refresh = fps->getFramesPerGeneration();
//	if(efConfiguration.isAutoSaveRuns())
//		m.startAllOptimizing();
//	else
//		m.stopAllOptimizing(); TODO

	bool endrun = false;
	unsigned int screenCapturing=0;

// ------ END INIT GRAPHIC ENGINE ------


	BitmapStorage::reset();	
	BitmapObject object(NULL, Rect(), Size(), BitmapStorage::instance().get(IDS::BACKGROUND_SC_BITMAP));
	DC* dc = gui->createScreen();
	GuiProcessor t;	
	bool done = false;


// ------ INTRO ------
	Rect rect1((dc->w()-650)/2 + 10, (dc->h() - 750)/2 + 10, 650 - 20, 650 - 20);
	Rect rect2((dc->w()-600)/2 + 10, (dc->h() - 700)/2 + 10, 600 - 20, 600 - 20);
	
	StaticText introText(NULL, rect2, Size(0,0), 
		ColorStorage::instance().get(IDS::BRIGHT_TEXT_COLOR_ID),
		FontStorage::instance().get(IDS::SMALL_MIDDLE_NORMAL_FONT_ID),
		TextStorage::instance().get(IDS::WELCOME_TEXT_ID),
		boost::assign::list_of(gui->getVersion()));

/*	bool done = false;
	while(!done)
	{
		introText.process();
		screen->SetPen(Pen(Color(screen->GetSurface(), 0, 0, 0), 1, TRANSPARENT_PEN_STYLE));
		screen->SetBrush(Brush(Color(screen->GetSurface(), 0, 0, 0), SOLID_BRUSH_STYLE));
		screen->DrawRectangle(Rect(resolution.x, resolution.y, resolution.w-1, resolution.h-1));
		screen->SetPen(*Object::theme.lookUpPen(OUTER_BORDER_PEN));
		screen->SetBrush(*Object::theme.lookUpBrush(WINDOW_BACKGROUND_BRUSH));
		screen->DrawEdgedRoundedRectangle(t,6);
//		screen->DrawBitmap(claw, resolution.w - claw->w, resolution.h - claw->h);
		introText.draw(screen);
		screen->updateScreen();
		fps->delay();
		
	}*/

// ------ END INTRO ------


	SDL_Event event;
	
	while(!done)
	{	
		t.process(dc);
		fps->delay();		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_KEYDOWN:
					done=true;break;
			}
		}
	}

	#if 0

	/*
// MAIN LOOP
	while(true)
	{
// ------ DRAWING ------
		Object::redrawnObjects = 0;
//		for(std::list<Object*>::iterator i = Object::processArray.begin(); i!=Object::processArray.end(); ++i)
//			(*i)->process();
//		{
//			std::ostringstream os;os.str("");os << "length :" << Object::processArray.size();toInfoLog(os.str());
//		}
	
//		Object::copyToNextProcessArray();
		m.process();
		screen->updateScreen();
		m.draw(screen);
// ------ END DRAWING ------

// ------ SCREENCAPTURE ------ 
        if(screenCapturing==100) {
			std::ostringstream os;
			os.str("");
			os << "shot" << screenshot << ".bmp";
			gui->saveBMP(os.str());
			++screenshot;
		}
		if(screenCapturing>0) {
			--screenCapturing;
			std::ostringstream os;
			os.str("");
			os << "shot" << (screenshot-1) << ".bmp" << " saved (" << (gui->getScreenDataSize()/1024) << "kb)";
                        screen->DrawText(os.str(), 50, 300);
                }
// ------ END SCREENCAPTURE -----

	
// ------ FRAMERATE AND CALCULATION ------	
		unsigned int frames_per_generation = fps->getFramesPerGeneration();
		unsigned int frames_per_second = fps->getCurrentFramerate();
		
		if((!endrun)&&(((Object::editTextField==NULL)&&(m.isAnyOptimizing()))||(efConfiguration.isAllowStaticFramerate()))) // TODO
		{
			if(efConfiguration.isAllowStaticFramerate())
				fps->setDesiredFramerate(efConfiguration.getStaticFramerate());
			else
				fps->setDesiredFramerate(efConfiguration.getDynamicFramerate());
			fps->setAllowStaticFramerate(efConfiguration.isAllowStaticFramerate());
			fps->delay();
	
			efConfiguration.setCurrentFramerate(frames_per_second);
			efConfiguration.setCurrentFramesPerGeneration(frames_per_generation);

			refresh+=100;
			while((refresh > frames_per_generation))// && (!(endrun = database.getIsNewRun()))) // TODO
			{
				m.OnIdle();
				if(frames_per_generation > refresh)
					refresh = 0;
				else
					refresh -= frames_per_generation;
			}
		}
		if(endrun)
			endrun = m.newRun();
		endrun=false; // TODO
// ------ END FRAMERATE AND CALCULATION 


// ------ FPS DEBUG
/*		{
			Point p = Point(20, resolution.GetHeight() - 50);
			screen->SetTextForeground(DC::toSDL_Color(255, 20, 20));
			screen->SetFont(Object::theme.lookUpFont(LARGE_BOLD_FONT));
			screen->SetBrush(Brush(Color(screen->GetSurface(), 0, 0, 0), SOLID_BRUSH_STYLE));
			screen->DrawRectangle(Rect(p, Size(200, 20)));

			std::ostringstream os;
			os.str("");
			os << "Objects: " << Object::redrawnObjects << "   FPS: " << efConfiguration.getCurrentFramerate();
			screen->DrawText(os.str(), p + Size(20, 2));	
		}*/
// ------ END FPS DEBUG

	

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					delete fps;delete screen;return EXIT_SUCCESS;
					break;
				case SDL_MOUSEBUTTONDOWN:
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
					switch(event.key.keysym.sym)
					{
						case SDLK_BACKSPACE:
						if(Object::editTextField!=NULL)
							Object::editTextField->removeCharBackspace();
						break;
						case SDLK_TAB:break;//TODO
						case SDLK_CLEAR:break;//TODO
						case SDLK_KP_ENTER:
						case SDLK_RETURN:
							if(Object::editTextField==NULL)
							{
								if(event.key.keysym.mod & (KMOD_LALT | KMOD_RALT | KMOD_ALT))
								{
//									screen->setFullscreen(!efConfiguration.isFullScreen());
									efConfiguration.setFullScreen(!efConfiguration.isFullScreen());
									m.noticeFullscreen();
//									toInfoLog(Object::theme.lookUpString(efConfiguration.isFullScreen()?START_SET_FULLSCREEN_MODE_STRING:START_SET_WINDOW_MODE_STRING));
								}
							} else
								Object::editTextField->forceDone();
							// else: OK bestaetigen!
						break;
						case SDLK_ESCAPE:
							if(Object::editTextField==NULL) {
								delete fps;delete screen;screen=NULL;return EXIT_SUCCESS;
							} else
								Object::editTextField->forceCancel();
							break;
						case SDLK_PAUSE:
						{
//							if(m.isOptimizing())
//								m.stopAllOptimizing();
//							else m.startAllOptimizing();
						}break;
						case SDLK_SPACE:
							if(Object::editTextField==NULL)
							{
								screenCapturing=100;
//								if(m.isOptimizing())
//									m.stopAllOptimizing();
//								else m.startAllOptimizing();
							} else
							Object::editTextField->addChar(' ');
							break;
						case SDLK_EXCLAIM:break;
						case SDLK_QUOTEDBL:break;
						case SDLK_HASH:break;
						case SDLK_DOLLAR:break;
						case SDLK_AMPERSAND:break;
						case SDLK_QUOTE:break;
						case SDLK_LEFTPAREN:break;
						case SDLK_RIGHTPAREN:break;
						case SDLK_KP_MULTIPLY:
						case SDLK_ASTERISK:break; // TODO
						case SDLK_KP_PLUS:
//						case SDLK_PLUS:break;
						case SDLK_COMMA:break;
						case SDLK_KP_MINUS:break;
//						case SDLK_MINUS:
//							if((event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT))&&(Object::editTextField!=NULL))
//							{
//								Object::editTextField->addChar('_');
//								break;
//							}break;
						case SDLK_KP_PERIOD:
						case SDLK_PERIOD:break;//TODO
						case SDLK_KP_DIVIDE:break;
						case SDLK_SLASH:break;//TODO

						case SDLK_COLON:break;
						case SDLK_SEMICOLON:break;
						case SDLK_LESS:break;//TODO
						case SDLK_KP_EQUALS:break;
//						case SDLK_EQUALS:break;
						case SDLK_GREATER:break;//TODO
						case SDLK_QUESTION:break;
						case SDLK_AT:break;
						case SDLK_BACKSLASH:break;
						case SDLK_CARET:break;
						case SDLK_UNDERSCORE:
							if(Object::editTextField!=NULL)
								Object::editTextField->addChar('_');
							break;
						case SDLK_BACKQUOTE:break;
						case SDLK_DELETE:
							if(Object::editTextField!=NULL)
								Object::editTextField->removeCharDelete();
							break;
						case SDLK_KP0:
						case SDLK_KP1:
						case SDLK_KP2:
						case SDLK_KP3:
						case SDLK_KP4:
						case SDLK_KP5:
						case SDLK_KP6:
						case SDLK_KP7:
						case SDLK_KP8:
						case SDLK_KP9:
							if(Object::editTextField!=NULL)
								Object::editTextField->addChar('0'+event.key.keysym.sym-SDLK_0);
							break;


//						case SDLK_PRINT:break;
						case SDLK_EQUALS:
								if(Object::theme.getResolution()<RESOLUTION_1280x1024)
								{
									Object::theme.setResolution((eResolution)(Object::theme.getResolution() + 1));
									screen->setResolution(Object::theme.getResolution());
									uiConfiguration.setResolution(Object::theme.getResolution());
									resolution = screen->getResolutionSize();
									Object::setResolution(resolution);
									std::ostringstream os;os.str("");
 									os << resolution.GetWidth() << "x" << resolution.GetHeight();
									toInfoLog(Object::theme.lookUpFormattedString(CHANGED_RESOLUTION_STRING, os.str()));
									m.reloadOriginalSize();
								}
								break;
						case SDLK_MINUS:
								if(Object::theme.getResolution()>RESOLUTION_640x480)
								{
									Object::theme.setResolution((eResolution)(Object::theme.getResolution() - 1));
									screen->setResolution(Object::theme.getResolution());
									uiConfiguration.setResolution(Object::theme.getResolution());
									resolution = screen->getResolutionSize();
									Object::setResolution(resolution);
									std::ostringstream os;os.str("");
 									os << resolution.GetWidth() << "x" << resolution.GetHeight();
									toInfoLog(Object::theme.lookUpFormattedString(CHANGED_RESOLUTION_STRING, os.str()));
									m.reloadOriginalSize();
								}
								break;
						case SDLK_LEFTBRACKET:
								if(screen->getBitDepth() > DEPTH_8BIT)
								{
									Object::theme.setBitDepth((eBitDepth)(screen->getBitDepth()-1));
									screen->setBitDepth(Object::theme.getBitDepth());
									uiConfiguration.setBitDepth(Object::theme.getBitDepth());
									Object::theme.updateColors(screen->GetSurface());
									// TODO bitDepth im theme aendern!
									toInfoLog(Object::theme.lookUpFormattedString(CHANGED_BIT_DEPTH_STRING, (unsigned int)screen->GetSurface()->format->BitsPerPixel));
								}
								break;
						case SDLK_RIGHTBRACKET:
								if(screen->getBitDepth() < DEPTH_32BIT)
								{
									Object::theme.setBitDepth((eBitDepth)(screen->getBitDepth()+1));
									screen->setBitDepth(Object::theme.getBitDepth());
									uiConfiguration.setBitDepth(Object::theme.getBitDepth());
									Object::theme.updateColors(screen->GetSurface());
									toInfoLog(Object::theme.lookUpFormattedString(CHANGED_BIT_DEPTH_STRING, (unsigned int)screen->GetSurface()->format->BitsPerPixel));
								}
								break;
							
//						case SDLK_F6:m.mainWindow->forcePressTab(MAP_TAB);break;
//						case SDLK_F7:m.mainWindow->forcePressTab(SETTINGS_TAB);break;
//						case SDLK_F8:m.mainWindow->forcePressTab(HELP_TAB);break;
						case SDLK_a:
						case SDLK_b:
						case SDLK_c:
						case SDLK_d:
						case SDLK_e:
						case SDLK_f:
						case SDLK_g:
						case SDLK_h:
						case SDLK_i:
						case SDLK_j:
						case SDLK_k:
						case SDLK_l:
						case SDLK_m:
						case SDLK_n:
						case SDLK_o:
						case SDLK_p:
						case SDLK_q:
						case SDLK_r:
						case SDLK_s:
						case SDLK_t:
						case SDLK_u:
						case SDLK_v:
						case SDLK_w:
						case SDLK_x:
						case SDLK_y:
						case SDLK_z:
							if(Object::editTextField!=NULL)
							{
								if(event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT))
									Object::editTextField->addChar('A'+event.key.keysym.sym-SDLK_a);
								else
									Object::editTextField->addChar('a'+event.key.keysym.sym-SDLK_a);
							}
							break;
						case SDLK_0:
						case SDLK_1:
						case SDLK_2:
						case SDLK_3:
						case SDLK_4:
						case SDLK_5:
						case SDLK_6:
						case SDLK_7:
						case SDLK_8:
						case SDLK_9:
							if(Object::editTextField!=NULL)
								Object::editTextField->addChar('0'+event.key.keysym.sym-SDLK_0);
							break;

						case SDLK_LEFT:
							if(Object::editTextField!=NULL)
								Object::editTextField->moveLeft();
							break;

						case SDLK_RIGHT:
							if(Object::editTextField!=NULL)
								Object::editTextField->moveRight();
							break;

						default:break;
					}
					break;
				default:break;
			}
		}

		if(m.hasBitDepthChanged())
		{
			screen->setBitDepth(Object::theme.getBitDepth());
			Object::theme.updateColors(screen->GetSurface());
			toInfoLog(Object::theme.lookUpFormattedString(CHANGED_BIT_DEPTH_STRING, (unsigned int)screen->GetSurface()->format->BitsPerPixel));
		} else
	
		if(m.hasResolutionChanged())
		{
			screen->setResolution(Object::theme.getResolution());
			resolution = screen->getResolutionSize();
			Object::setResolution(resolution);
			std::ostringstream os;
			os.str("");
 			os << resolution.GetWidth() << "x" << resolution.GetHeight();
			toInfoLog(Object::theme.lookUpFormattedString(CHANGED_RESOLUTION_STRING, os.str()));
			m.reloadOriginalSize();
		} else 

		if(m.hasFullScreenChanged())
		{
			screen->setFullscreen(efConfiguration.isFullScreen());
			toInfoLog(Object::theme.lookUpString(efConfiguration.isFullScreen()?START_SET_FULLSCREEN_MODE_STRING:START_SET_WINDOW_MODE_STRING));
		}
	}
#endif
	return EXIT_SUCCESS;
}
					


