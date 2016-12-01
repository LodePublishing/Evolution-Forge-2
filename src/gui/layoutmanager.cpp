#include "layoutmanager.hpp"

#include "window.hpp"

LayoutManager::LayoutManager():
	layoutMap()
{
}

LayoutManager::~LayoutManager()
{
}

void LayoutManager::registerWindow(const Window* object)
{
	layoutMap.insert(std::pair<const boost::uuids::uuid, const Window*>(object->getWindowLayout()->getId(), object));
}

Point LayoutManager::getGlobalWindowPosition(const boost::shared_ptr<const WindowLayout> windowLayout, const Size& objectSize) const 
{
	const Window* horizontalWindow = NULL;
	const Window* verticalWindow = NULL;



	if(!windowLayout) {
		return Point();
	}

	if(windowLayout->getWindowLayoutHorizontalId() != boost::uuids::uuid()) {
		horizontalWindow = layoutMap.find(windowLayout->getWindowLayoutHorizontalId())->second;
	}

	if(windowLayout->getWindowLayoutVerticalId() != boost::uuids::uuid()) {
		verticalWindow = layoutMap.find(windowLayout->getWindowLayoutVerticalId())->second;
	}

	Sint16 x = windowLayout->getPosition().getX();
	Sint16 y = windowLayout->getPosition().getY();

	switch(windowLayout->getDockTypeHorizontal()) {
		case NO_DOCKTYPE:break;
		case ABSOLUTE_COORDINATE_DOCKTYPE:break;
		case DOCK_WITH_BEGINNING_BORDER_OF_DOCKTYPE:x = horizontalWindow->getRelativeClientRectLeftBound() - objectSize.getWidth();break;
		case DOCK_WITH_ENDING_BORDER_OF_DOCKTYPE:x = horizontalWindow->getRelativeClientRectRightBound();break;
		case DOCK_WITH_BEGINNING_INSIDE_OF_DOCKTYPE:x = horizontalWindow->getRelativeClientRectLeftBound();break;
		case DOCK_WITH_ENDING_INSIDE_OF_DOCKTYPE:x = horizontalWindow->getRelativeClientRectRightBound() - objectSize.getWidth();break;
		case DOCK_WITH_CENTER_INSIDE_OF_DOCKTYPE:x = horizontalWindow->getAbsoluteClientRectLeftBound() + (horizontalWindow->getClientRectWidth() - objectSize.getWidth())/2;break;
	}

	switch(windowLayout->getDockTypeVertical()) {
		case NO_DOCKTYPE:break;
		case ABSOLUTE_COORDINATE_DOCKTYPE:break;
		case DOCK_WITH_BEGINNING_BORDER_OF_DOCKTYPE:y = verticalWindow->getRelativeClientRectUpperBound() - objectSize.getHeight();break;
		case DOCK_WITH_ENDING_BORDER_OF_DOCKTYPE:y = verticalWindow->getRelativeClientRectLowerBound();break;
		case DOCK_WITH_BEGINNING_INSIDE_OF_DOCKTYPE:y = verticalWindow->getRelativeClientRectUpperBound();break;
		case DOCK_WITH_ENDING_INSIDE_OF_DOCKTYPE:y = verticalWindow->getRelativeClientRectLowerBound() - objectSize.getHeight();break;
		case DOCK_WITH_CENTER_INSIDE_OF_DOCKTYPE:y = verticalWindow->getAbsoluteClientRectUpperBound() + (horizontalWindow->getClientRectHeight() - objectSize.getHeight())/2;break;
	}

	return Point(x,y);
}