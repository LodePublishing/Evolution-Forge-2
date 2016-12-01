#include "windowlayout.hpp"

WindowLayout::WindowLayout(const boost::uuids::uuid id, const Size& size, const Size& maxSize, const eDockType dockTypeHorizontal, const eDockType dockTypeVertical, const Point& point, const boost::uuids::uuid windowLayoutHorizontalId, const boost::uuids::uuid windowLayoutVerticalId):
	UUID<WindowLayout>(id),
	rect(point, size),
	maxSize(maxSize),
	dockTypeHorizontal(dockTypeHorizontal),
	dockTypeVertical(dockTypeVertical),
	windowLayoutHorizontalId(windowLayoutHorizontalId),
	windowLayoutVerticalId(windowLayoutVerticalId)
{ }

WindowLayout::WindowLayout(const Size& size, const Size& maxSize, const eDockType dockTypeHorizontal, const eDockType dockTypeVertical, const Point& point, const boost::uuids::uuid windowLayoutHorizontalId, const boost::uuids::uuid windowLayoutVerticalId):
	UUID<WindowLayout>(),
	rect(point, size),
	maxSize(maxSize),
	dockTypeHorizontal(dockTypeHorizontal),
	dockTypeVertical(dockTypeVertical),
	windowLayoutHorizontalId(windowLayoutHorizontalId),
	windowLayoutVerticalId(windowLayoutVerticalId)
{ }

WindowLayout::~WindowLayout()
{ }