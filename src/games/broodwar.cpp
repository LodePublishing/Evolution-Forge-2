#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "broodwar.hpp"
#include <globalstorage.hpp>

// TODO als XML abspeichern, Editor schreiben
Broodwar::Broodwar():
	GameData(),
	neutralRace(boost::shared_ptr<const Race>(new Race("Neutral"))),
	terraRace(boost::shared_ptr<const Race>(new Race("Terra"))),
	protossRace(boost::shared_ptr<const Race>(new Race("Protoss"))),
	zergRace(boost::shared_ptr<const Race>(new Race("Zerg"))),
	rules(new Rules("Broodwar", init_unittypelist_helper()))	
{
	GLOBAL_STORAGE.addRace(neutralRace);
	GLOBAL_STORAGE.addRace(terraRace);
	GLOBAL_STORAGE.addRace(protossRace);
	GLOBAL_STORAGE.addRace(zergRace);

	GLOBAL_STORAGE.addRules(rules);
}

Broodwar::~Broodwar()
{ 
	Rules::resetCounter();
	Race::resetCounter();
	UnitType::resetCounter();

	GLOBAL_STORAGE.clear();
}

const std::list<boost::shared_ptr<const UnitType> > Broodwar::init_unittypelist_helper() {
	std::list<boost::shared_ptr<const UnitType> > unitTypeList;

	//boost::assign::list_of(boost::shared_ptr<const UnitType>
	
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Mineral", neutralRace, 0, 99999, false, NO_MOVEMENT_TYPE, 0,
		
		boost::assign::list_of
		(UnitResourceType(RESOURCE_RESOURCES, 1, boost::assign::list_of
		(boost::assign::list_of(MINERAL_PATCH)(SCV)(COMMAND_CENTER)))))));
//		(boost::assign::list_of(MINERAL_PATCH)(PROBE)(NEXUS))
//		(boost::assign::list_of(MINERAL_PATCH)(DRONE)(HATCHERY)), // TODO lair, hive
		// TODO all gatherer / accepter combinations!
		
// TODO optimize!
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Gas", neutralRace, 0, 99999, false, NO_MOVEMENT_TYPE, 0,
		
		boost::assign::list_of
		(UnitResourceType(RESOURCE_RESOURCES, 1, boost::assign::list_of
		(boost::assign::list_of(REFINERY)(GAS_SCV)(COMMAND_CENTER)))))));
//		(boost::assign::list_of(EXTRACTOR)(GAS_DRONE)(HATCHERY)) // TODO LAIR, HIVE
//		(boost::assign::list_of(ASSIMILATOR)(GAS_PROBE)(NEXUS)),
	// TODO all combinations!	


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Terran Supply", neutralRace, 0, 200, false, NO_MOVEMENT_TYPE, 0,
	boost::assign::list_of
	(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(COMMAND_CENTER)(SUPPLY_DEPOT))))
	(UnitResourceType(NOT_BUILDABLE, 0, std::list<std::list<unsigned int> >()))
	)));

//	(new UnitType("Protoss Supply", protossRace, 0, 200, std::list<UnitResourceType>(),
//		(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(NEXUS)(PYLON)))), TODO
//		UnitBattleStats(false, NO_MOVEMENT_TYPE, 0)))
//	(new UnitType("Zerg Supply", zergRace, 0, 200, std::list<UnitResourceType>(),
		//(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(HATCHERY)(OVERLORD)))), TODO
//		UnitBattleStats(false, NO_MOVEMENT_TYPE, 0)))

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Mineral Patch", neutralRace, 0, 99999, true, NO_MOVEMENT_TYPE, 0,
		
		boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(MINERAL)(SCV)(COMMAND_CENTER))))
		(UnitResourceType(NOT_BUILDABLE, 0, std::list<std::list<unsigned int> >())))));

//	(new UnitType("Depleted Mineral Patch", neutralRace, 0, 99999, boost::assign::list_of
//		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(MINERAL)(SCV)(COMMAND_CENTER)))), 
//		UnitBattleStats(true, NO_MOVEMENT_TYPE, 0)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Vespene Geysir", neutralRace, 0, 99999, true, NO_MOVEMENT_TYPE, 0,
		boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(GAS)(GAS_SCV)(COMMAND_CENTER)))) // TODO all combinations
		(UnitResourceType(NOT_BUILDABLE, 0, std::list<std::list<unsigned int> >())))));


//	(new UnitType("Depleted Vespene Geysir", neutralRace, 0, 99999, boost::assign::list_of
//		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(GAS)(GAS_SCV)(COMMAND_CENTER)))), // TODO all combinations
//		UnitBattleStats(true, NO_MOVEMENT_TYPE, 0)));

	
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("SCV", terraRace, 300, 99999, true, GROUND_MOVEMENT_TYPE, 10, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(COMMAND_CENTER))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(MINERAL))))

		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(MINERAL)(MINERAL_PATCH)(COMMAND_CENTER))))))); // TODO all combinations?
 

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Gas SCV", terraRace, 10, 99999, true, GROUND_MOVEMENT_TYPE, 10, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(SCV))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY))))
		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(GAS)(REFINERY)(COMMAND_CENTER))))))); // TODO all combinations?
 

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Command Center", terraRace, 1800, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(SCV))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(MINERAL))))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, 10, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY))))

		(UnitResourceType(ACCEPTER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(MINERAL)(MINERAL_PATCH)(SCV))))))); // TODO later: also gas etc.


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Supply Depot", terraRace, 600, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(SCV))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(MINERAL))))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, 8, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)))))));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Refinery", terraRace, 600, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(SCV))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(MINERAL))))
		(UnitResourceType(FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(VESPENE_GEYSIR)))))));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Barracks", terraRace, 1200, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(SCV))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(MINERAL)))))));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType("Space Marine", terraRace, 360, 99999, true, GROUND_MOVEMENT_TYPE, 10, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(BARRACKS))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(MINERAL))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)))))));
		
	
	return unitTypeList;
}