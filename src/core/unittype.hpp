#ifndef _CORE_UNITTYPE_HPP
#define _CORE_UNITTYPE_HPP

#include <string>
#include <list>
#include <vector>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include "unitresourcetype.hpp"
#include "id.hpp"
#include "race.hpp"
#include "enums/unitmovementtypeenums.hpp"

#include "globalstorage.hpp"

class UnitType : public ID<UnitType>
{
public:

	UnitType(const unsigned int id,
		const std::string& name, 
		const boost::shared_ptr<const Race> race,
		const unsigned int buildTime,
		const unsigned int maxCount,		
		const bool corporeal,
		const eUnitMovementType movementType, 
		const unsigned int speed,
		const std::list<UnitResourceType>& resources);

	UnitType(const std::string& name, 
		const boost::shared_ptr<const Race> race,
		const unsigned int buildTime,
		const unsigned int maxCount,		
		const bool corporeal,
		const eUnitMovementType movementType, 
		const unsigned int speed,
		const std::list<UnitResourceType>& resources);
	
	~UnitType();

	const std::string& getName() const;
	unsigned int getBuildTime() const;
	unsigned int getRaceId() const;	
	unsigned int getSpeed() const;
	eUnitMovementType getMovementType() const;
	bool isCorporeal() const;

	const std::list<UnitResourceType>& getResources() const;	// TODO evtl Map machen

	const boost::shared_ptr<const Race> getRace() const;
	unsigned int getMaxCount() const;

	static const unsigned int MAX_COUNT;
	
private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const UnitType* unitType, const unsigned int version) { 

		const unsigned int& id = unitType->getId();
		const std::string& name = unitType->getName();
		const unsigned int& raceId = unitType->getRaceId();
		const unsigned int& buildTime = unitType->getBuildTime();
		const unsigned int& maxCount = unitType->getMaxCount();
		const bool& corporeal = unitType->isCorporeal();
		const eUnitMovementType& movementType = unitType->getMovementType();
		const unsigned int& speed = unitType->getSpeed();
		const std::list<UnitResourceType>& resources = unitType->getResources();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(raceId)
		   & BOOST_SERIALIZATION_NVP(buildTime)
		   & BOOST_SERIALIZATION_NVP(maxCount)
		   & BOOST_SERIALIZATION_NVP(corporeal)
		   & BOOST_SERIALIZATION_NVP(movementType)
		   & BOOST_SERIALIZATION_NVP(speed)
		   & BOOST_SERIALIZATION_NVP(resources);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, UnitType*& unitType, const unsigned int version)
	{
		unsigned int id;
		std::string name;
		unsigned int raceId;
		unsigned int buildTime;
		unsigned int maxCount;
		bool corporeal;
		eUnitMovementType movementType;
		unsigned int speed;
		std::list<UnitResourceType> resources;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(raceId)
		   & BOOST_SERIALIZATION_NVP(buildTime)
		   & BOOST_SERIALIZATION_NVP(maxCount)
		   & BOOST_SERIALIZATION_NVP(corporeal)
		   & BOOST_SERIALIZATION_NVP(movementType)
		   & BOOST_SERIALIZATION_NVP(speed)
		   & BOOST_SERIALIZATION_NVP(resources);

		if(version > 0) {
		}

		::new(unitType)UnitType(id, name, GLOBAL_STORAGE.getRace(raceId), buildTime, maxCount, corporeal, movementType, speed, resources);
	}

	// mandatory fields
	const std::string name;
	const boost::shared_ptr<const Race> race;
	const unsigned int raceId;
	const unsigned int buildTime;
	// maximal number of units of this type a player can have
	const unsigned int maxCount;
	const bool corporeal;
	const eUnitMovementType movementType;
	const unsigned int speed;
	const std::list<UnitResourceType> resources;
	
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

inline const boost::shared_ptr<const Race> UnitType::getRace() const {
	return race;
}

inline unsigned int UnitType::getRaceId() const {
	return raceId;
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

#endif
