#ifndef _CORE_RULES_HPP
#define _CORE_RULES_HPP


#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#pragma warning(pop)

#include <loadsave.hpp>

#include "unittype.hpp"
#include "id.hpp"

class Rules : public LoadSave<Rules>, public ID<Rules>
{
public:
	Rules(const std::string& name);
	~Rules();

	void addUnitType(const UnitType& unitType);
	void addRace(const Race& race);

	const std::list<Race>& getRaceList() const;
	const std::string& getName() const;

	const UnitType& getUnitType(unsigned int unitTypeID) const;
	const std::map<unsigned int, UnitType>& getUnitTypeMap() const;

	// call after deserialization to properly assign race IDs to the unitTypes
	void initializeRaces();

	//void initializeTemporaryVariables(); TODO

	unsigned int getUnitTypeCount() const;

	// needs to be public to allow deserialization (loading)
	Rules() {}

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		ar & boost::serialization::make_nvp(RaceList_tag_string, raceList);
		ar & boost::serialization::make_nvp(UnitTypeMap_tag_string, unitTypeMap);
		if(version > 0) {
		}
	}

	std::string name;
	std::list<Race> raceList;
	std::map<unsigned int, UnitType> unitTypeMap;

	static const char* const UnitTypeMap_tag_string;
	static const char* const RaceList_tag_string;
	static const char* const Name_tag_string;

};

inline const std::map<unsigned int, UnitType>& Rules::getUnitTypeMap() const {
	return unitTypeMap;
}

inline unsigned int Rules::getUnitTypeCount() const {
	return unitTypeMap.size();
}

inline const UnitType& Rules::getUnitType(unsigned int unitTypeID) const {
	const std::map<unsigned int, UnitType>::const_iterator i = unitTypeMap.find(unitTypeID);
	if(i == unitTypeMap.end()) {
		throw "Could not find unit type ID";
	}
	return (*i).second;
}

inline const std::list<Race>& Rules::getRaceList() const {
	return raceList;
}

inline const std::string& Rules::getName() const {
	return name;
}

#endif
