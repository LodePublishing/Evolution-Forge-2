#include "positionobject.hpp"

#include <misc/log.hpp>

#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)


PositionObject::PositionObject(const Rect& relative_rect, const Size& distance_bottom_right, const ePositionMode position_mode, const eAutoSize auto_size) :
	positionMode(position_mode),
	relativeRect(relative_rect),
	startRect(relative_rect),
	targetRect(relative_rect),
	originalRect(relative_rect),
	distanceBottomRight(distance_bottom_right),
	oldRect(relative_rect),

	autoSize(auto_size),
	moved(false)
{ }

PositionObject::~PositionObject()
{ }



void PositionObject::adjustRelativeRect(const Rect& rect)
{
	if(rect != targetRect)
	{
		if(rect.getTopLeft() != targetRect.getTopLeft()) {
			startRect.setTopLeft(getRelativePosition());
		}
		if(rect.getSize() != targetRect.getSize()) {
			startRect.setSize(getSize());
		}
		targetRect = rect;
	}
}


bool PositionObject::isMoving() const
{
	return relativeRect.getLeft() != targetRect.getLeft();
}

void PositionObject::setTargetPosition(const Point &position) {
	targetRect.setTopLeft(position);
	Sint16 x = getRelativePosition().getX();
	Sint16 y = getRelativePosition().getY();

	if(!((x >= startRect.getLeft() && x <= targetRect.getLeft()) || (x <= startRect.getLeft() && x >= targetRect.getLeft()) )) {
		startRect.setLeft(x);
	}
	if(!((y >= startRect.getTop() && y <= targetRect.getTop()) || (y <= startRect.getTop() && y >= targetRect.getTop()) )) {
		startRect.setTop(y);
	}
}

// TODO alle Aufrufe von adjustSize geben getSize() als Parameter durch...
bool PositionObject::adjustSize(const PositionObject* parentObject, const eAdjustMode adjust_mode, const Size& size)
{
	if(autoSize == NOTHING) {
		return false;
	}

	Sint16 left = originalRect.getLeft();
	Uint16 full_width;
	if(parentObject != NULL)
	{
		if(left + distanceBottomRight.getWidth() > parentObject->getWidth()) {
			full_width = 0;
		} else {
			full_width = parentObject->getWidth() - left - distanceBottomRight.getWidth();
		}
	} 
	else {
		full_width = getWidth();
	}

	if(adjust_mode == PARENT_WAS_CHANGED)
	{
		// called by PARENT after PARENT's size was changed
		switch(autoSize)
		{
		case NOTHING:break;
		case NO_AUTO_SIZE:break;
		case AUTO_SIZE:break;
		case AUTO_HEIGHT_FULL_WIDTH:
		case AUTO_DOUBLE_HEIGHT_FULL_WIDTH:
		case FULL_WIDTH:setWidth(full_width);break;
		case AUTO_HEIGHT_CONST_WIDTH:break;
		case AUTO_DOUBLE_HEIGHT_CONST_WIDTH:break;
		case CONST_SIZE:break;
		default:break; // TODO ERROR
		}
	} else
		if(adjust_mode == CHILD_WAS_CHANGED)
		{
			// called if the object is dependant on the child's size (e.g. Button - StaticText)
			// TODO maybe update other children too
			switch(autoSize)
			{
			case NOTHING:return false;break;
			case NO_AUTO_SIZE:setSize(originalRect.getSize());break;
			case AUTO_SIZE:setSize(size+Size(6, 0));break;
			case AUTO_HEIGHT_FULL_WIDTH:setSize(Size(full_width, size.getHeight()));break;
			case AUTO_DOUBLE_HEIGHT_FULL_WIDTH:setSize(Size(full_width, 2*size.getHeight()));break;
			case FULL_WIDTH:setSize(Size(full_width, getHeight()));break;
			case AUTO_HEIGHT_CONST_WIDTH:setSize(Size(originalRect.getWidth(), size.getHeight()));break;
			case AUTO_DOUBLE_HEIGHT_CONST_WIDTH:setSize(Size(originalRect.getWidth(), 2*size.getHeight()));break;
			case CONST_SIZE:setSize(Size(originalRect.getWidth(), originalRect.getHeight()));break;
			default:break; // TODO ERROR
			}
			return true;
		}
		return false;
}

void PositionObject::adjustPosition(const PositionObject* parentObject)
{
	if(positionMode == DO_NOT_ADJUST) {
		return;
	}

	Sint16 left = originalRect.getLeft() + distanceBottomRight.getWidth();
	Sint16 top = originalRect.getTop() + distanceBottomRight.getHeight();
	Uint16 full_width;
	Uint16 full_height;
	if(parentObject != NULL)
	{
		full_width = parentObject->getWidth() - left;
		full_height = parentObject->getHeight() - top;
	} 
	else
	{
		full_width = getWidth();
		full_height = getHeight();
	}

	Sint16 hor_center = left + ((Sint16)full_width - (Sint16)getWidth())/2;
	Sint16 right = (Sint16)full_width - left - (Sint16)getWidth();

	Sint16 ver_center = top + ((Sint16)full_height - (Sint16)getHeight())/2;
	if(ver_center < top) {
		ver_center = top;
	}
	Sint16 bottom = (Sint16)full_height - top - (Sint16)getHeight();

	switch(positionMode)
	{
	case DO_NOT_ADJUST:break;
	case TOTAL_CENTERED:setTargetPosition(hor_center, ver_center);break;
	case HORIZONTALLY_CENTERED:setTargetLeft(hor_center);break;
	case VERTICALLY_CENTERED:setTargetTop(ver_center);break;
	case TOP_LEFT:setTargetPosition(left, top);break;
	case TOP_CENTER:setTargetPosition(hor_center, top);break;
	case TOP_RIGHT:setTargetPosition(right, top);break;
	case CENTER_RIGHT:setTargetPosition(right, ver_center);break;
	case BOTTOM_RIGHT:setTargetPosition(right, bottom);break;
	case BOTTOM_CENTER:setTargetPosition(hor_center, bottom);break;
	case BOTTOM_LEFT:setTargetPosition(left, bottom);break;
	case CENTER_LEFT:setTargetPosition(left, ver_center);break;

	case SPECIAL_BUTTON_LEFT:break; // TODO!
	default:break;
	}
}

void PositionObject::move(const PositionObject* parentObject) {

	if(PositionObject::smoothMovements) {
		relativeRect.moveSmooth(startRect, targetRect);

		if(relativeRect.getTopLeft() == targetRect.getTopLeft()) {
			startRect.setTopLeft(relativeRect.getTopLeft());
		}
		if(relativeRect.getSize() == targetRect.getSize()) {
			startRect.setSize(relativeRect.getSize());
		}
	} else {
		relativeRect = targetRect;
		startRect = relativeRect;
	}

}




bool PositionObject::smoothMovements = false;