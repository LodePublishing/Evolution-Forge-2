#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "broodwar.hpp"
// TODO als XML abspeichern, Editor schreiben
Broodwar::Broodwar():
	GameData(new Rules("Broodwar"))
{
	neutralRace = new Race("Neutral");
	terraRace = new Race("Terra");
	protossRace = new Race("Protoss");
	zergRace = new Race("Zerg");

	rules->addRace(*neutralRace);
	rules->addRace(*terraRace);
	rules->addRace(*protossRace);
	rules->addRace(*zergRace);


	rules->addUnitType(UnitType("Mineral", neutralRace, 0, 99999, false, NO_MOVEMENT_TYPE, 0,
		
		boost::assign::list_of
		(UnitResourceType(RESOURCE_RESOURCES, boost::assign::list_of
		(boost::assign::list_of(MINERAL_PATCH)(SCV)(COMMAND_CENTER)), 1))));
//		(boost::assign::list_of(MINERAL_PATCH)(PROBE)(NEXUS))
//		(boost::assign::list_of(MINERAL_PATCH)(DRONE)(HATCHERY)), // TODO lair, hive
		// TODO all gatherer / accepter combinations!

// TODO optimize!
	rules->addUnitType(UnitType("Gas", neutralRace, 0, 99999, false, NO_MOVEMENT_TYPE, 0,
		
		boost::assign::list_of
		(UnitResourceType(RESOURCE_RESOURCES, boost::assign::list_of
		(boost::assign::list_of(REFINERY)(GAS_SCV)(COMMAND_CENTER)), 1))));
//		(boost::assign::list_of(EXTRACTOR)(GAS_DRONE)(HATCHERY)) // TODO LAIR, HIVE
//		(boost::assign::list_of(ASSIMILATOR)(GAS_PROBE)(NEXUS)),
	// TODO all combinations!	


rules->addUnitType(UnitType("Terran Supply", neutralRace, 0, 200, false, NO_MOVEMENT_TYPE, 0,
	boost::assign::list_of
	(UnitResourceType(SUPPLY_PROVIDER, boost::assign::list_of(boost::assign::list_of(COMMAND_CENTER)(SUPPLY_DEPOT)), 1))));
//	rules->addUnitType(UnitType("Protoss Supply", protossRace, 0, 200, std::list<UnitResourceType>(),
//		(UnitResourceType(SUPPLY_PROVIDER, boost::assign::list_of(boost::assign::list_of(NEXUS)(PYLON)), 1)), TODO
//		UnitBattleStats(false, NO_MOVEMENT_TYPE, 0)));
//	rules->addUnitType(UnitType("Zerg Supply", zergRace, 0, 200, std::list<UnitResourceType>(),
		//(UnitResourceType(SUPPLY_PROVIDER, boost::assign::list_of(boost::assign::list_of(HATCHERY)(OVERLORD)), 1)), TODO
//		UnitBattleStats(false, NO_MOVEMENT_TYPE, 0)));

	rules->addUnitType(UnitType("Mineral Patch", neutralRace, 0, 99999, true, NO_MOVEMENT_TYPE, 0,
		
		boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, boost::assign::list_of(boost::assign::list_of(MINERAL)(SCV)(COMMAND_CENTER)), 1)))); 

/*	rules->addUnitType(UnitType("Depleted Mineral Patch", neutralRace, 0, 99999, boost::assign::list_of

		(UnitResourceType(SOURCE_RESOURCES, boost::assign::list_of(boost::assign::list_of(MINERAL)(SCV)(COMMAND_CENTER)), 1)), 
		UnitBattleStats(true, NO_MOVEMENT_TYPE, 0)));
*/
	rules->addUnitType(UnitType("Vespene Geysir", neutralRace, 0, 99999, true, NO_MOVEMENT_TYPE, 0,
		boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, boost::assign::list_of(boost::assign::list_of(GAS)(GAS_SCV)(COMMAND_CENTER)), 1)))); // TODO all combinations



