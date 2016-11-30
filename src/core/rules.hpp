#ifndef _CORE_RULES_HPP
#define _CORE_RULES_HPP

#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <loadsave.hpp>
#include <uuid.hpp>

#include <globalstorage.hpp>

#include "unittype.hpp"


class Rules : public LoadSave<Rules>, public UUID<Rules>
{
public:
	Rules(const boost::uuids::uuid id,
		const std::string& name, 
		const std::list<boost::shared_ptr<const Race> > raceList,
		const std::list<boost::shared_ptr<const UnitType> > unitTypeList);
	Rules(const std::string& name, 
		const std::list<boost::shared_ptr<const Race> > raceList,
		const std::list<boost::shared_ptr<const UnitType> > unitTypeList);
	~Rules();	

	const std::string& getName() const;
	const boost::shared_ptr<const UnitType> getUnitType(boost::uuids::uuid unitTypeId) const;
	const std::list<boost::shared_ptr<const UnitType> >& getUnitTypeList() const;	
	const std::list<boost::uuids::uuid>& getUnitTypeIdList() const;
	unsigned int getUnitTypeCount() const;

	const boost::shared_ptr<const Race> getRace(boost::uuids::uuid raceId) const;
	const std::list<boost::shared_ptr<const Race> >& getRaceList() const;
	const std::list<boost::uuids::uuid>& getRaceIdList() const;
	unsigned int getRaceCount() const;
	

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Rules* rules, const unsigned int version) { 

		const boost::uuids::uuid& id = rules->getId();
		const std::string& name = rules->getName();
		const std::list<boost::uuids::uuid>& unitTypeIdList = rules->getUnitTypeIdList();
		const std::list<boost::uuids::uuid>& raceIdList = rules->getRaceIdList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(raceIdList)
		   & BOOST_SERIALIZATION_NVP(unitTypeIdList);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Rules*& rules, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;
		std::list<boost::uuids::uuid> raceIdList;
		std::list<boost::uuids::uuid> unitTypeIdList;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(raceIdList)
		   & BOOST_SERIALIZATION_NVP(unitTypeIdList);

		if(version > 0) {
		}

		std::list<boost::shared_ptr<const Race> > raceList;
		std::list<boost::shared_ptr<const UnitType> > unitTypeList;

		for(std::list<boost::uuids::uuid>::const_iterator i = raceIdList.begin(); i != raceIdList.end(); i++) {
			raceList.push_back(GlobalStorage::instance().getRace(*i));
		}
		for(std::list<boost::uuids::uuid>::const_iterator i = unitTypeIdList.begin(); i != unitTypeIdList.end(); i++) {
			unitTypeList.push_back(GlobalStorage::instance().getUnitType(*i));
		}

		::new(rules)Rules(id, name, raceList, unitTypeList);
	}

	void initialize();

	const std::string name;
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList;	
	std::list<boost::uuids::uuid> unitTypeIdList;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > unitTypeMap;
	
	const std::list<boost::shared_ptr<const Race> > raceList;	
	std::list<boost::uuids::uuid> raceIdList;
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > raceMap;

	Rules& operator=(const Rules& other);
};

inline const std::list<boost::shared_ptr<const UnitType> >& Rules::getUnitTypeList() const {
	return unitTypeList;
}

inline const std::list<boost::uuids::uuid>& Rules::getUnitTypeIdList() const {
	return unitTypeIdList;
}

inline unsigned int Rules::getUnitTypeCount() const {
	return unitTypeList.size();
}

inline const std::string& Rules::getName() const {
	return name;
}

inline const std::list<boost::shared_ptr<const Race> >& Rules::getRaceList() const {
	return raceList;
}

inline const std::list<boost::uuids::uuid>& Rules::getRaceIdList() const {
	return raceIdList;
}

inline unsigned int Rules::getRaceCount() const {
	return raceList.size();
}


#endif
