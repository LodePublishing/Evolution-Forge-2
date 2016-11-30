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

class Units : public boost::enable_shared_from_this<Units>
{
public:
	Units();
	Units(const std::list<boost::shared_ptr<Unit> > unitList); // TODO
	~Units();
	void clear();

	unsigned int getGlobalNeutralAvailable(const boost::uuids::uuid key) const;
	unsigned int getGlobalNeutralTotal(const boost::uuids::uuid key) const;
	unsigned int getGlobalAvailable(const UnitGlobalKey& key) const;
	unsigned int getGlobalTotal(const UnitGlobalKey& key) const;
	unsigned int getLocalAvailable(const UnitLocalKey& key) const;
	unsigned int getLocalTotal(const UnitLocalKey& key) const;
	unsigned int getLocalNeutralAvailable(const UnitLocalNeutralKey& key) const;
	unsigned int getLocalNeutralTotal(const UnitLocalNeutralKey& key) const;
	
	bool unitExists(const boost::shared_ptr<Unit> unit) const;

	const std::list<boost::shared_ptr<Unit> >& getUnitList() const;
	const boost::shared_ptr<Unit>& getUnit(const boost::uuids::uuid unitId) const;

	void addUnit(const boost::shared_ptr<Unit> unit);
	void addUnits(const std::list<boost::shared_ptr<Unit> > unitList);
	void removeUnit(const boost::shared_ptr<Unit> unit);
	
	void addLocalUnit(const boost::shared_ptr<Unit> unit);
	void removeLocalUnit(const boost::shared_ptr<Unit> unit);

	//void addOneGlobalNeutralAvailable(const boost::uuids::uuid key); // TODO make private?
	//void removeOneGlobalNeutralAvailable(const boost::uuids::uuid key); needed?
	void addOneGlobalAvailable(const UnitGlobalKey& key);
	void removeOneGlobalAvailable(const UnitGlobalKey& key);
	void addOneLocalAvailable(const UnitLocalKey& key);
	void removeOneLocalAvailable(const UnitLocalKey& key);
	void addOneLocalNeutralAvailable(const UnitLocalNeutralKey& key);
	void removeOneLocalNeutralAvailable(const UnitLocalNeutralKey& key);

	void process();
			
	Units(const Units& object);	
	Units& operator=(const Units& object);

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{ }	

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Units* units, const unsigned int version) { 

		const std::list<boost::shared_ptr<Unit> >&  unitList = units->getUnitList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(unitList);
	}

	template<class Archive>
	inline friend void load_construct_data(Archive& ar, Units* units, const unsigned int version)
	{
		std::list<boost::shared_ptr<Unit> > unitList;

		ar & BOOST_SERIALIZATION_NVP(unitList);
			
		if(version > 0) {
		}

		::new(units)Units(unitList);

		units->initializeUnitList();
	}
	// only call after deserialization
	void initializeUnitList();


	std::list<boost::shared_ptr<Unit> > unitList;
	
	// temporary variables (cache etc.)

	// unitID -> Unit map (unique! NOT unitTypeId!)
	std::map<const boost::uuids::uuid, const boost::shared_ptr<Unit> > unitMap;

	std::map<const boost::uuids::uuid, unsigned int> globalNeutralAvailable; // unitTypeId -> amount
	std::map<const boost::uuids::uuid, unsigned int> globalNeutralTotal; // unitTypeId -> amount
	std::map<const UnitGlobalKey, unsigned int> globalAvailable; // playerId -> unitTypeId -> amount
	std::map<const UnitGlobalKey, unsigned int> globalTotal; // playerId -> unitTypeId -> amount
	std::map<const UnitLocalKey, unsigned int> localAvailable; // locationId -> playerId -> unitTypeId -> amount
	std::map<const UnitLocalKey, unsigned int> localTotal; // locationId -> playerId -> unitTypeId -> amount
	std::map<const UnitLocalNeutralKey, unsigned int> localNeutralAvailable; // locationId -> unitTypeId -> amount
	std::map<const UnitLocalNeutralKey, unsigned int> localNeutralTotal; // locationId -> unitTypeId -> amount

	// these need to be private, no other class has a business administrating the total values!
	void addOneGlobalNeutralTotal(const boost::uuids::uuid key);
	void removeOneGlobalNeutralTotal(const boost::uuids::uuid key);
	void addOneGlobalTotal(const UnitGlobalKey& key);
	void removeOneGlobalTotal(const UnitGlobalKey& key);
	void addOneLocalTotal(const UnitLocalKey& key);
	void removeOneLocalTotal(const UnitLocalKey& key);	
	void addOneLocalNeutralTotal(const UnitLocalNeutralKey& key);
	void removeOneLocalNeutralTotal(const UnitLocalNeutralKey& key);	
};

