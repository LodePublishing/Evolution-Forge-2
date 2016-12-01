#ifndef _GEOMETRY_POSITIONOBJECT_HPP
#define _GEOMETRY_POSITIONOBJECT_HPP

#include "enums/autosize.hpp"
#include "enums/positionmode.hpp"
#include "enums/adjustmode.hpp"

#include "rect.hpp"

class PositionObject
{
	protected:
		PositionObject(const Rect& relative_rect = Rect(0, 0, 0, 0), 
				const Size& distance_bottom_right = Size(0, 0), 
				const ePositionMode position_mode = DO_NOT_ADJUST, 
				const eAutoSize auto_size = NOTHING);

		~PositionObject(); 
public:		
// ---- BEGIN POSITION/SIZE/MOVEMENT HANDLING ----
		const Point& getRelativePosition() const;	
		const Size& getSize() const;
		Sint16 getRelativeUpperBound() const;
		Sint16 getRelativeLowerBound() const;
		Sint16 getRelativeLeftBound() const;
		Sint16 getRelativeRightBound() const;
		Uint16 getHeight() const;
		Uint16 getWidth() const;
		const Rect& getRelativeRect() const;

		Uint16 getTargetWidth() const;
		Uint16 getTargetHeight() const;
		const Point getTargetPosition() const;
		const Rect& getTargetRect() const;

		void adjustRelativeRect(const Rect& rect);

		void setMoved();
		void resetMoved();
		bool wasMoved() const;
		
		const Point& getOriginalPosition() const;
		const Rect& getOriginalRect() const;
		const Size& getDistanceBottomRight() const;

		bool isMoving() const;
		
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

		static bool setSmoothMovements(const bool smooth);
		static bool isSmoothMovements();
// ---- END POSITION/SIZE/MOVEMENT HANDLING ----
		bool adjustSize(const PositionObject* parentObject, const eAdjustMode adjust_mode, const Size& size);
		void adjustPosition(const PositionObject* parentObject);

		void move(const PositionObject* parentObject);

	protected:
		static bool smoothMovements;
		Rect relativeRect; // every object needs a current position and size, position is >> RELATIVE << to parent!
		Rect startRect;
		Rect targetRect;
		Rect originalRect;
		Size distanceBottomRight;

		Rect oldRect;
		ePositionMode positionMode;
		
		eAutoSize autoSize;	

	private:

		bool moved;

		void setLeft(const Sint16 x);
		void setTop(const Sint16 y);
};

inline const Size& PositionObject::getDistanceBottomRight() const {
	return distanceBottomRight;
}

inline const Rect& PositionObject::getOriginalRect() const {
	return originalRect;
}

inline const Point& PositionObject::getOriginalPosition() const {
	return originalRect.getTopLeft();
}

inline void PositionObject::setOriginalPosition(const Point& position) {
	originalRect.setTopLeft(position);
	setPosition(position);
}

inline void PositionObject::setMoved() {
	moved = true;
}

inline void PositionObject::resetMoved() {
	moved = false;
}

inline bool PositionObject::wasMoved() const {
	return moved;
}

inline const Point& PositionObject::getRelativePosition() const {
	return relativeRect.getTopLeft();
}			
			
inline const Size& PositionObject::getSize() const {
	return relativeRect.getSize();
}
	
inline Sint16 PositionObject::getRelativeUpperBound() const {
	return relativeRect.getTop();
}
				
inline Sint16 PositionObject::getRelativeLowerBound() const {
	return relativeRect.getBottom();
}
	
inline Sint16 PositionObject::getRelativeLeftBound() const {
	return relativeRect.getLeft();
}
	
inline Sint16 PositionObject::getRelativeRightBound() const {
	return relativeRect.getRight();
}
	
inline Uint16 PositionObject::getHeight() const {
	return relativeRect.getHeight();
}
	
inline Uint16 PositionObject::getWidth() const {
	return relativeRect.getWidth();
}
	
inline const Rect& PositionObject::getRelativeRect() const {
	return relativeRect;
}

inline Uint16 PositionObject::getTargetWidth() const {
	return targetRect.getWidth();
}

inline Uint16 PositionObject::getTargetHeight() const {
	return targetRect.getHeight();
}

inline const Point PositionObject::getTargetPosition() const {
	return targetRect.getTopLeft();
}

inline const Rect& PositionObject::getTargetRect() const {
	return targetRect;
}

inline void PositionObject::setPosition(const Sint16 x, const Sint16 y) {
	setPosition(Point(x, y));
}

inline void PositionObject::setSize(const Uint16 width, const Uint16 height) {
	setSize(Size(width, height));
}


// -------- BEGIN COORDINATES --------

inline void PositionObject::setRect(const Rect& rect) 
{
	relativeRect = rect;
	startRect = rect;
	targetRect = rect;
}

inline void PositionObject::setPosition(const Point& position)
{
	if(position != relativeRect.getTopLeft()) {
		startRect.setTopLeft(position);
		targetRect.setTopLeft(position);
		relativeRect.setTopLeft(position);
	}
}

inline void PositionObject::setTargetPosition(const Sint16 x, const Sint16 y) {
	setTargetPosition(Point(x, y));
}

inline void PositionObject::setTargetLeft(const Sint16 x) {
	setTargetPosition(x, targetRect.getTop());
}

inline void PositionObject::setTargetTop(const Sint16 y) {
	setTargetPosition(targetRect.getLeft(), y);
}


inline void PositionObject::setHeight(const Uint16 height) 
{
	if(getTargetHeight() != height) {
		relativeRect.setHeight(height);
		startRect.setHeight(height);
		targetRect.setHeight(height);
	}
}

inline void PositionObject::setWidth(const Uint16 width) 
{
	if(relativeRect.getWidth() != width) {
		relativeRect.setWidth(width);
		startRect.setWidth(width);
		targetRect.setWidth(width);
	}
}

inline void PositionObject::setSize(const Size& size)
{
	if(relativeRect.getSize() != size) {
		relativeRect.setSize(size);
		startRect.setSize(size);
		targetRect.setSize(size);
	}
}

inline void PositionObject::setLeft(const Sint16 x) 
{
	if(relativeRect.getLeft() != x) {
		relativeRect.setLeft(x);
		startRect.setLeft(x);
		targetRect.setLeft(x);
	}
}
		
inline void PositionObject::setTop(const Sint16 y) 
{
	if(relativeRect.getTop() != y) {
		relativeRect.setTop(y);
		startRect.setTop(y);
		targetRect.setTop(y);
	}
}


inline void PositionObject::setOriginalRect(const Rect& rect) {
	originalRect = rect;
	setRect(rect);
}

inline void PositionObject::setOriginalSize(const Size& size) {
	originalRect.setSize(size);
	setSize(size);
}

inline void PositionObject::setOriginalWidth(const Uint16 width) {
	originalRect.setWidth(width);
	setWidth(width);
}

inline bool PositionObject::setSmoothMovements(const bool smooth) {
	if(smoothMovements == smooth) {
		return false;
	}
	smoothMovements = smooth;
	return true;
}

inline bool PositionObject::isSmoothMovements() {
	return smoothMovements;
}


// -------- END COORDINATES --------


#endif // _GEOMETRY_POSITIONOBJECT_HPP

