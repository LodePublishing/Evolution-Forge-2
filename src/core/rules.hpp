#ifndef _CORE_RULES_HPP
#define _CORE_RULES_HPP

#include <map>

#pragma warning(push, 0)
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>

#include "unittype.hpp"


class Rules : public UUID<Rules>
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
