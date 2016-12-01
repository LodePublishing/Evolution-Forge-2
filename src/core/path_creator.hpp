#ifndef _CORE_STORAGES_PATH_CREATOR_HPP
#define _CORE_STORAGES_PATH_CREATOR_HPP

#include <misc/nodecreator.hpp>

class Path;

class PathCreator : public NodeCreator<Path>
{ 
private:
	PathCreator();
	~PathCreator();
};

#endif // _CORE_STORAGES_PATH_CREATOR_HPP