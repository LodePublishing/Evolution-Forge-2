#ifndef _UI_MAINWINDOW_HPP
#define _UI_MAINWINDOW_HPP

#include <gui/window.hpp>

class MainWindow : public Window
{
	public:
		MainWindow();
		~MainWindow();
		void process();
		void draw( DC* dc ) const;
		void addNewGameTab();
		void removeGameTab(const unsigned int game_number);
		void setGizmo(const bool do_gizmo = true);
		void continueOptimizationAnimation(const bool running);
		
		const unsigned int getGameTabCount() const;

		void reloadStrings();
		void reloadOriginalSize();
	private:
		const Size helper(DC* const dc, Point point, const unsigned int dx, const int i, const std::string& str) const;
		Button* tab[MAX_TABS];
		unsigned int ani, ani2;
		bool gizmo;
		unsigned int gameTabCount;
		unsigned int gameNumber;
		unsigned int gameNumbers[MAX_TABS];
};

inline void MainWindow::setGizmo(const bool do_gizmo)
{
	gizmo = do_gizmo;
}

#endif // _UI_MAINWINDOW_HPP
