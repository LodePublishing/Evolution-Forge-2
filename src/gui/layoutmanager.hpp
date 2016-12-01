#ifndef _GUI_LAYOUTMANAGER_HPP
#define _GUI_LAYOUTMANAGER_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#pragma warning(pop)

class Window;

#include <geometry/size.hpp>
#include <geometry/point.hpp>
#include <map>
#include <geometry/windowlayout.hpp>

class LayoutManager
{
public:
	LayoutManager();
	~LayoutManager();

	void registerWindow(const Window* object);

	Point getGlobalWindowPosition(const boost::shared_ptr<const WindowLayout> windowLayout, const Size& objectSize) const;

private:
	std::map<const boost::uuids::uuid, const Window*> layoutMap;
};

#endif // _GUI_LAYOUTMANAGER_HPP