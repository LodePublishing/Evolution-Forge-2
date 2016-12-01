#ifndef _GUI_GUIPROCESSOR_HPP
#define _GUI_GUIPROCESSOR_HPP

#include "tooltip.hpp"
#include "window.hpp"
#include <geometry/rect.hpp>
#include <sdlwrap/sdl_object.hpp>
#include <guicore/cursor.hpp>

class GuiProcessor
{
public:
	GuiProcessor();
	~GuiProcessor();
		void process(DC* dc);
		bool isMouseInside(const Rect& rect) const;
		void setMouse(const Point& p, SDL_Object* root_object, const bool showTooltip, const Size& windowSize);
		const Point& getMouse() const;

		void leftDown(const Point& mouse, SDL_Object* root_object);
		void leftUp(const Point& mouse, SDL_Object* root_object);
		void rightDown(const Point& mouse, SDL_Object* root_object);
		void rightUp(const Point& mouse, SDL_Object* root_object);

		void wheelUp();
		void wheelDown();
		void wheelToTop();
		void wheelToBottom();

		bool isWindowSelected() const;
		Window* getCurrentWindow() const; 
		void setWindowSelected(const bool selected = true);
		void setCurrentWindow(Window* window);
		void resetWindow();

		void setToolTip(ToolTip* tooltip);
		ToolTip* getToolTip() const;
		void setToolTipParent(const Object* parent);
		const Object* getToolTipParent() const;
		
		void resetCursor();
		void setCursor(Cursor* cursor);

private:
		ToolTip* tooltip;
		const Object* toolTipParent;
		Window* currentWindow;
		bool windowSelected;
		// TODO currentButton
		unsigned int mouseType;
		Point mouse;
		SDL_Cursor* defaultCursor;
};



// ----- ACTIVE PARTS (mouse, tooltip, selected window etc. -----

inline void GuiProcessor::setToolTip(ToolTip* tooltip) {
	this->tooltip = tooltip;
}

inline ToolTip* GuiProcessor::getToolTip() const {
	return this->tooltip;
}

inline void GuiProcessor::setToolTipParent(const Object* parent) {
	this->toolTipParent = parent;
}

inline const Object* GuiProcessor::getToolTipParent() const {
	return toolTipParent;
}

inline bool GuiProcessor::isWindowSelected() const {
	return this->windowSelected;
}

inline Window* GuiProcessor::getCurrentWindow() const {
	return this->currentWindow;
}

inline void GuiProcessor::setWindowSelected(const bool selected) {
	windowSelected = selected;
}

inline void GuiProcessor::setCurrentWindow(Window* window) {
	currentWindow = window;
}

inline const Point& GuiProcessor::getMouse() const {
	return mouse;
}

inline bool GuiProcessor::isMouseInside(const Rect& rect) const {
	return rect.isTopLeftCornerInside(mouse);
}

// ----- ACTIVE PARTS (mouse, tooltip, selected window etc. END -----

#endif // _GUI_GUIPROCESSOR_HPP