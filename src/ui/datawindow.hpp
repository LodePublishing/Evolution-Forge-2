#ifndef _UI_DATABASE_WINDOW_HPP
#define _UI_DATABASE_WINDOW_HPP

#include <gui/window.hpp>
#include "dataentry.hpp"
#include "game.hpp"

class DataBaseWindow : public Window
{
	public:
		DataBaseWindow(Object* data_window_parent);
		~DataBaseWindow();
		
		void resetData();
		void process();
		void draw() const;

		void reloadOriginalSize();

		void newGeneration();

		// goal liste (loeschbar)
		// liste (aehnlich bowindow) von build-order-namen und Zeit (geordnet nach Zeit) (auch loeschbar)
		// wenn da eins angeklickt wird dann erscheint die build order in einem weiteren Fenster (split-screen)
	
	private:
//		void saveBoxDone(const std::string file_name);
//		void saveBoxCanceled();
		
		void activateGame();
		void mouseHasLeft();
		void updateList();
		void updateItemPositions();
	
		std::list<DataBaseEntry*> dataList;
		Window* dataListWindow;
		
		unsigned int currentRace;
		unsigned int currentBuildOrder;
		unsigned int currentGoal;
		
 		Game* game;
		bool needUpdate;
		
//		Button* executeButton; // apply changes to the disk
//		Button* exportDataBase; // write everything in one file
//		Button* importDataBase; // import such a file and add it to the database without overwriting things ~~
//		
//		Button* deleteButton; // delete all marked items
//		Button* exportBoAsHTML;
//		Button* exportBoAsDingens;
//		Button* exportBoAsPicture;
//		StaticText* ein paar Erklaerungen, ueberschriften

		
// jeder goal eintrag kann geoeffnet oder geschlossen werden (wie [+] [-] bei windows guis), am besten mit Pfeil > und Pfeil v
// auf der rechten Seite erscheint dann ein 'game' mit der aktuellen build order, sobald ein goal oder bo MARKIERT wurde
// wenn goals markiert werden => besondere situation, bowindow soll dann nur force window darstellen (bzw. den Rest auch)
// => erst mal keine Eingabemoeglichkeit auf der rechten Seite? mmmh... ne, ganz normal...
// 

// => DataEntry: bool isGoal, Button* openclose, Button* delete, Button* this (text button bestehend aus goal/bonamen und Zeit falls kein goal bzw. (<ZAHL>) Anzahl der im Ordner gespeicherten bos), Button* exportAsPicture, Button* exportAsHTML, Button* exportAsBoDingens...
		
/*

		Button* sortBOsByGoal;

		Button* importDatabase; // => saveBox (ersetzen?)
		Button* exportDatabase; // => saveBox

		bool saveBoxImport;
		bool saveBoxExport;

		
// => aktualisierungsfunktion (sobald auf database umgeschaltet wird oder wenn geloescht wird)
		std::list<std::pair<GOAL_ENTRY*, std::list<BUILD_ORDER*> > > boList;*/
		
};

#endif