/*	rules->addUnitType(UnitType("Depleted Vespene Geysir", neutralRace, 0, 99999, boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, boost::assign::list_of(boost::assign::list_of(GAS)(GAS_SCV)(COMMAND_CENTER)), 1)), // TODO all combinations
		UnitBattleStats(true, NO_MOVEMENT_TYPE, 0)));
*/
	
	rules->addUnitType(UnitType("SCV", terraRace, 300, 99999, true, GROUND_MOVEMENT_TYPE, 10, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, boost::assign::list_of(boost::assign::list_of(COMMAND_CENTER)), 1))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)), 1))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(MINERAL)), 50))

		(UnitResourceType(GATHERER_RESOURCES, boost::assign::list_of(boost::assign::list_of(MINERAL)(MINERAL_PATCH)(COMMAND_CENTER)), 1)))); // TODO all combinations?
 

	rules->addUnitType(UnitType("Gas SCV", terraRace, 10, 99999, true, GROUND_MOVEMENT_TYPE, 10, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, boost::assign::list_of(boost::assign::list_of(SCV)), 1))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)), 1))
		(UnitResourceType(GATHERER_RESOURCES, boost::assign::list_of(boost::assign::list_of(GAS)(REFINERY)(COMMAND_CENTER)), 1)))); // TODO all combinations?
 

	rules->addUnitType(UnitType("Command Center", terraRace, 1800, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, boost::assign::list_of(boost::assign::list_of(SCV)), 1))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(MINERAL)), 400))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)), 10))

		(UnitResourceType(ACCEPTER_RESOURCES, boost::assign::list_of(boost::assign::list_of(MINERAL)(MINERAL_PATCH)(SCV)), 1)))); // TODO later: also gas etc.


	rules->addUnitType(UnitType("Supply Depot", terraRace, 600, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(MINERAL)), 100))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)), 8)))); 

	rules->addUnitType(UnitType("Refinery", terraRace, 600, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(MINERAL)), 100))
		(UnitResourceType(FACILITY_IS_NEEDED_ALWAYS_RESOURCE, boost::assign::list_of(boost::assign::list_of(VESPENE_GEYSIR)), 1)))); 

	rules->addUnitType(UnitType("Barracks", terraRace, 1200, 99999, true, NO_MOVEMENT_TYPE, 0, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, boost::assign::list_of(boost::assign::list_of(SCV)), 1))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(MINERAL)), 150))));

	rules->addUnitType(UnitType("Space Marine", terraRace, 360, 99999, true, GROUND_MOVEMENT_TYPE, 10, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, boost::assign::list_of(boost::assign::list_of(BARRACKS)), 1))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, boost::assign::list_of(boost::assign::list_of(MINERAL)), 50))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, boost::assign::list_of(boost::assign::list_of(TERRAN_SUPPLY)), 1))));


/*
	rules->addUnitType(UnitType("Probe", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Nexus", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Drone", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Hatchery", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Refinery", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Gas SCV", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Extractor", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Gas Drone", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Assimilator", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Gas Probe", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Gas", terraRace, 360, 99999, boost::assign::list_of
	rules->addUnitType(UnitType("Vespene Geysir", terraRace, 360, 99999, boost::assign::list_of

Games/Broodwar.cpp:23: error: ‘PROBE’ was not declared in this scope
Games/Broodwar.cpp:23: error: ‘NEXUS’ was not declared in this scope
Games/Broodwar.cpp:24: error: ‘DRONE’ was not declared in this scope
Games/Broodwar.cpp:24: error: ‘HATCHERY’ was not declared in this scope
Games/Broodwar.cpp:32: error: ‘REFINERY’ was not declared in this scope
Games/Broodwar.cpp:32: error: ‘GAS_SCV’ was not declared in this scope
Games/Broodwar.cpp:33: error: ‘EXTRACTOR’ was not declared in this scope
Games/Broodwar.cpp:33: error: ‘GAS_DRONE’ was not declared in this scope
Games/Broodwar.cpp:34: error: ‘ASSIMILATOR’ was not declared in this scope
Games/Broodwar.cpp:34: error: ‘GAS_PROBE’ was not declared in this scope
Games/Broodwar.cpp:55: error: ‘GAS’ was not declared in this scope
Games/Broodwar.cpp:98: error: ‘VESPENE_GEYSIR’ was not declared in this scope
*/
}

Broodwar::~Broodwar()
{
	delete neutralRace;
	delete terraRace;
	delete protossRace;
	delete zergRace;

}
