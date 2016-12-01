#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "moo.hpp"
#include "enums/mooraces.hpp"
#include "enums/moounits.hpp"

MasterOfOrion::MasterOfOrion():
	GameData(init_raceidmap_helper(), init_unitidmap_helper()),
	neutralRace(new Race(race_id_map[NEUTRAL_RACE], "Neutral"))
{
	rules = boost::shared_ptr<const Rules>(new Rules(Misc::uuid("{0fd51ae0-3194-11e0-91fa-0800200c9a66}"), "MasterOfOrion", init_racelist_helper(), init_unittypelist_helper()));
	initRules();
}

MasterOfOrion::~MasterOfOrion()
{ }

const std::list<boost::shared_ptr<const Race> > MasterOfOrion::init_racelist_helper() const {
	std::list<boost::shared_ptr<const Race> > raceList;

	raceList.push_back(neutralRace);

	return raceList;
}


const std::map<const unsigned int, const boost::uuids::uuid> MasterOfOrion::init_raceidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> raceIdMap;

	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NEUTRAL_RACE, Misc::uuid("{26885840-3196-11e0-91fa-0800200c9a66}")));

	return raceIdMap;
}


const std::map<const unsigned int, const boost::uuids::uuid> MasterOfOrion::init_unitidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> unitMap;

//	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NONE, Misc::uuid("{ca01df58-1e9c-11e0-a2fd-0025d338d400}")));

	return unitMap;
}


const std::list<boost::shared_ptr<const UnitType> > MasterOfOrion::init_unittypelist_helper() {
	std::list<boost::shared_ptr<const UnitType> > unitTypeList;
	

	/*
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NONE], "None", neutralRace)));
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LOCATION_PRIORITY], "Set priority", neutralRace))); // TODO set priority
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[WAIT], "Wait", neutralRace)));	 // TODO wait command
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[BREAK_UP_BUILDING], "Break up building", neutralRace))); // TODO cancel building command



	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MINERAL], "Mineral", neutralRace, 
		boost::assign::list_of
		(UnitResourceType(RESOURCE_RESOURCES, 1, boost::assign::list_of
		(boost::assign::list_of(unit_id_map[MINERAL_PATCH])(unit_id_map[SCV])(unit_id_map[COMMAND_CENTER]))
		(boost::assign::list_of(unit_id_map[MINERAL_PATCH])(unit_id_map[PROBE])(unit_id_map[NEXUS]))
		(boost::assign::list_of(unit_id_map[MINERAL_PATCH])(unit_id_map[DRONE])(unit_id_map[HATCHERY]))
		(boost::assign::list_of(unit_id_map[MINERAL_PATCH])(unit_id_map[DRONE])(unit_id_map[LAIR]))
		(boost::assign::list_of(unit_id_map[MINERAL_PATCH])(unit_id_map[DRONE])(unit_id_map[HIVE]))
		))
		)));
	// TODO all gatherer / accepter combinations! (mind control)
	// TODO optimize!*/


	return unitTypeList;
}
