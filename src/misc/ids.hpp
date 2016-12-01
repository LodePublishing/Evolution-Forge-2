#ifndef _MISC_IDS_HPP
#define _MISC_IDS_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <misc/miscellaneous.hpp>
#pragma warning(pop)

struct IDS
{

static const boost::uuids::uuid ENGLISH_LANGUAGE_ID;
static const boost::uuids::uuid GERMAN_LANGUAGE_ID;

static const boost::uuids::uuid START_INIT_SDL_TEXT_ID;
static const boost::uuids::uuid START_SET_FULLSCREEN_MODE_TEXT_ID;
static const boost::uuids::uuid START_SET_WINDOW_MODE_TEXT_ID;
static const boost::uuids::uuid START_UNABLE_TO_INIT_SDL_TEXT_ID;
static const boost::uuids::uuid START_ERROR_SETTING_VIDEO_MODE_TEXT_ID;
static const boost::uuids::uuid START_CREATED_SURFACE_TEXT_ID;
static const boost::uuids::uuid START_INIT_SDL_TRUETYPE_FONTS_TEXT_ID;
static const boost::uuids::uuid START_INIT_SDL_TTF_ERROR_TEXT_ID;
static const boost::uuids::uuid START_LOAD_CONFIGURATION_TEXT_ID;
static const boost::uuids::uuid END_RESET_MOUSE_CURSOR_TEXT_ID;
static const boost::uuids::uuid END_FREEING_COLORS_BRUSHES_PENS_TEXT_ID;
static const boost::uuids::uuid END_FREEING_BITMAPS_TEXT_ID;
static const boost::uuids::uuid END_FREEING_ANIMATIONS_TEXT_ID;
static const boost::uuids::uuid END_FREEING_COORDINATES_TEXT_ID;
static const boost::uuids::uuid END_FREEING_BUTTONS_TEXT_ID;
static const boost::uuids::uuid END_FREEING_FONTS_TEXT_ID;
static const boost::uuids::uuid START_SDL_NO_MODES_AVAILABLE_TEXT_ID;
static const boost::uuids::uuid START_SDL_ALL_RESOLUTIONS_AVAILABLE_TEXT_ID;
static const boost::uuids::uuid START_SDL_AVAILABLE_MODES_TEXT_ID;
static const boost::uuids::uuid START_SDL_MAX_COLOR_DEPTH_TEXT_ID;
static const boost::uuids::uuid START_SDL_HARDWARE_SURFACES_POSSIBLE_TEXT_ID;
static const boost::uuids::uuid START_SDL_WINDOW_MANAGER_AVAILABLE_TEXT_ID;
static const boost::uuids::uuid START_SDL_SOFTWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_SOFTWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_SOFTWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_HARDWARE_TO_HARDWARE_BLITS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_HARDWARE_TO_HARDWARE_COLORKEY_BLITS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_HARDWARE_TO_HARDWARE_ALPHA_BLITS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_COLOR_FILLS_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_TOTAL_VIDEO_MEMORY_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_STORED_IN_SYSTEM_MEMORY_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_STORED_IN_VIDEO_MEMORY_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_USES_ASYNCHRONOUS_BLITS_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_ALLOWS_ANY_PIXEL_FORMAT_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_HAS_EXCLUSIVE_PALETTE_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_IS_DOUBLE_BUFFERED_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_HAS_OPENGL_CONTEXT_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_SUPPORTS_OPENGL_BLITTING_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_IS_RESIZABLE_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_BLIT_USES_HARDWARE_ACCELERATION_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_USES_COLORKEY_BLITTING_TEXT_ID;
static const boost::uuids::uuid START_SDL_COLORKEY_BLITTING_RLE_ACCELERATED_TEXT_ID;
static const boost::uuids::uuid START_SDL_BLIT_USES_ALPHA_BLENDING_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_USES_PREALLOCATED_MEMORY_TEXT_ID;
static const boost::uuids::uuid START_SDL_SURFACE_NEEDS_LOCKING_TEXT_ID;
static const boost::uuids::uuid END_RELEASING_SOUND_ENGINE_TEXT_ID;
static const boost::uuids::uuid END_CLOSING_SOUND_ENGINE_TEXT_ID;
static const boost::uuids::uuid START_INIT_SOUND_TEXT_ID;
static const boost::uuids::uuid START_INIT_FMOD_SYSTEM_CREATE_ERROR_TEXT_ID;
static const boost::uuids::uuid START_INIT_FMOD_GET_VERSION_ERROR_TEXT_ID;
static const boost::uuids::uuid START_INIT_FMOD_VERSION_ERROR_TEXT_ID;
static const boost::uuids::uuid START_INIT_FMOD_SYSTEM_INIT_ERROR_TEXT_ID;
static const boost::uuids::uuid START_INIT_NOSOUND_TEXT_ID;
static const boost::uuids::uuid WELCOME_TEXT_ID;


// ------ BITMAPS ------
static const boost::uuids::uuid NULL_BITMAP;
static const boost::uuids::uuid INCREASE_BITMAP;
static const boost::uuids::uuid SUB_BITMAP;
static const boost::uuids::uuid CANCEL_BITMAP;
static const boost::uuids::uuid SMALL_ARROW_LEFT_BITMAP;
static const boost::uuids::uuid SMALL_ARROW_RIGHT_BITMAP;
static const boost::uuids::uuid SMALL_ARROW_UP_BITMAP;
static const boost::uuids::uuid SMALL_ARROW_DOWN_BITMAP;
static const boost::uuids::uuid LOCATION_BUTTON_BITMAP;
static const boost::uuids::uuid TIME_BUTTON_BITMAP;

static const boost::uuids::uuid BLUE_RADIO_OFF_BITMAP;
static const boost::uuids::uuid BLUE_RADIO_ON_BITMAP;
static const boost::uuids::uuid RED_RADIO_OFF_BITMAP;
static const boost::uuids::uuid RED_RADIO_ON_BITMAP;
static const boost::uuids::uuid YELLOW_RADIO_OFF_BITMAP;
static const boost::uuids::uuid YELLOW_RADIO_ON_BITMAP;
static const boost::uuids::uuid GREY_RADIO_OFF_BITMAP;
static const boost::uuids::uuid GREYRADIO_ON_BITMAP;

static const boost::uuids::uuid BACKGROUND_SC_BITMAP;

static const boost::uuids::uuid BAR_BITMAP;
static const boost::uuids::uuid KEY_BITMAP;

static const boost::uuids::uuid CLAWSOFTWARE_BITMAP;
static const boost::uuids::uuid CLAWSOFTWARE_MONO_BITMAP;

static const boost::uuids::uuid NEW_BITMAP;
static const boost::uuids::uuid LOAD_BITMAP; 
static const boost::uuids::uuid SAVE_BITMAP; 
static const boost::uuids::uuid REFRESH_BITMAP; 

static const boost::uuids::uuid BACK_BITMAP;
static const boost::uuids::uuid FORWARD_BITMAP; 
static const boost::uuids::uuid ADD_BITMAP; 
static const boost::uuids::uuid DELETE_BITMAP; 

static const boost::uuids::uuid HELP_BITMAP; 
static const boost::uuids::uuid MAP_BITMAP;
static const boost::uuids::uuid SETTING_BITMAP; 

static const boost::uuids::uuid BLUE_BULLET_BITMAP; 
static const boost::uuids::uuid RED_BULLET_BITMAP; 
static const boost::uuids::uuid YELLOW_BULLET_BITMAP; 
	
static const boost::uuids::uuid ARROW_LEFT_BITMAP;
static const boost::uuids::uuid ARROW_RIGHT_BITMAP;
static const boost::uuids::uuid ARROW_UP_BITMAP;
static const boost::uuids::uuid ARROW_DOWN_BITMAP;
		
static const boost::uuids::uuid CLICKED_SMALL_ARROW_LEFT_BITMAP;
static const boost::uuids::uuid CLICKED_SMALL_ARROW_RIGHT_BITMAP;
static const boost::uuids::uuid CLICKED_ARROW_LEFT_BITMAP;
static const boost::uuids::uuid CLICKED_ARROW_RIGHT_BITMAP;
static const boost::uuids::uuid CLICKED_SMALL_ARROW_UP_BITMAP;
static const boost::uuids::uuid CLICKED_SMALL_ARROW_DOWN_BITMAP;
static const boost::uuids::uuid CLICKED_ARROW_UP_BITMAP;
static const boost::uuids::uuid CLICKED_ARROW_DOWN_BITMAP;
	
	
static const boost::uuids::uuid INTRO_SDL_BITMAP;
static const boost::uuids::uuid INTRO_SDL_TTF_BITMAP;
static const boost::uuids::uuid INTRO_SDL_IMAGE_BITMAP;
static const boost::uuids::uuid INTRO_GUI_BITMAP;
static const boost::uuids::uuid INTRO_SMPEG_BITMAP;
static const boost::uuids::uuid INTRO_FMOD_BITMAP;
static const boost::uuids::uuid INTRO_SDL_MIXER_BITMAP;


static const boost::uuids::uuid DEFAULT_GUI_CONFIGURATION_ID;
static const boost::uuids::uuid DEFAULT_GUI_ID;
static const boost::uuids::uuid DEFAULT_MAIN_CONFIGURATION_ID;

// ----- COLORS -----

// ----- COLORS END -----

// ----- FONTS -----
// ----- FONTS END -----

};

#endif // _MISC_IDS_HPP
