#ifndef _CORE_RULES_HPP
#define _CORE_RULES_HPP

#include <map>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <loadsave.hpp>
#include <uuid.hpp>

#include "unittype.hpp"


class Rules : public LoadSave<Rules>, public UUID<Rules>
{
public:
	Rules(const boost::uuids::uuid id,
		const std::string& name, 
		const std::list<boost::shared_ptr<const UnitType> > unitTypeList);
	Rules(const std::string& name, 
		const std::list<boost::shared_ptr<const UnitType> > unitTypeList);
	~Rules();	

	const std::string& getName() const;
	const boost::shared_ptr<const UnitType> getUnitType(boost::uuids::uuid unitTypeId) const;
	const std::list<boost::shared_ptr<const UnitType> >& getUnitTypeList() const;	
	unsigned int getUnitTypeCount() const;

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Rules* rules, const unsigned int version) { 

		const boost::uuids::uuid& id = rules->getId();
		const std::string& name = rules->getName();
		const std::list<boost::shared_ptr<const UnitType> >& unitTypeList = rules->getUnitTypeList();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(unitTypeList);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Rules*& rules, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;
		std::list<boost::shared_ptr<const UnitType> > unitTypeList;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(unitTypeList);

		if(version > 0) {
		}

		::new(rules)Rules(id, name, unitTypeList);
	}

	void initializeUnitTypes();

	const std::string name;
	const std::list<boost::shared_ptr<const UnitType> > unitTypeList;
	
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > unitTypeMap;

	Rules& operator=(const Rules& other);
};

inline const std::list<boost::shared_ptr<const UnitType> >& Rules::getUnitTypeList() const {
	return unitTypeList;
}

inline unsigned int Rules::getUnitTypeCount() const {
	return unitTypeList.size();
}

inline const std::string& Rules::getName() const {
	return name;
}

#endif
