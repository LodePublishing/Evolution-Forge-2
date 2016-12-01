#ifndef _SDL_OBJECT_HPP
#define _SDL_OBJECT_HPP

#include "dc.hpp"
#include <geometry/zrect.hpp>

#include "enums/autosize.hpp"
#include "enums/positionmode.hpp"
#include "enums/drawtype.hpp"
#include "enums/adjustmode.hpp"

#include <misc/uuid.hpp>
/*
usage:
derive objects from sdl_object
define the draw function
SDL_Object::processAll for movement
SDL_Object::updateAreasToUpdate to define updateable areas of the screen
SDL_Object::drawAll(dc) to draw the objects
*/

class SDL_Object;

class SDL_Object : public UUID<SDL_Object>
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
		bool isTopItem() const;

		const Point& getRelativePosition() const;
	
		const Size& getSize() const;
		Sint16 getRelativeUpperBound() const;
		Sint16 getRelativeLowerBound() const;
		Sint16 getRelativeLeftBound() const;
		Sint16 getRelativeRightBound() const;
		Uint16 getHeight() const;
		Uint16 getWidth() const;
		const Rect& getRelativeRect() const;
		const Point getParentAbsolutePosition() const;
		const Point getAbsolutePosition() const;
		const Rect getAbsoluteRect() const;
		Sint16 getAbsoluteUpperBound() const;
		Sint16 getAbsoluteLowerBound() const;
		Sint16 getAbsoluteLeftBound() const;
		Sint16 getAbsoluteRightBound() const;

		Uint16 getTargetWidth() const;
		Uint16 getTargetHeight() const;
		const Point getTargetPosition() const;
		const Rect& getTargetRect() const;

		void adjustRelativeRect(const Rect& rect);

		void makePufferInvalid();
		void makePufferValid();
		bool isPufferValid() const;

		void setMoved();
		void resetMoved();
		bool wasMoved() const;
		
		void Show(const bool show = true);
		void Hide(const bool hide = true);

		virtual void draw(DC* const dc) const;
		void redrawWholeObject();		

		void reloadOriginalSize();

		void process();
		void resetData();
		
		static unsigned int redrawnObjects;
		
		
		
		const Point& getOriginalPosition() const;
		const Rect& getOriginalRect() const;
		const Size& getDistanceBottomRight() const;
	

		bool isMoving() const;
		
		void adjustSize(const eAdjustMode adjust_mode, const Size& size = Size(0,0));
		void setOriginalPosition(const Point& position);
		void setPosition(const Point& position);
		void setPosition(const Sint16 x, const Sint16 y);
		void setTargetPosition(const Point& position);
		void setTargetPosition(const Sint16 x, const Sint16 y);
		// TODO setTargetSize
		void setTargetLeft(const Sint16 x);
		void setTargetTop(const Sint16 y);
		void setSize(const Size& size);
		void setRect(const Rect& rect);
		void setWidth(const Uint16 width);
		void setHeight(const Uint16 height);
		void setSize(const Uint16 width, const Uint16 height);

		void setOriginalSize(const Size& size);
		void setOriginalRect(const Rect& rect);
		void setOriginalWidth(const Uint16 width);

		void setParent(SDL_Object* const parent);
		void setPositionParent(SDL_Object* const parent);
		SDL_Object* getNextBrother() const;

		SDL_Object* checkHighlight(const Point& mouse);
		eDrawType getDrawType() const;
		void setDrawType(const eDrawType draw_type);

		signed int getZ() const;
		void setZ(const signed int zcoord);
		void makeFirstChild();	



		static void updateAreasToUpdate();
		static void drawAll(DC* dc);
		static void processAll();	

		static bool setSmoothMovements(const bool smooth);
		static bool isSmoothMovements();
		static void resetFocus();
		static void setFocus(const SDL_Object* const new_focus);
		static const SDL_Object* getFocus();
		static void setHighlighted(const SDL_Object* const new_highlighted);
		static const SDL_Object* getHighlighted();
		static void resetHighlighted();	


	protected:
		static bool smoothMovements;

		void addIfPufferInvalid();
		void checkForChildrenOverlap(const Rect& rect);


		SDL_Object* getPrevBrother() const;
		SDL_Object* getParent() const; // TODO make const correctness!
		SDL_Object* getPositionParent() const; // TODO make const correctness!
		SDL_Object* getChildren() const;


		void setChildrenWereChanged(const bool changed = true);
		bool wereChildrenChanged() const;

	private:


		static const SDL_Object* focus;	
		static const SDL_Object* highlighted;
		static void removeRootObject(SDL_Object* const object);

		void putOnScreen(DC* dc);
		// TODO , (*i)->getTransparentCornersSize());
		static void checkAreaVisibility(ZRect rect, const bool show);
		void checkHighestZ(std::list<ZRect>& old_rect_list, std::list<ZRect>& new_rect_list);

		SDL_Object* children; // pointer to the head of the linked list of children
		bool pufferValid;
		bool moved;
		SDL_Surface* drawPuffer;
		eDrawType drawType;
		bool childrenWereChanged;
		void removeFromFamily();

		void move();

		void setLeft(const Sint16 x);
		void setTop(const Sint16 y);

		void adjustPosition();
		Rect relativeRect; // every object needs a current position and size, position is >> RELATIVE << to parent!
		Rect startRect;
		Rect targetRect;
	
		Rect originalRect;
		Size distanceBottomRight;

		Rect oldRect;
		ePositionMode positionMode;

		void checkRectHasChanged();

		eAutoSize autoSize;

		signed int zCoordinate;

		bool shown;


		void addChild(SDL_Object* const child);
		SDL_Object* parent; // = NULL means that this is the screen (x=0/y=0)
		SDL_Object* positionParent; // = NULL means that this is the screen (x=0/y=0)
		SDL_Object* prevBrother;
		SDL_Object* nextBrother; 

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

