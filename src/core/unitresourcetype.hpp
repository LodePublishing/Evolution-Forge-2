#ifndef _CORE_UNITRESOURCETYPE_HPP
#define _CORE_UNITRESOURCETYPE_HPP

#include <list>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include <uuid.hpp>

#include "enums/unitresourcetypeenums.hpp"

class UnitResourceType
{
public:
	UnitResourceType(const eUnitResourceType resourceType, 
		const signed int amount,
		const std::list<std::list<boost::uuids::uuid> >& unitTypeIdList);
	~UnitResourceType() {}
	
	eUnitResourceType getResourceType() const;
	signed int getAmount() const;

	// returns the ID of the unit type that is needed (e.g. the supply resource, a facility unit type id etc.)
	// it is a list of list, all lists in the top list are ORed (makes only sense with prerequisites)
	const std::list<std::list<boost::uuids::uuid> >& getUnitTypeIDList() const;
	
	
private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const UnitResourceType* unitResourceType, const unsigned int version) { 

		const eUnitResourceType& resourceType = unitResourceType->getResourceType();
		const signed int& amount = unitResourceType->getAmount();
		const std::list<std::list<boost::uuids::uuid> >& unitTypeIdList = unitResourceType->getUnitTypeIDList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(resourceType)
		   & BOOST_SERIALIZATION_NVP(amount)
		   & BOOST_SERIALIZATION_NVP(unitTypeIdList);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, UnitResourceType*& unitResourceType, const unsigned int version)
	{
		eUnitResourceType resourceType;
		signed int amount;
		std::list<std::list<boost::uuids::uuid> > unitTypeIdList; // corresponding unit (for some types)

		ar & BOOST_SERIALIZATION_NVP(resourceType)
		   & BOOST_SERIALIZATION_NVP(amount)
		   & BOOST_SERIALIZATION_NVP(unitTypeIdList);
					
		if(version > 0) {
		}

		::new(unitResourceType)UnitResourceType(resourceType, amount, unitTypeIdList);
	}

	eUnitResourceType resourceType;
	signed int amount;
	std::list<std::list<boost::uuids::uuid> > unitTypeIdList; // corresponding unit (for some types)
};

inline eUnitResourceType UnitResourceType::getResourceType() const {
	return resourceType;
}

inline signed int UnitResourceType::getAmount() const {
	return amount;
}

inline const std::list<std::list<boost::uuids::uuid> >& UnitResourceType::getUnitTypeIDList() const {
	return unitTypeIdList;
}

#endif