inline const std::list<boost::shared_ptr<Unit> >& Units::getUnitList() const {
	return unitList;
}

inline const boost::shared_ptr<Unit>& Units::getUnit(const boost::uuids::uuid unitId) const {
	if(unitMap.find(unitId) == unitMap.end()) {
		throw "Invalid unit id!";
	}
	return unitMap.find(unitId)->second;
}

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


/**
 * LOCAL
 */
inline void Units::addOneLocalAvailable(const UnitLocalKey& key) {
	++localAvailable[key];

	addOneGlobalAvailable(UnitGlobalKey(key.playerId, key.unitTypeId));
}

inline void Units::removeOneLocalAvailable(const UnitLocalKey& key) {
	BOOST_ASSERT(localAvailable[key] > 0);

	--localAvailable[key];

	removeOneLocalNeutralTotal(UnitLocalNeutralKey(key.locationId, key.unitTypeId));
	removeOneGlobalAvailable(UnitGlobalKey(key.playerId, key.unitTypeId));
}

inline void Units::addOneLocalTotal(const UnitLocalKey& key) {
	++localTotal[key];

	addOneLocalNeutralTotal(UnitLocalNeutralKey(key.locationId, key.unitTypeId));
	addOneGlobalTotal(UnitGlobalKey(key.playerId, key.unitTypeId));
}

inline void Units::removeOneLocalTotal(const UnitLocalKey& key) {
	BOOST_ASSERT(localTotal[key] > 0);

	--localTotal[key];

	removeOneLocalNeutralTotal(UnitLocalNeutralKey(key.locationId, key.unitTypeId));
	removeOneGlobalTotal(UnitGlobalKey(key.playerId, key.unitTypeId));
}

/**
 *  GLOBAL
 */
inline void Units::addOneGlobalAvailable(const UnitGlobalKey& key) {
	++globalAvailable[key];

	// addOneGlobalNeutralAvailable(key.unitTypeId);
}

inline void Units::removeOneGlobalAvailable(const UnitGlobalKey& key) {
	BOOST_ASSERT(globalAvailable[key] > 0);

	--globalAvailable[key];

	// removeOneGlobalNeutralAvailable(key.unitTypeId);
}

inline void Units::addOneGlobalTotal(const UnitGlobalKey& key) {
	++globalTotal[key];

	// addOneGlobalNeutralAvailable(key.unitTypeId);
}

inline void Units::removeOneGlobalTotal(const UnitGlobalKey& key) {
	BOOST_ASSERT(globalTotal[key] > 0);

	--globalTotal[key];

	// removeOneGlobalNeutralTotal(key.unitTypeId);
}

/**
 * NEUTRAL
 */

// remember: there are no global neutral units!
inline void Units::addOneLocalNeutralAvailable(const UnitLocalNeutralKey& key) {
	++localNeutralAvailable[key];
}

inline void Units::removeOneLocalNeutralAvailable(const UnitLocalNeutralKey& key) {
	BOOST_ASSERT(localNeutralAvailable[key] > 0);

	--localNeutralAvailable[key];
}

inline void Units::addOneLocalNeutralTotal(const UnitLocalNeutralKey& key) {
	++localNeutralTotal[key];
}

inline void Units::removeOneLocalNeutralTotal(const UnitLocalNeutralKey& key) {
	BOOST_ASSERT(localNeutralTotal[key] > 0);

	--localNeutralTotal[key];
}

#endif // _CORE_UNITS_HPP

