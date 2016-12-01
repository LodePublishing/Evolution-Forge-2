#ifndef _CORE_STORAGES_UNIT_CREATOR_HPP
#define _CORE_STORAGES_UNIT_CREATOR_HPP

#include <misc/nodecreator.hpp>

class Unit;

class UnitCreator : public NodeCreator<Unit>
{ 
private:
	UnitCreator();
	~UnitCreator();
};

#endif // _CORE_STORAGES_UNIT_CREATOR_HPP