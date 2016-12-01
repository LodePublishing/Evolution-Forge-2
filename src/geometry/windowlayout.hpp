#ifndef _GEOMETRY_WINDOWLAYOUT_HPP
#define _GEOMETRY_WINDOWLAYOUT_HPP

#include "rect.hpp"
#include <misc/uuid.hpp>
#include "enums/docktype.hpp"

class WindowLayout : public UUID<WindowLayout>
{
public:
	WindowLayout(const boost::uuids::uuid id, const Size& size, const Size& maxSize, const eDockType dockTypeHorizontal = NO_DOCKTYPE, const eDockType dockTypeVertical = NO_DOCKTYPE, const Point& point = Point(), const boost::uuids::uuid windowLayoutHorizontalId = boost::uuids::nil_uuid(), const boost::uuids::uuid windowLayoutVerticalId = boost::uuids::nil_uuid());
	WindowLayout(const Size& size, const Size& maxSize, const eDockType dockTypeHorizontal = NO_DOCKTYPE, const eDockType dockTypeVertical = NO_DOCKTYPE, const Point& point = Point(), const boost::uuids::uuid windowLayoutHorizontalId = boost::uuids::nil_uuid(), const boost::uuids::uuid windowLayoutVerticalId = boost::uuids::nil_uuid());
	~WindowLayout();

	const Point& getPosition() const;
	const Size& getSize() const;
	const unsigned int getWidth() const;
	const unsigned int getHeight() const;

	const eDockType getDockTypeHorizontal() const;
	const eDockType getDockTypeVertical() const;
	
	const Size& getMaxSize() const;
	const unsigned int getMaxWidth() const;
	const unsigned int getMaxHeight() const;

	const boost::uuids::uuid getWindowLayoutHorizontalId() const;
	const boost::uuids::uuid getWindowLayoutVerticalId() const;

private:
	const Rect rect;
	const Size maxSize;

	const eDockType dockTypeHorizontal;
	const eDockType dockTypeVertical;

	const boost::uuids::uuid windowLayoutHorizontalId;
	const boost::uuids::uuid windowLayoutVerticalId;
};

inline const Point& WindowLayout::getPosition() const {
	return rect.getTopLeft();
}

inline const unsigned int WindowLayout::getWidth() const {
	return rect.getWidth();
}

inline const unsigned int WindowLayout::getHeight() const {
	return rect.getHeight();
}

inline const Size& WindowLayout::getSize() const {
	return rect.getSize();
}

inline const eDockType WindowLayout::getDockTypeHorizontal() const {
	return dockTypeHorizontal;
}

inline const eDockType WindowLayout::getDockTypeVertical() const {
	return dockTypeVertical;
}

inline const Size& WindowLayout::getMaxSize() const {
	return maxSize;
}

inline const unsigned int WindowLayout::getMaxWidth() const {
	return maxSize.getWidth();
}

inline const unsigned int WindowLayout::getMaxHeight() const {
	return maxSize.getHeight();
}

inline const boost::uuids::uuid WindowLayout::getWindowLayoutHorizontalId() const {
	return windowLayoutHorizontalId;
}

inline const boost::uuids::uuid WindowLayout::getWindowLayoutVerticalId() const {
	return windowLayoutVerticalId;
}

#endif // _GEOMETRY_WINDOWLAYOUT_HPP