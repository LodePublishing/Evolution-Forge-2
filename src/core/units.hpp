#ifndef _CORE_UNITS_HPP
#define _CORE_UNITS_HPP

#include <map>

#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

#include "unit.hpp"
/**
* Indexed container of a set of units
*/

class Units
{
public:
	Units();
	~Units();

	unsigned int getGlobalNeutralAvailable(const unsigned int key) const;
	unsigned int getGlobalNeutralTotal(const unsigned int key) const;
	unsigned int getGlobalAvailable(const UnitGlobalKey& key) const;
	unsigned int getGlobalTotal(const UnitGlobalKey& key) const;
	unsigned int getLocalAvailable(const UnitLocalKey& key) const;
	unsigned int getLocalTotal(const UnitLocalKey& key) const;
	unsigned int getLocalNeutralAvailable(const UnitLocalNeutralKey& key) const;
	unsigned int getLocalNeutralTotal(const UnitLocalNeutralKey& key) const;

	const std::list<Unit*>& getUnitList() const;

	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);
	void clear();
	void calculateAvailableAndTotal();
	void process();

	
	void addLocalUnit(Unit* unit);
	void removeLocalUnit(Unit* unit);

	void addOneGlobalNeutralAvailable(const unsigned int key);
	void removeOneGlobalNeutralAvailable(const unsigned int key);
	void addOneGlobalAvailable(const UnitGlobalKey& key);
	void removeOneGlobalAvailable(const UnitGlobalKey& key);
	void addOneLocalAvailable(const UnitLocalKey& key);
	void removeOneLocalAvailable(const UnitLocalKey& key);
	void addOneLocalNeutralAvailable(const UnitLocalNeutralKey& key);
	void removeOneLocalNeutralAvailable(const UnitLocalNeutralKey& key);
		
	static const char* const UnitList_tag_string;

//	void setParent(Units* parent);

	Units(const Units& object);
	
	Units& operator=(const Units& object);

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(UnitList_tag_string, unitList);
		if(version > 0) {
		}
	}
	

	std::list<Unit*> unitList;
	

	// if not NULL this unit is for example part of a LOCATION, i.e. all changes in unit count has
//	Units* parent;

	// temporary variables (cache etc.)

	// unitID -> Unit map (unique! NOT unitTypeID!)
	std::map<unsigned int, Unit*> unitListMap;

	std::map<unsigned int, unsigned int> globalNeutralAvailable; // unitTypeID -> amount
	std::map<unsigned int, unsigned int> globalNeutralTotal; // unitTypeID -> amount
	std::map<UnitGlobalKey, unsigned int> globalAvailable; // playerID -> unitTypeID -> amount
	std::map<UnitGlobalKey, unsigned int> globalTotal; // playerID -> unitTypeID -> amount
	std::map<UnitLocalKey, unsigned int> localAvailable; // locationID -> playerID -> unitTypeID -> amount
	std::map<UnitLocalKey, unsigned int> localTotal; // locationID -> playerID -> unitTypeID -> amount
	std::map<UnitLocalNeutralKey, unsigned int> localNeutralAvailable; // locationID -> unitTypeID -> amount
	std::map<UnitLocalNeutralKey, unsigned int> localNeutralTotal; // locationID -> unitTypeID -> amount

	// these need to be private, no other class has a business administrating the total values!
	void addOneGlobalNeutralTotal(const unsigned int key);
	void removeOneGlobalNeutralTotal(const unsigned int key);
	void addOneGlobalTotal(const UnitGlobalKey& key);
	void removeOneGlobalTotal(const UnitGlobalKey& key);
	void addOneLocalTotal(const UnitLocalKey& key);
	void removeOneLocalTotal(const UnitLocalKey& key);	
	void addOneLocalNeutralTotal(const UnitLocalNeutralKey& key);
	void removeOneLocalNeutralTotal(const UnitLocalNeutralKey& key);	
};

inline const std::list<Unit*>& Units::getUnitList() const {
	return unitList;
}

