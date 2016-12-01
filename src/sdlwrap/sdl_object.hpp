#ifndef _SDL_OBJECT_HPP
#define _SDL_OBJECT_HPP

#include "dc.hpp"
#include <geometry/positionobject.hpp>
#include <geometry/zrect.hpp>

#include "enums/drawtype.hpp"

#include <misc/uuid.hpp>
#include <misc/objectnode.hpp>
/*
usage:
derive objects from sdl_object
define the draw function
SDL_Object::processAll for movement
SDL_Object::updateAreasToUpdate to define updateable areas of the screen
SDL_Object::drawAll(dc) to draw the objects
*/

class SDL_Object;

class SDL_Object : public UUID<SDL_Object>, public PositionObject, public ObjectNode
{
protected:
	SDL_Object(SDL_Object* const parent_object, 
		const Rect& relative_rect = Rect(0, 0, 0, 0), 
		const Size& distance_bottom_right = Size(0, 0), 
		const ePositionMode position_mode = DO_NOT_ADJUST, 
		const eAutoSize auto_size = NOTHING);

	SDL_Object(const boost::uuids::uuid id, 
		SDL_Object* const parent_object, 
		const Rect& relative_rect = Rect(0, 0, 0, 0), 
		const Size& distance_bottom_right = Size(0, 0), 
		const ePositionMode position_mode = DO_NOT_ADJUST, 
		const eAutoSize auto_size = NOTHING);

	~SDL_Object(); 

public:

	bool isShown() const;

	void reloadOriginalSize();


	void makePufferInvalid();
	void makePufferValid();
	bool isPufferValid() const;

	void Show(const bool show = true);
	void Hide(const bool hide = true);

	virtual void draw(DC* const dc) const;
	void redrawWholeObject();		
	static void redrawAllRootObjects();

	void process();
	void resetData();

	const Point getAbsolutePosition() const;	
	const Point getParentAbsolutePosition() const;		
	const Rect getAbsoluteRect() const;		
	Sint16 getAbsoluteUpperBound() const;				
	Sint16 getAbsoluteLowerBound() const;	
	Sint16 getAbsoluteLeftBound() const;	
	Sint16 getAbsoluteRightBound() const;

	SDL_Object* checkHighlight(const Point& mouse);
	eDrawType getDrawType() const;
	void setDrawType(const eDrawType draw_type);		

	static void updateAreasToUpdate();
	static void drawAll(DC* dc);
	static void processAll();	
	static void processRects();

	static void resetFocus();
	static void setFocus(const SDL_Object* const new_focus);
	static const SDL_Object* getFocus();
	static void setHighlighted(const SDL_Object* const new_highlighted);
	static const SDL_Object* getHighlighted();
	static void resetHighlighted();	
		
	void setZ(const signed int zcoord);
	static void cutBorders(const Rect& screen);

protected:

	void addIfPufferInvalid();
	void checkForChildrenOverlap(const Rect& rect);

private:
	

	static const SDL_Object* focus;	
	static const SDL_Object* highlighted;
	static std::list<ZRect> oldRectList;
	static std::list<ZRect> newRectList;

	void putOnScreen(DC* dc);
	// TODO , (*i)->getTransparentCornersSize());
	
	static void addToPreviousRects(ZRect zrect);
	static void addToCurrentRects(ZRect zrect);
	void checkHighestZ(std::list<ZRect>& old_rect_list, std::list<ZRect>& new_rect_list);

	bool pufferValid;

	bool wasShown;
	bool wasHidden;
	
	SDL_Surface* drawPuffer;
	eDrawType drawType;		

	void checkRectHasChanged();		
	void reinitializeDrawPuffer(DC* const dc);
	void deleteDrawPuffer();
	void signalSizeChange();
	bool shown;
	
	//		SDL_Object& operator=(const SDL_Object& object);
	//		SDL_Object(const SDL_Object& object);
};

inline void SDL_Object::setFocus(const SDL_Object* const new_focus) {
	focus = new_focus;
}

inline void SDL_Object::resetFocus() {
	focus = NULL;
}

inline const SDL_Object* SDL_Object::getFocus() {
	return focus;
}

inline void SDL_Object::setHighlighted(const SDL_Object* const new_highlighted) {
	highlighted = new_highlighted;
}

inline void SDL_Object::resetHighlighted() {
	highlighted = NULL;
}

inline const SDL_Object* SDL_Object::getHighlighted() {
	return highlighted;
}

inline eDrawType SDL_Object::getDrawType() const {
	return drawType;
}

inline void SDL_Object::setDrawType(const eDrawType draw_type) {
	drawType = draw_type;
}

inline bool SDL_Object::isPufferValid() const {
	return pufferValid;
}

inline void SDL_Object::Hide(const bool hide) {
	Show(!hide);
}

inline bool SDL_Object::isShown() const {
	return shown;
}

inline void SDL_Object::makePufferValid() {
	pufferValid = true;
}


inline const Point SDL_Object::getAbsolutePosition() const {
	if(getPositionParent()) {
		return relativeRect.getTopLeft() + ((SDL_Object*)getPositionParent())->getAbsolutePosition();
	} else {
		return relativeRect.getTopLeft();
	}
}

inline const Point SDL_Object::getParentAbsolutePosition() const	{
	if(getPositionParent()) {
		return ((SDL_Object*)getPositionParent())->getAbsolutePosition();
	} else { 
		return Point(0,0);
	}
}

inline const Rect SDL_Object::getAbsoluteRect() const {
	if(getPositionParent()) {
		return Rect(relativeRect.getTopLeft() + ((SDL_Object*)getPositionParent())->getAbsolutePosition(), getSize());
	} else {
		return relativeRect;
	}
}

inline Sint16 SDL_Object::getAbsoluteUpperBound() const {
	if(getPositionParent()) {
		return relativeRect.getTop() + ((SDL_Object*)getPositionParent())->getAbsoluteUpperBound();
	} else {
		return relativeRect.getTop();
	}
}

inline Sint16 SDL_Object::getAbsoluteLowerBound() const {
	if(getPositionParent()) {
		return relativeRect.getBottom() + ((SDL_Object*)getPositionParent())->getAbsoluteUpperBound();			
	} else {
		return relativeRect.getBottom();
	}
}

inline Sint16 SDL_Object::getAbsoluteLeftBound() const {
	if(getPositionParent()) {
		return relativeRect.getLeft() + ((SDL_Object*)getPositionParent())->getAbsoluteLeftBound();			
	} else {
		return relativeRect.getLeft();
	}
}

inline Sint16 SDL_Object::getAbsoluteRightBound() const {
	if(getPositionParent()) {
		return relativeRect.getRight() + ((SDL_Object*)getPositionParent())->getAbsoluteLeftBound();			
	} else {
		return relativeRect.getRight();
	}
}





#endif // _SDL_OBJECT_HPP

