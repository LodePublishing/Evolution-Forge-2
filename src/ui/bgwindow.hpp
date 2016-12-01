#ifndef _UI_BOGRAPH_WINDOW_HPP
#define _UI_BOGRAPH_WINDOW_HPP

#if 0

#include <gui/window.hpp>
#include "bgline.hpp"
#include "../core/anabuildorder.hpp"

#define BOGRAPH_MAX_LINES 30


class BoGraphWindow : public Window
{
	public:
		BoGraphWindow(Object* bograph_parent, const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		BoGraphWindow(Object* bograph_parent, const unsigned int bograph_window_number);
		~BoGraphWindow();

		void setMode(const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		void reloadOriginalSize();
		void resetData();
		void process();
		void processList();
		void draw() const;
	    	void mouseHasMoved();
		void assignAnarace(ANABUILDORDER* bograph_anarace);
		
		const std::list<unsigned int>& getSelectedItems() const;
		void setSelected(const std::list<unsigned int>& selected);
	private:
//		BoGraphWindow(const BoGraphWindow& object); // don't allow copying... wouldn't make sense... :-/
//		BoGraphWindow& operator=(const BoGraphWindow& object);
	
		std::list<BoGraphLine*> boGraphLine;

		void checkForInfoWindow();
		unsigned int markAni;
		ANABUILDORDER* anarace;
		std::list<unsigned int> selectedItems;
//		std::list<StaticText*> legend;
		unsigned int gameNumber;
		unsigned int gameMax;
		unsigned int playerNumber;
		unsigned int playerMax;
		unsigned int lastRace;
		unsigned int totalTime;
};

inline const std::list<unsigned int>& BoGraphWindow::getSelectedItems() const {
	return(selectedItems);
}

#endif

#endif // _UI_BOGRAPH_WINDOW_HPP