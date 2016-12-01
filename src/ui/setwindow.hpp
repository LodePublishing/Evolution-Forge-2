#ifndef _UI_SETTINGS_HPP
#define _UI_SETTINGS_HPP

#include <gui/window.hpp>
#include <gui/radio.hpp>
#include <gui/numberfield.hpp>

#include <gui/menu.hpp>

class SettingsWindow:public Window
{
	public:
		SettingsWindow(Object* setwindow_parent);
		~SettingsWindow();
		
		void resetDataChange();
		void process();
		void updateItems();

		void forceLanguageChange();
		void forceResolutionChange();
		void forceBitDepthChange();
		void forceFullScreenChange();
		void reloadOriginalSize();
		
		const bool hasLanguageChanged() const;
		const bool hasResolutionChanged() const;
		const bool hasBitDepthChanged() const;
		const bool hasThemeChanged() const;
		const bool hasFullScreenChanged() const;
		const bool hasCompactDisplayModeChanged() const;
		const bool hasBackGroundChanged() const;
		const bool hasAllowWaitOrdersChanged() const;
//		const bool hasGameSpeedChanged() const;
	private:

		void reloadFromFile();
		void loadDefaults();
		void closeMenus();

		// TODO: SEttings ueberarbeiten
//
//
// 
//
//
// maxLength raus => dynamisch anpassen (und grosser interner Maximalwert)
//
// GAMMA NumberField!
// TODO SDL_SetAlpha(surface, SDL_SRCALPHA, 128) !!!!!!!!!!
//  
// waitorders, breedfactor, timeout, maxLength, maxTimeOut, ... in ein 'fast calculate' CheckButton zusammenfassen
// breedfactor in CheckButton (Tiefen/Breitensuche), evtl 'max programs' wieder dazu
//		Button* transparency;
// Option bowindow, bodiagram window oder bograph window nicht anzuzeigen
//		Button* softwareMouse;

		Group* uberSettings;

		Group* coreSettings;
		Group* soundSettings;
		
		Group* guiSettings;
		Group* graphicSettings;

		Radio* uiSettingsRadio;
		Group* loadSaveSettings;

		Button* fastCalculation;
		Button* alwaysBuildWorkers;
		Button* allowWaitOrders;
		NumberField* waitAccuracy;
//		NumberField* gameSpeed;
		Button* autoRuns;
		NumberField* maxGenerations;
		
		Button* useMusic;
		NumberField* musicVolume;
		Button* useSound;
		NumberField* soundVolume;
		NumberField* channels; // TODO evtl raus
		
		Button* backgroundBitmap;
		Button* smoothMovement;
		Button* waitAfterChange;
		Button* tooltips;
		Button* dnaSpiral;
		Button* raceSpecificTheme;
		Button* glowingButtons;
		Button* compactDisplayMode;
		Button* facilityMode;
		
		Button* fullscreen;
		Button* unloadGraphics;
		Button* showDebug;
		NumberField* desiredFramerate;
		NumberField* desiredCPU;
	
		Button* reloadFromFileButton;
		Button* saveToFileButton;
		Button* loadDefaultsButton;

// number
	
		Button* languageMenuButton;
		Button* resolutionMenuButton;
		Button* bitDepthMenuButton;
		Button* themeMenuButton;
		Menu* languageMenu;
		Menu* resolutionMenu;
		Menu* bitDepthMenu;
		Menu* themeMenu;

		bool languageHasChanged;
		bool resolutionHasChanged;
		bool bitDepthHasChanged;
		bool themeHasChanged;
		bool fullScreenHasChanged;
		bool compactDisplayModeHasChanged;
		bool backGroundHasChanged;
		bool allowWaitOrdersHasChanged;
//		bool gameSpeedHasChanged;
};

inline const bool SettingsWindow::hasLanguageChanged() const {
	return(languageHasChanged);
}

inline const bool SettingsWindow::hasResolutionChanged() const {
	return(resolutionHasChanged);
}

inline const bool SettingsWindow::hasBitDepthChanged() const {
	return(bitDepthHasChanged);
}

inline const bool SettingsWindow::hasThemeChanged() const {
	return(themeHasChanged);
}

inline const bool SettingsWindow::hasFullScreenChanged() const {
	return(fullScreenHasChanged);
}

inline const bool SettingsWindow::hasCompactDisplayModeChanged() const {
	return(compactDisplayModeHasChanged);
}

inline const bool SettingsWindow::hasBackGroundChanged() const {
	return(backGroundHasChanged);
}

inline const bool SettingsWindow::hasAllowWaitOrdersChanged() const {
	return(allowWaitOrdersHasChanged);
}

//inline const bool SettingsWindow::hasGameSpeedChanged() const {
//	return(gameSpeedHasChanged);
//}

inline void SettingsWindow::forceResolutionChange() {
	resolutionHasChanged = true;
}

inline void SettingsWindow::forceBitDepthChange() {
	bitDepthHasChanged = true;
}

inline void SettingsWindow::forceLanguageChange() {
	languageHasChanged=true;
}

#endif