/*inline void Units::setParent(Units* parent) {
	this->parent = parent;
}*/

// TODO selber Name für local/global, überladen über parameter

inline unsigned int Units::getLocalAvailable(const UnitLocalKey& key) const {
	if(localAvailable.find(key) == localAvailable.end()) {
		return 0;
	}
	return localAvailable.find(key)->second;
}

inline unsigned int Units::getLocalTotal(const UnitLocalKey& key) const {
	if(localTotal.find(key) == localTotal.end()) {
		return 0;
	}
	return localTotal.find(key)->second;
}

inline unsigned int Units::getLocalNeutralAvailable(const UnitLocalNeutralKey& key) const {
	if(localNeutralAvailable.find(key) == localNeutralAvailable.end()) {
		return 0;
	}
	return localNeutralAvailable.find(key)->second;
}

inline unsigned int Units::getLocalNeutralTotal(const UnitLocalNeutralKey& key) const {
	if(localNeutralTotal.find(key) == localNeutralTotal.end()) {
		return 0;
	}
	return localNeutralTotal.find(key)->second;
}

inline unsigned int Units::getGlobalAvailable(const UnitGlobalKey& key) const {
	if(globalAvailable.find(key) == globalAvailable.end()) {
		return 0;
	}
	return globalAvailable.find(key)->second;
}

inline unsigned int Units::getGlobalTotal(const UnitGlobalKey& key) const {
	if(globalTotal.find(key) == globalTotal.end()) {
		return 0;
	}
	return globalTotal.find(key)->second;
}

// adding and removing units globally should ONLY be done on global (noncorporeal) units! TODO
// no corresponding local units are updated! they need to be called from the outside

inline void Units::addOneGlobalAvailable(const UnitGlobalKey& key)
{
	++globalAvailable[key];
}

inline void Units::removeOneGlobalAvailable(const UnitGlobalKey& key)
{
	BOOST_ASSERT(globalAvailable[key] > 0);

	--globalAvailable[key];
}

inline void Units::addOneGlobalTotal(const UnitGlobalKey& key)
{
	++globalTotal[key];
}

inline void Units::removeOneGlobalTotal(const UnitGlobalKey& key)
{
	BOOST_ASSERT(globalTotal[key] > 0);

	--globalTotal[key];
}


inline void Units::addOneLocalAvailable(const UnitLocalKey& key)
{
	++localAvailable[key];

	addOneGlobalAvailable(UnitGlobalKey(key.playerID, key.unitTypeID));
}

inline void Units::removeOneLocalAvailable(const UnitLocalKey& key)
{
	BOOST_ASSERT(localAvailable[key] > 0);

	--localAvailable[key];

	removeOneGlobalAvailable(UnitGlobalKey(key.playerID, key.unitTypeID));
}

inline void Units::addOneLocalTotal(const UnitLocalKey& key)
{
	++localTotal[key];

	addOneGlobalTotal(UnitGlobalKey(key.playerID, key.unitTypeID));
}

inline void Units::removeOneLocalTotal(const UnitLocalKey& key)
{
	BOOST_ASSERT(localTotal[key] > 0);

	--localTotal[key];

	removeOneGlobalTotal(UnitGlobalKey(key.playerID, key.unitTypeID));
}


// remember: there are no global neutral units!
inline void Units::addOneLocalNeutralAvailable(const UnitLocalNeutralKey& key)
{
	++localNeutralAvailable[key];
}

inline void Units::removeOneLocalNeutralAvailable(const UnitLocalNeutralKey& key)
{
	BOOST_ASSERT(localNeutralAvailable[key] > 0);

	--localNeutralAvailable[key];
}

inline void Units::addOneLocalNeutralTotal(const UnitLocalNeutralKey& key)
{
	++localNeutralTotal[key];
}

inline void Units::removeOneLocalNeutralTotal(const UnitLocalNeutralKey& key)
{
	BOOST_ASSERT(localNeutralTotal[key] > 0);

	--localNeutralTotal[key];
}


#endif // _CORE_UNITS_HPP

