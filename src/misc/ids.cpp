#include "ids.hpp"
#include "miscellaneous.hpp"

// ---- STRINGS ----



// ---- GUI ----
const boost::uuids::uuid IDS::START_INIT_SDL_TEXT_ID = Misc::uuid("e438cdf0-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SET_FULLSCREEN_MODE_TEXT_ID = Misc::uuid("e81f08d0-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SET_WINDOW_MODE_TEXT_ID = Misc::uuid("eaf4be10-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_UNABLE_TO_INIT_SDL_TEXT_ID = Misc::uuid("ed5ee040-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_ERROR_SETTING_VIDEO_MODE_TEXT_ID = Misc::uuid("f4d74290-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_CREATED_SURFACE_TEXT_ID = Misc::uuid("f82227d0-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_SDL_TRUETYPE_FONTS_TEXT_ID = Misc::uuid("fe0e1dc0-4b5b-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_SDL_TTF_ERROR_TEXT_ID = Misc::uuid("00eb4d10-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_LOAD_CONFIGURATION_TEXT_ID = Misc::uuid("036bb660-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_RESET_MOUSE_CURSOR_TEXT_ID = Misc::uuid("05d4a010-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_FREEING_COLORS_BRUSHES_PENS_TEXT_ID = Misc::uuid("080ba450-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_FREEING_BITMAPS_TEXT_ID = Misc::uuid("0a8c82d0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_FREEING_ANIMATIONS_TEXT_ID = Misc::uuid("0ddf3040-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_FREEING_COORDINATES_TEXT_ID = Misc::uuid("10600ec0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_FREEING_BUTTONS_TEXT_ID = Misc::uuid("138e6b50-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_FREEING_FONTS_TEXT_ID = Misc::uuid("16265440-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_NO_MODES_AVAILABLE_TEXT_ID = Misc::uuid("18ecee50-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_ALL_RESOLUTIONS_AVAILABLE_TEXT_ID = Misc::uuid("1b3cf8d0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_AVAILABLE_MODES_TEXT_ID = Misc::uuid("1d8d5170-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_MAX_COLOR_DEPTH_TEXT_ID = Misc::uuid("1fbbf140-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_HARDWARE_SURFACES_POSSIBLE_TEXT_ID = Misc::uuid("222ec600-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_WINDOW_MANAGER_AVAILABLE_TEXT_ID = Misc::uuid("24a2d340-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SOFTWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID = Misc::uuid("26f74a90-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SOFTWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID = Misc::uuid("29525190-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SOFTWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID = Misc::uuid("2bd971a0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_HARDWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID = Misc::uuid("2e3a6c10-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_HARDWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID = Misc::uuid("30923ec0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_HARDWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID = Misc::uuid("32d81010-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_COLOR_FILLS_ACCELERATED_TEXT_ID = Misc::uuid("35024310-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_TOTAL_VIDEO_MEMORY_TEXT_ID = Misc::uuid("38e0dcd0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_STORED_IN_SYSTEM_MEMORY_TEXT_ID = Misc::uuid("3b90ba90-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_STORED_IN_VIDEO_MEMORY_TEXT_ID = Misc::uuid("3dbfcf90-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_USES_ASYNCHRONOUS_BLITS_TEXT_ID = Misc::uuid("42b5f3d0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_ALLOWS_ANY_PIXEL_FORMAT_TEXT_ID = Misc::uuid("452bd5d0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_HAS_EXCLUSIVE_PALETTE_TEXT_ID = Misc::uuid("47718010-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_IS_DOUBLE_BUFFERED_TEXT_ID = Misc::uuid("49a43e90-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_HAS_OPENGL_CONTEXT_TEXT_ID = Misc::uuid("4bb914d0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_SUPPORTS_OPENGL_BLITTING_TEXT_ID = Misc::uuid("4e671dd0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_IS_RESIZABLE_TEXT_ID = Misc::uuid("50817250-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_BLIT_USES_HARDWARE_ACCELERATION_TEXT_ID = Misc::uuid("5350bef0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_USES_COLORKEY_BLITTING_TEXT_ID = Misc::uuid("56552550-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_COLORKEY_BLITTING_RLE_ACCELERATED_TEXT_ID = Misc::uuid("58db8210-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_BLIT_USES_ALPHA_BLENDING_TEXT_ID = Misc::uuid("5b80ff90-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_USES_PREALLOCATED_MEMORY_TEXT_ID = Misc::uuid("5dcdfcd0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_SDL_SURFACE_NEEDS_LOCKING_TEXT_ID = Misc::uuid("600cf050-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_RELEASING_SOUND_ENGINE_TEXT_ID = Misc::uuid("62a6d510-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::END_CLOSING_SOUND_ENGINE_TEXT_ID = Misc::uuid("64d06bd0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_SOUND_TEXT_ID = Misc::uuid("66fac5e0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_FMOD_SYSTEM_CREATE_ERROR_TEXT_ID = Misc::uuid("6966e3e0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_FMOD_GET_VERSION_ERROR_TEXT_ID = Misc::uuid("6ba9f610-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_FMOD_VERSION_ERROR_TEXT_ID = Misc::uuid("6de2cf10-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_FMOD_SYSTEM_INIT_ERROR_TEXT_ID = Misc::uuid("70b4b3c0-4b5c-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::START_INIT_NOSOUND_TEXT_ID = Misc::uuid("73009f90-4b5c-11e0-b8af-0800200c9a66");

// ------ BITMAPS ------
const boost::uuids::uuid IDS::NULL_BITMAP = Misc::uuid("b428fec0-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INCREASE_BITMAP =  Misc::uuid("ba7a6d40-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::SUB_BITMAP = Misc::uuid("bd68daa0-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CANCEL_BITMAP = Misc::uuid("bfad7370-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::SMALL_ARROW_LEFT_BITMAP = Misc::uuid("c2311110-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::SMALL_ARROW_RIGHT_BITMAP = Misc::uuid("c47b7640-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::SMALL_ARROW_UP_BITMAP = Misc::uuid("c6892090-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::SMALL_ARROW_DOWN_BITMAP = Misc::uuid("c8ac9cd0-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::LOCATION_BUTTON_BITMAP = Misc::uuid("cac23660-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::TIME_BUTTON_BITMAP = Misc::uuid("cd968c10-4dc0-11e0-b8af-0800200c9a66");

const boost::uuids::uuid IDS::BLUE_RADIO_OFF_BITMAP = Misc::uuid("017e6cb0-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::BLUE_RADIO_ON_BITMAP = Misc::uuid("042cc3d0-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::RED_RADIO_OFF_BITMAP = Misc::uuid("06f8b510-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::RED_RADIO_ON_BITMAP = Misc::uuid("09d5bd50-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::YELLOW_RADIO_OFF_BITMAP = Misc::uuid("0cfffb30-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::YELLOW_RADIO_ON_BITMAP = Misc::uuid("10877440-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::GREY_RADIO_OFF_BITMAP = Misc::uuid("13e60890-4dca-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::GREYRADIO_ON_BITMAP = Misc::uuid("173078a0-4dca-11e0-b8af-0800200c9a66");

const boost::uuids::uuid IDS::BACKGROUND_SC_BITMAP = Misc::uuid("d5d572b0-4dc0-11e0-b8af-0800200c9a66");

const boost::uuids::uuid IDS::BAR_BITMAP = Misc::uuid("e7b281d0-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::KEY_BITMAP = Misc::uuid("ea0fabb0-4dc0-11e0-b8af-0800200c9a66");

const boost::uuids::uuid IDS::CLAWSOFTWARE_BITMAP = Misc::uuid("eca809d0-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLAWSOFTWARE_MONO_BITMAP = Misc::uuid("ef00c6e0-4dc0-11e0-b8af-0800200c9a66");

const boost::uuids::uuid IDS::NEW_BITMAP = Misc::uuid("f14dc420-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::LOAD_BITMAP = Misc::uuid("f41f0c90-4dc0-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::SAVE_BITMAP = Misc::uuid("f6526750-4dc0-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::REFRESH_BITMAP = Misc::uuid("f8e1ebd0-4dc0-11e0-b8af-0800200c9a66"); 

const boost::uuids::uuid IDS::BACK_BITMAP = Misc::uuid("fb55aaf0-4dc0-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::FORWARD_BITMAP = Misc::uuid("fd655110-4dc0-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::ADD_BITMAP = Misc::uuid("ffa703b0-4dc0-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::DELETE_BITMAP = Misc::uuid("01f894d0-4dc1-11e0-b8af-0800200c9a66"); 

const boost::uuids::uuid IDS::HELP_BITMAP = Misc::uuid("042e3980-4dc1-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::MAP_BITMAP = Misc::uuid("065eae10-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::SETTING_BITMAP = Misc::uuid("08c3a020-4dc1-11e0-b8af-0800200c9a66"); 

const boost::uuids::uuid IDS::BLUE_BULLET_BITMAP = Misc::uuid("0ceeac30-4dc1-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::RED_BULLET_BITMAP = Misc::uuid("cd5a3040-4dc9-11e0-b8af-0800200c9a66"); 
const boost::uuids::uuid IDS::YELLOW_BULLET_BITMAP = Misc::uuid("d31467d0-4dc9-11e0-b8af-0800200c9a66"); 
	
const boost::uuids::uuid IDS::ARROW_LEFT_BITMAP = Misc::uuid("152c5a50-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::ARROW_RIGHT_BITMAP = Misc::uuid("19685650-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::ARROW_UP_BITMAP = Misc::uuid("1d9b2a90-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::ARROW_DOWN_BITMAP = Misc::uuid("21fc13b0-4dc1-11e0-b8af-0800200c9a66");
		
const boost::uuids::uuid IDS::CLICKED_SMALL_ARROW_LEFT_BITMAP = Misc::uuid("26bcd010-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_SMALL_ARROW_RIGHT_BITMAP = Misc::uuid("28e3f5d0-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_ARROW_LEFT_BITMAP = Misc::uuid("4c8c60d0-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_ARROW_RIGHT_BITMAP = Misc::uuid("4e7dd090-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_SMALL_ARROW_UP_BITMAP = Misc::uuid("509d0710-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_SMALL_ARROW_DOWN_BITMAP = Misc::uuid("534a73d0-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_ARROW_UP_BITMAP = Misc::uuid("5593c790-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::CLICKED_ARROW_DOWN_BITMAP = Misc::uuid("57ab0ed0-4dc1-11e0-b8af-0800200c9a66");
	
	
const boost::uuids::uuid IDS::INTRO_SDL_BITMAP = Misc::uuid("5be36150-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INTRO_SDL_TTF_BITMAP = Misc::uuid("5ed2b910-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INTRO_SDL_IMAGE_BITMAP = Misc::uuid("60d42e60-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INTRO_GUI_BITMAP = Misc::uuid("62fc3e80-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INTRO_SMPEG_BITMAP = Misc::uuid("6542ac10-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INTRO_FMOD_BITMAP = Misc::uuid("6774ce50-4dc1-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::INTRO_SDL_MIXER_BITMAP = Misc::uuid("697ad780-4dc1-11e0-b8af-0800200c9a66");


const boost::uuids::uuid IDS::DEFAULT_GUI_CONFIGURATION_ID = Misc::uuid("0d3c67b0-4e69-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::DEFAULT_GUI_ID = Misc::uuid("3d73caf0-4f58-11e0-b8af-0800200c9a66");
const boost::uuids::uuid IDS::DEFAULT_MAIN_CONFIGURATION_ID = Misc::uuid("ed97ad00-4e9c-11e0-b8af-0800200c9a66");

const boost::uuids::uuid IDS::ENGLISH_LANGUAGE_ID = Misc::uuid("e0962fd0-3201-11e0-bc8e-0800200c9a66");
const boost::uuids::uuid IDS::GERMAN_LANGUAGE_ID = Misc::uuid("e3b06820-3201-11e0-bc8e-0800200c9a66");

const boost::uuids::uuid IDS::WELCOME_TEXT_ID = Misc::uuid("e3f57230-50d3-11e0-b8af-0800200c9a66");