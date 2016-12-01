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
#include <guicore/pen_storage.hpp>
#include <guicore/brush_storage.hpp>

#include <gui/background.hpp>

#include <sound/soundprocessor.hpp>
#include <sound/sound_storage.hpp>
#include <sound/music_storage.hpp>
#include <sound/soundconfiguration_storage.hpp>
#include <ui/mainmenuline.hpp>

int main(int argc, char *argv[])
{	
	std::list<std::string> arguments;
	for(int i = 1;i<argc;++i) {
		arguments.push_back(argv[i]);
	}
	MainDirectories::init();
	const boost::shared_ptr<const MainConfiguration> mainConfiguration = MainConfigurationStorage::instance().get(IDS::DEFAULT_MAIN_CONFIGURATION_ID);
	TextStorage::updateLanguage(mainConfiguration->getLanguageId());

	toInfoLog(TextStorage::instance().get(IDS::START_LOAD_CONFIGURATION_TEXT_ID)->getText());

	const boost::shared_ptr<const Gui> gui = GuiStorage::instance().get(mainConfiguration->getGuiId());
	SDL_Object::setSmoothMovements(gui->getGuiConfiguration()->isSmoothMovements());
	// ------ CAP FRAMERATE ------
	boost::scoped_ptr<FrameRate> fps(new FrameRate(gui->getGuiConfiguration()->getDesiredFramerate(), gui->getGuiConfiguration()->getDesiredCPU()));
	// ------ END CAP FRAMERATE


	// ------- INIT GRAPHIC ENGINE ------
	unsigned int screenshot = 100;
	unsigned int refresh = fps->getFramesPerGeneration();
	unsigned int screenCapturing = 0;
	// ------ END INIT GRAPHIC ENGINE ------

	toInfoLog(TextStorage::instance().get(IDS::START_INIT_SDL_TEXT_ID)->getText());
		
	DC* dc = gui->createScreen();
	GuiProcessor t;	

	dc->setPen(PenStorage::instance().get(IDS::BORDER_PEN_ID));
	dc->setDarkPen(PenStorage::instance().get(IDS::OUTER_BORDER_PEN_ID));
	BitmapStorage::reset();	

	BackGround background(BitmapStorage::instance().get(IDS::BACKGROUND_SC_BITMAP_ID), TextStorage::instance().get(IDS::FPS_TEXT_ID));
	MainMenuLine mainMenuLine(&background);

	// ------ INTRO ------
	Rect rect((dc->w()-650)/2 + 10, (dc->h() - 750)/2 + 10, 200, 200);

	StaticText introText(&background, rect, Size(0,0), 
		ColorStorage::instance().get(IDS::BRIGHT_TEXT_COLOR_ID),
		FontStorage::instance().get(IDS::HUGE_SHADOW_BOLD_FONT_ID),
		TextStorage::instance().get(IDS::WELCOME_TEXT_ID),
		boost::assign::list_of(gui->getVersion()),
		DO_NOT_ADJUST);
	TextStorage::updateLanguage(mainConfiguration->getLanguageId());
	introText.updateParameters(boost::assign::list_of(gui->getVersion()));
	bool done = false;


	// ------ END INTRO ------

	SoundProcessor soundProcessor(SoundConfigurationStorage::instance().get(IDS::DEFAULT_SOUND_CONFIGURATION_ID));
	soundProcessor.playMusic(MusicStorage::instance().get(IDS::DIABLO_MUSIC_ID));
	
	SDL_Event event;
	std::ostringstream os;
	while(!done)
	{
		t.process(dc);
		soundProcessor.process();
		background.updateParameters(boost::assign::list_of(gui->getVersion())(boost::lexical_cast<std::string>((int)fps->getCurrentFramerate())));			
		fps->delay();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				soundProcessor.playSound(SoundStorage::instance().get(IDS::CLICK_SOUND_ID), SoundProcessor::calculatePosition(event.motion.x, dc->w()));
				if(event.button.button == SDL_BUTTON_LEFT) {
					t.leftDown(Point(event.motion.x, event.motion.y), background);
				} else if(event.button.button == SDL_BUTTON_RIGHT) {
					t.rightDown(Point(event.motion.x, event.motion.y), background);
				} else if(event.button.button == SDL_BUTTON_WHEELUP) {
					t.wheelUp();
				} else if(event.button.button == SDL_BUTTON_WHEELDOWN) {
					t.wheelDown();
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT) {
					t.leftUp(Point(event.motion.x, event.motion.y), background);
				} else if(event.button.button == SDL_BUTTON_RIGHT) {
					t.rightUp(Point(event.motion.x, event.motion.y), background);
				} else if(event.button.button == SDL_BUTTON_WHEELUP) {
					t.wheelUp();
				} else if(event.button.button == SDL_BUTTON_WHEELDOWN) {
					t.wheelDown();
				}
				break;
			case SDL_MOUSEMOTION: {
				//introText.setTargetPosition(Point(event.motion.x, event.motion.y));
				t.setMouse(Point(event.motion.x, event.motion.y), background, gui->getGuiConfiguration()->isToolTips(), dc->getSize());break;
								  }
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_PRINT:
					t.screenshot();break;
				case SDLK_BACKSPACE:
					//if(Object::editTextField!=NULL) {
					//	Object::editTextField->removeCharBackspace();
					//}
					break;
				case SDLK_TAB:break;
				case SDLK_CLEAR:break;
				case SDLK_RETURN:
					/*if(Object::editTextField==NULL)
					{*/
					if(event.key.keysym.mod & (KMOD_LALT | KMOD_RALT | KMOD_ALT))
					{
						toInfoLog(TextStorage::instance().get(dc->isFullScreen()?IDS::START_SET_WINDOW_MODE_TEXT_ID : IDS::START_SET_FULLSCREEN_MODE_TEXT_ID)->getText());
						dc->setFullScreen(!dc->isFullScreen());
						background.redrawWholeObject();
					}
					/*} else {
					Object::editTextField->forceDone();
					}*/
					// else: OK bestaetigen!*/
					break;
				case SDLK_ESCAPE:
					done = true;
					/*
					if(Object::editTextField!=NULL) {
						Object::editTextField->forceCancel();
					}*/
					break;
				case SDLK_PAUSE:
					{
						/*if(t.isOptimizing()) {
						t.stopAllOptimizing();
						} else {
						t.startAllOptimizing();
						}*/
					}break;
				case SDLK_SPACE:
					/*if(Object::editTextField==NULL)
					{
						if(t.isOptimizing()) {
							t.stopAllOptimizing();
						} else {
							t.startAllOptimizing();
						}
					} else {
					Object::editTextField->addChar(' ');
					}*/
					break;
				case SDLK_EXCLAIM:break;
				case SDLK_QUOTEDBL:break;
				case SDLK_HASH:break;
				case SDLK_DOLLAR:break;
				case SDLK_AMPERSAND:break;
				case SDLK_QUOTE:break;
				case SDLK_LEFTPAREN:break;
				case SDLK_RIGHTPAREN:break;
				case SDLK_ASTERISK:break;
				case SDLK_PLUS:break;
				case SDLK_COMMA:break;

				case SDLK_PERIOD:break;
				case SDLK_SLASH:break;

				case SDLK_COLON:break;
				case SDLK_SEMICOLON:break;
				case SDLK_LESS:break;
				case SDLK_GREATER:break;
				case SDLK_QUESTION:break;
				case SDLK_AT:break;
				case SDLK_BACKSLASH:break;
				case SDLK_CARET:break;
				case SDLK_UNDERSCORE:
					/*if(Object::editTextField!=NULL) {
					Object::editTextField->addChar('_');
					}*/
					break;
				case SDLK_BACKQUOTE:break;
				case SDLK_DELETE:
					/*if(Object::editTextField!=NULL) {
					Object::editTextField->removeCharDelete();
					}*/
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
					/*if(Object::editTextField!=NULL) {
					Object::editTextField->addChar('0'+event.key.keysym.sym-SDLK_0);
					}*/
					break;
				
				case SDLK_EQUALS:
					/*if(Object::theme.getResolution()<RESOLUTION_1280x1024)
					{
					Object::theme.setResolution((eResolution)(Object::theme.getResolution() + 1));
					screen->setResolution(Object::theme.getResolution());
					uiConfiguration.setResolution(Object::theme.getResolution());
					resolution = screen->getResolutionSize();
					Object::setResolution(resolution);
					std::ostringstream os;os.str("");
					os << resolution.GetWidth() << "x" << resolution.GetHeight();
					toInfoLog(Object::theme.lookUpFormattedString(CHANGED_RESOLUTION_STRING, os.str()));
					t.reloadOriginalSize();
					}*/
					break;
				case SDLK_MINUS:
					/*if(Object::theme.getResolution()>RESOLUTION_640x480)
					{
					Object::theme.setResolution((eResolution)(Object::theme.getResolution() - 1));
					screen->setResolution(Object::theme.getResolution());
					uiConfiguration.setResolution(Object::theme.getResolution());
					resolution = screen->getResolutionSize();
					Object::setResolution(resolution);
					std::ostringstream os;os.str("");
					os << resolution.GetWidth() << "x" << resolution.GetHeight();
					toInfoLog(Object::theme.lookUpFormattedString(CHANGED_RESOLUTION_STRING, os.str()));
					t.reloadOriginalSize();
					}*/
					//							if((event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT))&&(Object::editTextField!=NULL))
					//							{
					//								Object::editTextField->addChar('_');
					//								break;
					//							}break;
					break;
				case SDLK_LEFTBRACKET:
					if(dc->getBitDepth() > DEPTH_8BIT)
					{
						dc->setBitDepth((eBitDepth)(dc->getBitDepth()-1));
						SDL_Object::redrawAllRootObjects();
						std::list<std::string> strlist = boost::assign::list_of(boost::lexical_cast<std::string>((int)(dc->getSurface()->format->BitsPerPixel)));
						toInfoLog(TextStorage::instance().get(IDS::CHANGED_BIT_DEPTH_TEXT_ID)->getText(strlist));
					}
					break;
				case SDLK_RIGHTBRACKET:
					if(dc->getBitDepth() < DEPTH_32BIT)
					{
						dc->setBitDepth((eBitDepth)(dc->getBitDepth()+1));
						SDL_Object::redrawAllRootObjects();
						std::list<std::string> strlist = boost::assign::list_of(boost::lexical_cast<std::string>((int)(dc->getSurface()->format->BitsPerPixel)));
						toInfoLog(TextStorage::instance().get(IDS::CHANGED_BIT_DEPTH_TEXT_ID)->getText(strlist));
					}
					break;
				case SDLK_F11:
					if(background.getBitmapId() == IDS::BACKGROUND_SC_BITMAP_ID) {
						background.updateBitmap(BitmapStorage::instance().get(IDS::BACKGROUND1_SC2_BITMAP_ID));
					} else 
					if(background.getBitmapId() == IDS::BACKGROUND1_SC2_BITMAP_ID) {
						background.updateBitmap(BitmapStorage::instance().get(IDS::BACKGROUND2_SC2_BITMAP_ID));
					} else 
					if(background.getBitmapId() == IDS::BACKGROUND2_SC2_BITMAP_ID) {
						background.updateBitmap(BitmapStorage::instance().get(IDS::BACKGROUND_SC_BITMAP_ID));
					}break;
				case SDLK_F12:
					if(TextStorage::getCurrentLanguageId() == IDS::ENGLISH_LANGUAGE_ID) {
						TextStorage::updateLanguage(IDS::GERMAN_LANGUAGE_ID);
					} else {
						TextStorage::updateLanguage(IDS::ENGLISH_LANGUAGE_ID);
					}
					break;
					//						case SDLK_F6:t.mainWindow->forcePressTab(MAP_TAB);break;
					//						case SDLK_F7:t.mainWindow->forcePressTab(SETTINGS_TAB);break;
					//						case SDLK_F8:t.mainWindow->forcePressTab(HELP_TAB);break;
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
					/*if(Object::editTextField!=NULL)
					{
					if(event.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT)) {
					Object::editTextField->addChar('A'+event.key.keysym.sym-SDLK_a);
					} else {
					Object::editTextField->addChar('a'+event.key.keysym.sym-SDLK_a);
					}
					}*/
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
					/*if(Object::editTextField!=NULL) {
					Object::editTextField->addChar('0'+event.key.keysym.sym-SDLK_0);
					}*/
					break;

				case SDLK_LEFT:
					/*if(Object::editTextField!=NULL) {
					Object::editTextField->moveLeft();
					}*/
					break;

				case SDLK_RIGHT:
					/*if(Object::editTextField!=NULL) {
					Object::editTextField->moveRight();
					}*/
					break;

				default:break;
				}
				break;
			default:break;
			}
		}
	}

	return EXIT_SUCCESS;
}



