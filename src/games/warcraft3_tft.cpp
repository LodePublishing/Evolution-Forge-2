#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "enums/warcraft3_tftraces.hpp"
#include "enums/warcraft3_tftunits.hpp"

#include "warcraft3_tft.hpp"

WarCraft3TFT::WarCraft3TFT():
	GameData(init_raceidmap_helper(), init_unitidmap_helper()),
	neutralRace(new Race(race_id_map[NEUTRAL_RACE], "Neutral")),
	humanRace(new Race(race_id_map[HUMAN_RACE], "Human")),
	orcRace(new Race(race_id_map[ORC_RACE], "Orc")),
	nightelfRace(new Race(race_id_map[NIGHTELF_RACE], "Nightelf")),
	undeadRace(new Race(race_id_map[UNDEAD_RACE], "Undead"))
{ 	
	rules = boost::shared_ptr<const Rules>(new Rules(Misc::uuid("{339ddf20-3194-11e0-91fa-0800200c9a66}"), "WarCraft3TFT", init_racelist_helper(), init_unittypelist_helper()));
	initRules();	
}

WarCraft3TFT::~WarCraft3TFT()
{ }


const std::list<boost::shared_ptr<const Race> > WarCraft3TFT::init_racelist_helper() const {
	std::list<boost::shared_ptr<const Race> > raceList;

	raceList.push_back(neutralRace);
	raceList.push_back(humanRace);
	raceList.push_back(orcRace);
	raceList.push_back(nightelfRace);
	raceList.push_back(undeadRace);

	return raceList;
}

const std::map<const unsigned int, const boost::uuids::uuid> WarCraft3TFT::init_raceidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> raceIdMap;

	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NEUTRAL_RACE, Misc::uuid("{1b38f2c0-3195-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_RACE, Misc::uuid("{1eda8380-3195-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_RACE, Misc::uuid("{22720220-3195-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NIGHTELF_RACE, Misc::uuid("{25b2ae30-3195-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(UNDEAD_RACE, Misc::uuid("{298b5480-3195-11e0-91fa-0800200c9a66}")));

	return raceIdMap;
}


const std::map<const unsigned int, const boost::uuids::uuid> WarCraft3TFT::init_unitidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> unitMap;

//	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NONE, Misc::uuid("{ca01df58-1e9c-11e0-a2fd-0025d338d400}")));

	return unitMap;
}


const std::list<boost::shared_ptr<const UnitType> > WarCraft3TFT::init_unittypelist_helper() {
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
