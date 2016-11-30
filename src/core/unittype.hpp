#ifndef _CORE_UNITTYPE_HPP
#define _CORE_UNITTYPE_HPP

#include <string>
#include <list>
#include <vector>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include "unitresourcetype.hpp"
#include "id.hpp"
#include "race.hpp"
#include "enums/unitmovementtypeenums.hpp"
//#include "UnitSizeType.hpp"
//#include "UnitContainerType.hpp"

class UnitType : public ID<UnitType>
{
public:

	UnitType(const std::string& unit_name, 
		const Race* race,
		const unsigned int buildTime,
		const unsigned int maxCount,		
		const bool corporeal,
		const eUnitMovementType movementType, 
		const unsigned int speed,
		const std::list<UnitResourceType>& resources);
	
//	const UnitSizeType& getSizeType() const;
//	const std::list<UnitContainerType>& getContainerTypes() const;


	~UnitType();

	const std::string& getName() const;
	unsigned int getBuildTime() const;
	unsigned int getRaceID() const;
	
	unsigned int getSpeed() const;
	eUnitMovementType getMovementType() const;
	bool isCorporeal() const;

	const std::list<UnitResourceType>& getResources() const;
	// evtl Map machen

// needs to be called after deserialization
	void setRace(const Race* race);
	const Race* getRace() const;
	unsigned int getMaxCount() const;

	static const char* const Name_tag_string;
	static const char* const Race_tag_string;
	static const char* const MaxCount_tag_string;
	static const char* const BuildTime_tag_string;
	static const char* const ResourceList_tag_string;

	static const char* const Corporeal_tag_string;
	static const char* const MovementType_tag_string;
	static const char* const Speed_tag_string;

	static const unsigned int MAX_COUNT;

	// public, in order to use for std::maps
	UnitType():race(NULL) {}

	
private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		ar & boost::serialization::make_nvp(Race_tag_string, raceID);
		ar & boost::serialization::make_nvp(BuildTime_tag_string, buildTime);
		ar & boost::serialization::make_nvp(MaxCount_tag_string, maxCount);
		ar & boost::serialization::make_nvp(ResourceList_tag_string, resources);

		ar & boost::serialization::make_nvp(Corporeal_tag_string, corporeal);
		ar & boost::serialization::make_nvp(MovementType_tag_string, movementType);
		ar & boost::serialization::make_nvp(Speed_tag_string, speed);	
		if(version > 0) {
		}
	}

	// mandatory fields
	std::string name;
	const Race* race;
	unsigned int raceID;
	unsigned int buildTime;
	// maximal number of units of this type a player can have
	unsigned int maxCount;
	bool corporeal;
	eUnitMovementType movementType;
	unsigned int speed;


//	UnitSizeType sizeType;
//	std::list<UnitContainerType> containerType;

/*	const unsigned int HP;
	const unsigned int XP;
	const unsigned int defense;
	const unsigned int damage;
	const unsigned int damageSpeed;
	const unsigned int attackModifierGlobalUnitID;
	const unsigned int defenseModifierGlobalUnitID;
// etc.*/
	// energy
	// last time energy-ability used (better than incrementing all units)


	std::list<UnitResourceType> resources;
	
	UnitType& operator=(const UnitType& other);
	
};

inline unsigned int UnitType::getBuildTime() const {
	return buildTime;
}

inline unsigned int UnitType::getMaxCount() const {
	return maxCount;
}

inline const std::string& UnitType::getName() const {
	return name;
}

inline const std::list<UnitResourceType>& UnitType::getResources() const {
	return resources;
}

inline const Race* UnitType::getRace() const {
	return race;
}

inline unsigned int UnitType::getRaceID() const {
	return raceID;
}

inline bool UnitType::isCorporeal() const {
	return corporeal;
}

inline unsigned int UnitType::getSpeed() const {
	return speed;
}

inline eUnitMovementType UnitType::getMovementType() const {
	return movementType;
}

/*
inline const UnitSizeType& UnitType::getSizeType() const {
	return sizeType;
}

inline const std::list<UnitContainerType>& UnitType::getContainerTypes() const {
	return containerType;
}*/

#endif
