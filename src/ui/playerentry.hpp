#ifndef _UI_PLAYERENTRY_HPP
#define _UI_PLAYERENTRY_HPP

#if 0

#include <gui/radio.hpp>
#include "racemenu.hpp"

enum eScoreMode
{
	SCORE_FULFILL_MODE,
	SCORE_TIME_MODE,
	SCORE_MODE	
};

enum eInitMode
{
	INACTIVE, // => 'add player' button active
	NOT_INITIALIZED, // => waiting for user to pick race
	INITIALIZED	// everything ok
};

/*enum ePlayerEntryMenu
{
        RACE_MENU,
        MAX_PLAYER_ENTRY_MENUS
};*/


class PlayerEntry : public Object
{
	public:
		PlayerEntry(Object* player_parent, const Rect rect, const Size distance_bottom_right);
		~PlayerEntry();

		void setScore(const unsigned int score);
		void setGoalComplete(const unsigned int goal_complete);
		void setOptimizing(const bool opt=true);
		void setInitMode(const eInitMode init_mode);
		void setScoreMode(const eScoreMode score_mode);
		void setNumber(const unsigned int player_number);
		const eScoreMode getScoreMode() const;
		const eInitMode getInitMode() const;

		void resetData();
		void resetTime();
		const bool isOptimizing() const;

		void process();

		void reloadOriginalSize();
		void reloadStrings();
		
		const unsigned int getLineHeight() const;

		const signed int getAssignedRace() const;
		void mouseHasLeft();

		const bool addPlayer();
		const bool openRaceMenu();
	private:
		unsigned int oldScoreCounter[20], oldScore[20];
		unsigned int currentScore, programScore;
		unsigned int goalComplete;

		eInitMode initMode;
		eScoreMode scoreMode;
		StaticText* playerText;
		Button* currentActionButton;
//		Radio* menuRadio;
		Button* raceMenuButton;
		RaceMenu* raceMenu;
//		Button* removePlayerButton;
		StaticText* scoreText;
		StaticText* speedText;
		StaticText* goalsFulfilledText;
//		Button* addPlayerButton;
		bool optimizing;
		unsigned int number;

		signed int assignRace;
		bool raceMenuOpenedExternally;
};

inline const signed int PlayerEntry::getAssignedRace() const {
	return(assignRace);
}

inline const eScoreMode PlayerEntry::getScoreMode() const {
	return(scoreMode);
}

inline const eInitMode PlayerEntry::getInitMode() const {
	return(initMode);
}

#endif

#endif // _UI_PLAYERENTRY_HPP
