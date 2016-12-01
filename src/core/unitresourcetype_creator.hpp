#ifndef _CORE_STORAGES_UNITRESOURCETYPE_CREATOR_HPP
#define _CORE_STORAGES_UNITRESOURCETYPE_CREATOR_HPP

#include <misc/nodecreator.hpp>

class UnitResourceType;

class UnitResourceTypeCreator : public NodeCreator<UnitResourceType>
{ 
private:
	UnitResourceTypeCreator();
	~UnitResourceTypeCreator();

};

#endif // _CORE_STORAGES_UNITRESOURCETYPE_CREATOR_HPP