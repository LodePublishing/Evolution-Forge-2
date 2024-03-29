#ifndef _UI_SCORE_HPP
#define _UI_SCORE_HPP

#if 0

#include <gui/window.hpp>
#include "mapmenu.hpp"
#include "playerentry.hpp"

enum ePlayerOrder
{
	ADD_PLAYER,
	OPEN_RACE_MENU,
	RESTART_CALCULATION,
	OPEN_BO_MENU,
	OPEN_GOAL_MENU,
	OPEN_UNIT_MENU,
	SAVE_GOAL,
	SAVE_BUILD_ORDER,
	EDIT_FORCE_LIST
};

class ScoreWindow : public Window
{
	public:
		ScoreWindow(Object* score_parent, const unsigned int game_number, const unsigned int game_max);
		~ScoreWindow();

		void resetData();
		void resetPlayerTime(unsigned int player_number);
		void process();
		void draw() const;

		const eScoreMode getScoreMode(const unsigned int player_number) const;
		void setScoreMode(const unsigned int player_number, const eScoreMode score_mode);

		const eInitMode getInitMode(const unsigned int player_number) const;
		void setInitMode(const unsigned int player_number, const eInitMode init_mode);

		void setScore(const unsigned int player, const unsigned int score);
		void setGoalComplete(const unsigned int player, const unsigned int goal);
		void setPlayers(const unsigned int player_count);
		void setMaxPlayer(const unsigned int max_player);
		const unsigned int getPlayers() const;
		const bool isOptimizing(const unsigned int player_number) const;
		void startOptimizing(const unsigned int player_number);
		void stopOptimizing(const unsigned int player_number);
		const signed int getAssignedMap() const;

		void reloadOriginalSize();
		void setMode(const unsigned int game_number, const unsigned int game_max);

		const signed int getAssignedRace(const unsigned int player_number) const;

		void setUnchangedGenerations(const unsigned int unchanged_generations);

		const bool openMenu(const ePlayerOrder order);
		unsigned int currentPlayer;
	private:
		PlayerEntry* player[MAX_PLAYER];
		unsigned int players;
		unsigned int maxPlayer;

		unsigned int unchangedGenerations;

		void closeMenus();
//		Button* mapMenuButton;
//		MapMenu* mapMenu;		
		signed int assignMap;

		unsigned int gameNumber;
		unsigned int gameMax;

};

//inline const bool ScoreWindow::isOptimizing() const {
//	return optimizing;
//}

inline void ScoreWindow::setScore(const unsigned int player_number, const unsigned int score) 
{
#ifdef _SCC_DEBUG       
	if(player_number >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::setScore): Value player_number out of range.");return;
	}
#endif
	player[player_number]->setScore(score);
}

inline void ScoreWindow::setGoalComplete(const unsigned int player_number, const unsigned int goal) {
#ifdef _SCC_DEBUG       
	if(player_number >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::setGoalComplete): Value player_number out of range.");return;
	}
#endif
	player[player_number]->setGoalComplete(goal);
}

inline void ScoreWindow::setPlayers(const unsigned int player_count) {
#ifdef _SCC_DEBUG       
	if(player_count >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::setPlayers): Value player_count out of range.");return;
	}
#endif
	players = player_count;
}

inline const unsigned int ScoreWindow::getPlayers() const {
	return(players);
}

inline const signed int ScoreWindow::getAssignedMap() const {
	return(assignMap);
}

inline const bool ScoreWindow::isOptimizing(const unsigned int player_number) const
{
#ifdef _SCC_DEBUG       
        if(player_number >= maxPlayer) {
                toErrorLog("DEBUG: (ScoreWindow::isOptimizing): Value player_number out of range.");return(false);
        }
#endif
	return(player[player_number]->isOptimizing());
}

inline void ScoreWindow::setMaxPlayer(const unsigned int max_player)
{
#ifdef _SCC_DEBUG       
	if(max_player > MAX_PLAYER) {
		toErrorLog("DEBUG: (ScoreWindow::setMaxPlayer): Value max_player out of range.");return;
	}
#endif
	maxPlayer = max_player;
}

inline void ScoreWindow::setScoreMode(const unsigned int player_number, eScoreMode score_mode) // for different tabs different behaviour
{
#ifdef _SCC_DEBUG       
	if(player_number >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::setScoreMode): Value player_number out of range.");return;
	}
#endif
	player[player_number]->setScoreMode(score_mode);
}

inline const eScoreMode ScoreWindow::getScoreMode(const unsigned int player_number) const
{
#ifdef _SCC_DEBUG       
	if(player_number >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::getScoreMode): Value player_number out of range.");return(SCORE_FULFILL_MODE);
	}
#endif
	return(player[player_number]->getScoreMode());
}

inline void ScoreWindow::setInitMode(const unsigned int player_number, eInitMode init_mode) // for different tabs different behaviour
{
#ifdef _SCC_DEBUG
	if(player_number >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::setInitMode): Value player_number out of range.");return;
	}
#endif
	player[player_number]->setInitMode(init_mode);
}

inline const eInitMode ScoreWindow::getInitMode(const unsigned int player_number) const
{
#ifdef _SCC_DEBUG       
	if(player_number >= maxPlayer) {
		toErrorLog("DEBUG: (ScoreWindow::getInitMode): Value player_number out of range.");return(INACTIVE);
	}
#endif
	return(player[player_number]->getInitMode());
}

inline const signed int ScoreWindow::getAssignedRace(const unsigned int player_number) const
{
#ifdef _SCC_DEBUG       
        if(player_number >= maxPlayer) {
                toErrorLog("DEBUG: (ScoreWindow::getAssignedRace): Value player_number out of range.");return(-1);
        }
#endif
	return(player[player_number]->getAssignedRace());
}


#endif

#endif // _UI_SCORE_HPP