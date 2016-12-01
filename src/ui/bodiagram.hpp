#ifndef _UI_BODIAGRAM_HPP
#define _UI_BODIAGRAM_HPP

#include <gui/window.hpp>
#include <gui/diagram.hpp>
#include "../core/database.hpp"
#include "../core/anabuildorder.hpp"
#include "configuration.hpp"

class BoDiagramWindow : public Window 
{
	public:
		BoDiagramWindow(Object* bod_parent, const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		~BoDiagramWindow();

		void resetData();
		void process();
		void processList();
		void draw() const;

		void assignAnarace(ANABUILDORDER* bod_anarace);
		void setMode(const unsigned int game_number, const unsigned int game_max, const unsigned int player_number, const unsigned int player_max);
		void reloadOriginalSize();

		const std::list<unsigned int>& getSelectedItems() const;
		void setSelected(const std::list<unsigned int>& selected);
	private:
		UI_Diagram* diagram;
		static unsigned int HAVE_SUPPLY;
		static unsigned int NEED_SUPPLY;
		ANABUILDORDER* anarace;
		
		std::list<unsigned int> selectedItems;
		std::list<unsigned int> tempSelectedItems;
		
		unsigned int count;
		bool bold;
		unsigned int mouseTime;
		unsigned int totalTime;
		Point oldMouse;

		unsigned int gameNumber;
		unsigned int gameMax;
		unsigned int playerNumber;
		unsigned int playerMax;

		unsigned int firstTime;
		unsigned int lastTime;
	
		BoDiagramWindow(const BoDiagramWindow& object);
		BoDiagramWindow& operator=(const BoDiagramWindow& object);
};

inline const std::list<unsigned int>& BoDiagramWindow::getSelectedItems() const {
	return(selectedItems);
}

#endif // _UI_BODIAGRAM_HPP