inline bool SDL_Object::wereChildrenChanged() const {
	return childrenWereChanged;
}

inline void SDL_Object::setChildrenWereChanged(const bool changed) {
	childrenWereChanged = changed;
}

inline signed int SDL_Object::getZ() const {
	return zCoordinate;
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

inline const Size& SDL_Object::getDistanceBottomRight() const {
	return distanceBottomRight;
}

inline const Rect& SDL_Object::getOriginalRect() const {
	return originalRect;
}

inline const Point& SDL_Object::getOriginalPosition() const {
	return originalRect.getTopLeft();
}

inline void SDL_Object::setOriginalPosition(const Point& position) {
	originalRect.setTopLeft(position);
	setPosition(position);
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

inline void SDL_Object::setMoved() {
	moved = true;
}

inline void SDL_Object::resetMoved() {
	moved = false;
}

inline bool SDL_Object::wasMoved() const {
	return moved;
}

inline const Point& SDL_Object::getRelativePosition() const {
	return relativeRect.getTopLeft();
}			
			
inline const Size& SDL_Object::getSize() const {
	return relativeRect.getSize();
}
	
inline Sint16 SDL_Object::getRelativeUpperBound() const {
	return relativeRect.getTop();
}
				
inline Sint16 SDL_Object::getRelativeLowerBound() const {
	return relativeRect.getBottom();
}
	
inline Sint16 SDL_Object::getRelativeLeftBound() const {
	return relativeRect.getLeft();
}
	
inline Sint16 SDL_Object::getRelativeRightBound() const {
	return relativeRect.getRight();
}
	
inline Uint16 SDL_Object::getHeight() const {
	return relativeRect.getHeight();
}
	
inline Uint16 SDL_Object::getWidth() const {
	return relativeRect.getWidth();
}
	
inline const Rect& SDL_Object::getRelativeRect() const {
	return relativeRect;
}
	
inline const Point SDL_Object::getAbsolutePosition() const {
	if(positionParent) {
		return relativeRect.getTopLeft() + positionParent->getAbsolutePosition();
	} else {
		return relativeRect.getTopLeft();
	}
}
	
inline const Point SDL_Object::getParentAbsolutePosition() const	{
	if(positionParent) {
		return positionParent->getAbsolutePosition();
	} else { 
		return Point(0,0);
	}
}
		
inline const Rect SDL_Object::getAbsoluteRect() const {
	if(positionParent) {
		return Rect(relativeRect.getTopLeft() + positionParent->getAbsolutePosition(), getSize());
	} else {
		return relativeRect;
	}
}
		
inline Sint16 SDL_Object::getAbsoluteUpperBound() const {
	if(positionParent) {
		return relativeRect.getTop() + positionParent->getAbsoluteUpperBound();
	} else {
		return relativeRect.getTop();
	}
}
				
inline Sint16 SDL_Object::getAbsoluteLowerBound() const {
	if(positionParent) {
		return relativeRect.getBottom() + positionParent->getAbsoluteUpperBound();			
	} else {
		return relativeRect.getBottom();
	}
}
	
inline Sint16 SDL_Object::getAbsoluteLeftBound() const {
	if(positionParent) {
		return relativeRect.getLeft() + positionParent->getAbsoluteLeftBound();			
	} else {
		return relativeRect.getLeft();
	}
}
	
inline Sint16 SDL_Object::getAbsoluteRightBound() const {
	if(positionParent) {
		return relativeRect.getRight() + positionParent->getAbsoluteLeftBound();			
	} else {
		return relativeRect.getRight();
	}
}

inline SDL_Object* SDL_Object::getPrevBrother() const {
	return prevBrother;
}

inline SDL_Object* SDL_Object::getNextBrother() const {
	return nextBrother;
}

inline SDL_Object* SDL_Object::getParent() const {
	return parent;
}

inline SDL_Object* SDL_Object::getPositionParent() const {
	return positionParent;
}

inline SDL_Object* SDL_Object::getChildren() const {
	return children;
}

inline Uint16 SDL_Object::getTargetWidth() const {
	return targetRect.getWidth();
}

inline Uint16 SDL_Object::getTargetHeight() const {
	return targetRect.getHeight();
}

inline const Point SDL_Object::getTargetPosition() const {
	return targetRect.getTopLeft();
}

inline const Rect& SDL_Object::getTargetRect() const {
	return targetRect;
}

inline void SDL_Object::setPosition(const Sint16 x, const Sint16 y) {
	setPosition(Point(x, y));
}

inline void SDL_Object::setSize(const Uint16 width, const Uint16 height) {
	setSize(Size(width, height));
}


inline bool SDL_Object::isTopItem() const {
	return positionParent==NULL;
}


// -------- BEGIN COORDINATES --------

inline void SDL_Object::setRect(const Rect& rect) 
{
	relativeRect = rect;
	startRect = rect;
	targetRect = rect;
}

inline void SDL_Object::setPosition(const Point& position)
{
	if(position != relativeRect.getTopLeft()) {
		startRect.setTopLeft(position);
		targetRect.setTopLeft(position);
		relativeRect.setTopLeft(position);
	}
}

inline void SDL_Object::setTargetPosition(const Sint16 x, const Sint16 y) {
	setTargetPosition(Point(x, y));
}

inline void SDL_Object::setTargetLeft(const Sint16 x) {
	setTargetPosition(x, targetRect.getTop());
}

inline void SDL_Object::setTargetTop(const Sint16 y) {
	setTargetPosition(targetRect.getLeft(), y);
}


inline void SDL_Object::setHeight(const Uint16 height) 
{
	if(getTargetHeight() != height) {
		relativeRect.setHeight(height);
		startRect.setHeight(height);
		targetRect.setHeight(height);
	}
}

inline void SDL_Object::setWidth(const Uint16 width) 
{
	if(relativeRect.getWidth() != width) {
		relativeRect.setWidth(width);
		startRect.setWidth(width);
		targetRect.setWidth(width);
	}
}

inline void SDL_Object::setSize(const Size& size)
{
	if(relativeRect.getSize() != size) {
		relativeRect.setSize(size);
		startRect.setSize(size);
		targetRect.setSize(size);
	}
}

inline void SDL_Object::setLeft(const Sint16 x) 
{
	if(relativeRect.getLeft() != x) {
		relativeRect.setLeft(x);
		startRect.setLeft(x);
		targetRect.setLeft(x);
	}
}
		
inline void SDL_Object::setTop(const Sint16 y) 
{
	if(relativeRect.getTop() != y) {
		relativeRect.setTop(y);
		startRect.setTop(y);
		targetRect.setTop(y);
	}
}


inline void SDL_Object::setOriginalRect(const Rect& rect) {
	originalRect = rect;
	setRect(rect);
}

inline void SDL_Object::setOriginalSize(const Size& size) {
	originalRect.setSize(size);
	setSize(size);
}

inline void SDL_Object::setOriginalWidth(const Uint16 width) {
	originalRect.setWidth(width);
	setWidth(width);
}

inline bool SDL_Object::setSmoothMovements(const bool smooth) {
	if(smoothMovements == smooth) {
		return false;
	}
	smoothMovements = smooth;
	return true;
}

inline bool SDL_Object::isSmoothMovements() {
	return smoothMovements;
}


// -------- END COORDINATES --------

//extern unsigned int SDL_Object::redrawnObjects;
//extern bool SDL_Object::smoothMovements;
//extern SDL_Object* SDL_Object::focus;

//extern std::list<SDL_Object*> SDL_Object::rootObjectList;
//extern std::list<std::pair<signed int, Rect> > SDL_Object::newRectList;
//extern std::list<std::pair<signed int, Rect> > SDL_Object::oldRectList;

#endif // _SDL_OBJECT_HPP

