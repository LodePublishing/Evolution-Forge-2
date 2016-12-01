#ifndef _UI_BOWINDOW_HPP
#define _UI_BOWINDOW_HPP

#if 0

#include <gui/window.hpp>
#include <gui/group.hpp>

#include "boentry.hpp"
#include "bomenu.hpp"
#include "unitmenu.hpp"

class BoWindow : public Window
{
	public:
		BoWindow(const BoWindow& object);
		BoWindow& operator=(const BoWindow& object);
		BoWindow(Object* bo_parent, const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		~BoWindow();
		void resetData();
		void draw() const;
//		void reloadStrings();
		void processList();
		void process();

		void assignAnarace(ANABUILDORDER* bo_anarace);
		void setMode(const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		void reloadOriginalSize();

		const bool wasResetted() const;

		const std::list<unsigned int>& getSelectedItems() const;
		void setSelected(const std::list<unsigned int>& selected);

		void recheckSomeDataAfterChange();
		
		void needSaveBox();
		void saveBoxIsCanceled();
		void saveBoxIsDone(std::string input_string);

		const bool saveBuildOrder();
		const bool openBoMenu();
		void mouseHasLeft();
		const signed int getLoadedBuildOrder() const;

		const bool areBosStillMoving() const;
	private:
		float geneAnimation;
		void drawGeneString() const;
		void drawGene(unsigned int k, const Point* points, const Point position, Pen& bla1, Pen& bla2) const;

		void closeMenus();
		void drawSelectionStuff() const;
		void checkForInfoWindow();
//		void resetButtons();
		ANABUILDORDER* anarace;
		std::list<BoEntry*> boList;
//		Rect moveTarget;
		unsigned int optimizeMode;
		signed int addUnit;
//		bool wasMovedByMouse;
//		signed int boInsertPoint, boEndPoint;
//		int makeSpaceButton;
//		int unitButton[2*MAX_LENGTH];
//		int optButton[2*MAX_LENGTH];
//		int orderButton[2*MAX_LENGTH];
		unsigned int boGoalListOpened;
		unsigned int lastBogoal;
		unsigned int startLine;
		std::list<unsigned int> selectedItems;


//		StaticText* timeSlot[60];

		Group* menuGroup;
		Button* restartBuildOrderButton;
		Button* saveBuildOrderButton;
		Button* loadBuildOrderButton;
		
		UI_ScrollBar* scrollBar;
//		Button* alwaysBuildWorker;
//		Button* onlySwapOrders;
		
//		Button* unitMenuButton;
//		UnitMenu* unitMenu;

		BoMenu* boMenu;
	
		unsigned int gameNumber;
		unsigned int gameMax;
		unsigned int playerNumber;
		unsigned int playerMax;

		bool saveBox;

		bool boMenuOpenedExternally;

		signed int loadedBuildOrder;
};

inline const signed int BoWindow::getLoadedBuildOrder() const {
	return(loadedBuildOrder);
}

inline const std::list<unsigned int>& BoWindow::getSelectedItems() const {
	return(selectedItems);
}

#endif

#endif // _UI_BOWINDOW_HPP

