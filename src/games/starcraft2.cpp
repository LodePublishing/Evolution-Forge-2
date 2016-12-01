#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "starcraft2.hpp"
#include "enums/starcraft2races.hpp"
#include "enums/starcraft2units.hpp"

#include <misc/miscellaneous.hpp>

StarCraft2::StarCraft2():
	GameData(init_raceidmap_helper(), init_unitidmap_helper()),
	neutralRace(boost::shared_ptr<Race>(new Race(race_id_map[NEUTRAL_RACE], "Neutral"))),
	terraRace(boost::shared_ptr<Race>(new Race(race_id_map[TERRA_RACE], "Terra"))),
	protossRace(boost::shared_ptr<Race>(new Race(race_id_map[PROTOSS_RACE], "Protoss"))),
	zergRace(boost::shared_ptr<Race>(new Race(race_id_map[ZERG_RACE], "Zerg")))
{ 
	rules = boost::shared_ptr<const Rules>(new Rules(Misc::uuid("{1c1b0ad0-3194-11e0-91fa-0800200c9a66}"), "StarCraft2", init_racelist_helper(), init_unittypelist_helper()));
	initRules();	
}

StarCraft2::~StarCraft2()
{ }

const std::list<boost::shared_ptr<const Race> > StarCraft2::init_racelist_helper() const {
	std::list<boost::shared_ptr<const Race> > raceList;

	raceList.push_back(neutralRace);
	raceList.push_back(terraRace);
	raceList.push_back(protossRace);
	raceList.push_back(zergRace);

	return raceList;
}


const std::map<const unsigned int, const boost::uuids::uuid> StarCraft2::init_raceidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> raceIdMap;

	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NEUTRAL_RACE, Misc::uuid("{8a90b670-3196-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TERRA_RACE, Misc::uuid("{8e581eb0-3196-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PROTOSS_RACE, Misc::uuid("{935c4cb0-3196-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ZERG_RACE, Misc::uuid("{966260c0-3196-11e0-91fa-0800200c9a66}")));

	return raceIdMap;
}

const std::map<const unsigned int, const boost::uuids::uuid> StarCraft2::init_unitidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> unitMap;

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NONE, Misc::uuid("{82cea0f0-3196-11e0-91fa-0800200c9a66}")));
	/*
	TODO new UUIDS!
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MINERAL, Misc::uuid("{d8831be0-1c4f-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GAS, Misc::uuid("{cbd8c008-1e9c-11e0-a80f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TERRAN_SUPPLY, Misc::uuid("{cdc41d36-1e9c-11e0-80b1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PROTOSS_SUPPLY, Misc::uuid("{ce461b6a-1e9c-11e0-9a92-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ZERG_SUPPLY, Misc::uuid("{ce67ab68-1e9c-11e0-9819-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MINERAL_PATCH, Misc::uuid("{ce84f6aa-1e9c-11e0-82c3-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEPLETED_MINERAL_PATCH, Misc::uuid("{ceaa57e2-1e9c-11e0-a199-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VESPENE_GEYSIR, Misc::uuid("{cece594e-1e9c-11e0-aa32-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEPLETED_VESPENE_GEYSIR, Misc::uuid("{cef1c3f2-1e9c-11e0-9105-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WAIT, Misc::uuid("{cf133cf8-1e9c-11e0-bd45-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BREAK_UP_BUILDING, Misc::uuid("{cf393ebc-1e9c-11e0-a28e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCV, Misc::uuid("{cf5dc7b4-1e9c-11e0-9281-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GAS_SCV, Misc::uuid("{cf8074c6-1e9c-11e0-96b9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCV_FROM_GAS_TO_MINERALS, Misc::uuid("{cfa81792-1e9c-11e0-bf3d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPACE_MARINE, Misc::uuid("{cfcadfb6-1e9c-11e0-8b89-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GHOST, Misc::uuid("{cff15074-1e9c-11e0-bc8f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VULTURE, Misc::uuid("{d011dc2c-1e9c-11e0-9b62-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GOLIATH, Misc::uuid("{d03204a2-1e9c-11e0-99b8-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SIEGE_TANK, Misc::uuid("{d04c6504-1e9c-11e0-88b9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FIREBAT, Misc::uuid("{d06461ae-1e9c-11e0-ad88-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MEDIC, Misc::uuid("{d079b5b8-1e9c-11e0-b623-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WRAITH, Misc::uuid("{d4b74082-1e9c-11e0-b9ad-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCIENCE_VESSEL, Misc::uuid("{d5636038-1e9c-11e0-86be-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DROPSHIP, Misc::uuid("{d591c1d0-1e9c-11e0-9c01-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BATTLE_CRUISER, Misc::uuid("{d5be4f52-1e9c-11e0-a39e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VALKYRIE, Misc::uuid("{d5eadce8-1e9c-11e0-9193-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NUCLEAR_WARHEAD, Misc::uuid("{d6178a5e-1e9c-11e0-a2a7-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(REFINERY, Misc::uuid("{d64367e6-1e9c-11e0-80f0-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEPLETED_REFINERY, Misc::uuid("{d66fefe6-1e9c-11e0-b766-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(COMMAND_CENTER, Misc::uuid("{d69c061c-1e9c-11e0-a88e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SUPPLY_DEPOT, Misc::uuid("{d6cd50c8-1e9c-11e0-a0cf-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BARRACKS, Misc::uuid("{d6fd84dc-1e9c-11e0-8493-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ACADEMY, Misc::uuid("{d8b460ca-1e9c-11e0-b666-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FACTORY, Misc::uuid("{d8e35f9c-1e9c-11e0-be5b-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(STARPORT, Misc::uuid("{d91fc892-1e9c-11e0-9620-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCIENCE_FACILITY, Misc::uuid("{d948ad20-1e9c-11e0-b129-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ENGINEERING_BAY, Misc::uuid("{d977ab66-1e9c-11e0-882c-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARMORY, Misc::uuid("{d9a1cf90-1e9c-11e0-97a3-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MISSILE_TURRET, Misc::uuid("{d9ca401a-1e9c-11e0-aa85-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BUNKER, Misc::uuid("{d9f3bd8c-1e9c-11e0-b9ef-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(COMSAT_STATION, Misc::uuid("{da1fc058-1e9c-11e0-b00e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NUCLEAR_SILO, Misc::uuid("{da4894f6-1e9c-11e0-ad22-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CONTROL_TOWER, Misc::uuid("{da734d86-1e9c-11e0-bff1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(COVERT_OPS, Misc::uuid("{da9c3eee-1e9c-11e0-aca9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PHYSICS_LAB, Misc::uuid("{e10377d4-1e9c-11e0-9429-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MACHINE_SHOP, Misc::uuid("{e2130f9a-1e9c-11e0-9f85-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(COMMAND_CENTER_CS, Misc::uuid("{e2691af2-1e9c-11e0-9854-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(COMMAND_CENTER_NS, Misc::uuid("{e3510ea2-1e9c-11e0-b296-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(STARPORT_CT, Misc::uuid("{e3a08c7a-1e9c-11e0-90cd-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCIENCE_FACILITY_CO, Misc::uuid("{e3f1bdac-1e9c-11e0-9568-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCIENCE_FACILITY_PL, Misc::uuid("{e4337a62-1e9c-11e0-b971-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FACTORY_MS, Misc::uuid("{e46fffb4-1e9c-11e0-ac9c-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(STIM_PACKS, Misc::uuid("{e4a53f94-1e9c-11e0-8b09-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LOCKDOWN, Misc::uuid("{e4eb3486-1e9c-11e0-a025-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(EMP_SHOCKWAVE, Misc::uuid("{e5266ad8-1e9c-11e0-b1a3-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPIDER_MINES, Misc::uuid("{e55cc114-1e9c-11e0-a35e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TANK_SIEGE_MODE, Misc::uuid("{e593a6ac-1e9c-11e0-8356-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(IRRADIATE, Misc::uuid("{e5cd099c-1e9c-11e0-8fe2-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(YAMATO_GUN, Misc::uuid("{e603f93e-1e9c-11e0-aced-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CLOAKING_FIELD, Misc::uuid("{e63b8fde-1e9c-11e0-bdc5-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PERSONNEL_CLOAKING, Misc::uuid("{e668b7c0-1e9c-11e0-a7ad-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(RESTORATION, Misc::uuid("{e6a330c6-1e9c-11e0-bafb-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(OPTICAL_FLARE, Misc::uuid("{e6e3da54-1e9c-11e0-9630-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(U238_SHELLS, Misc::uuid("{e73b41f4-1e9c-11e0-be57-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ION_THRUSTERS, Misc::uuid("{e779a7c8-1e9c-11e0-8cdd-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TITAN_REACTOR, Misc::uuid("{e7a3ca26-1e9c-11e0-a040-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(OCULAR_IMPLANTS, Misc::uuid("{e7d81948-1e9c-11e0-b787-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MOEBIUS_REACTOR, Misc::uuid("{e8085338-1e9c-11e0-b316-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(APOLLO_REACTOR, Misc::uuid("{e83c5944-1e9c-11e0-92e9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(COLOSSUS_REACTOR, Misc::uuid("{e87459ca-1e9c-11e0-9593-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CADUCEUS_REACTOR, Misc::uuid("{e8a4c254-1e9c-11e0-b362-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CHARON_BOOSTER, Misc::uuid("{e8d60710-1e9c-11e0-8f8e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INFANTRY_ARMOR_1, Misc::uuid("{e90a7ed2-1e9c-11e0-9611-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INFANTRY_ARMOR_2, Misc::uuid("{e93e618e-1e9c-11e0-add2-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INFANTRY_ARMOR_3, Misc::uuid("{e967e130-1e9c-11e0-a532-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INFANTRY_WEAPONS_1, Misc::uuid("{e99b3558-1e9c-11e0-9d16-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INFANTRY_WEAPONS_2, Misc::uuid("{e9d65886-1e9c-11e0-a2d1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INFANTRY_WEAPONS_3, Misc::uuid("{ea07d712-1e9c-11e0-8485-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VEHICLE_PLATING_1, Misc::uuid("{ea3b4070-1e9c-11e0-a82e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VEHICLE_PLATING_2, Misc::uuid("{ea6d44d0-1e9c-11e0-9d10-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VEHICLE_PLATING_3, Misc::uuid("{eaa2fc60-1e9c-11e0-b1d9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VEHICLE_WEAPONS_1, Misc::uuid("{ead6deae-1e9c-11e0-8065-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VEHICLE_WEAPONS_2, Misc::uuid("{eb08e94e-1e9c-11e0-aa01-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VEHICLE_WEAPONS_3, Misc::uuid("{eb42e3e2-1e9c-11e0-a835-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIP_PLATING_1, Misc::uuid("{eb789a50-1e9c-11e0-9bfe-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIP_PLATING_2, Misc::uuid("{eba8d3c8-1e9c-11e0-ac95-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIP_PLATING_3, Misc::uuid("{ebdfd8a0-1e9c-11e0-bd15-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIP_WEAPONS_1, Misc::uuid("{ec16b00a-1e9c-11e0-8cc3-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIP_WEAPONS_2, Misc::uuid("{ec51c492-1e9c-11e0-855d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIP_WEAPONS_3, Misc::uuid("{ec877056-1e9c-11e0-86de-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(F_FACTORY_ADDON, Misc::uuid("{ecbdd13c-1e9c-11e0-b0c0-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(F_STARPORT_ADDON, Misc::uuid("{ecee96a0-1e9c-11e0-9fdf-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(F_COMMAND_CENTER_ADDON, Misc::uuid("{ed227f42-1e9c-11e0-a913-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(F_SCIENCE_FACILITY_ADDON, Misc::uuid("{ed5d3bf0-1e9c-11e0-a8f5-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PROBE, Misc::uuid("{f19b8ee2-1e9c-11e0-962c-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GAS_PROBE, Misc::uuid("{f885805a-1e9c-11e0-9865-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PROBE_FROM_GAS_TO_MINERALS, Misc::uuid("{f8d810fe-1e9c-11e0-bd93-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DARK_TEMPLAR, Misc::uuid("{f91a9bfe-1e9c-11e0-a643-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DARK_ARCHON, Misc::uuid("{f9563eca-1e9c-11e0-bdbf-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ZEALOT, Misc::uuid("{f998f198-1e9c-11e0-807d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DRAGOON, Misc::uuid("{f9d54a44-1e9c-11e0-9f56-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HIGH_TEMPLAR, Misc::uuid("{fa130154-1e9c-11e0-b51d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARCHON, Misc::uuid("{fa53b4e2-1e9c-11e0-8046-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(REAVER, Misc::uuid("{fa8d94fa-1e9c-11e0-8427-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HALF_SCARAB, Misc::uuid("{fac8482a-1e9c-11e0-8fec-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FULL_SCARAB, Misc::uuid("{fb042598-1e9c-11e0-9cf8-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CORSAIR, Misc::uuid("{fb4a4b4a-1e9c-11e0-9500-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHUTTLE, Misc::uuid("{fb87ef04-1e9c-11e0-9063-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCOUT, Misc::uuid("{fbc01e9c-1e9c-11e0-b750-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARBITER, Misc::uuid("{fbfef84c-1e9c-11e0-8e47-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CARRIER, Misc::uuid("{fc3370ae-1e9c-11e0-a6e1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HALF_INTERCEPTOR, Misc::uuid("{fc692802-1e9c-11e0-a8bc-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FULL_INTERCEPTOR, Misc::uuid("{fc9e41ea-1e9c-11e0-b057-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(OBSERVER, Misc::uuid("{fcee479e-1e9c-11e0-806b-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ASSIMILATOR, Misc::uuid("{fd246252-1e9c-11e0-aa58-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEPLETED_ASSIMILATOR, Misc::uuid("{fd57a388-1e9c-11e0-8dba-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NEXUS, Misc::uuid("{fd910772-1e9c-11e0-b38e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ROBOTICS_FACILITY, Misc::uuid("{fdcb01de-1e9c-11e0-b7d1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PYLON, Misc::uuid("{fe028f50-1e9c-11e0-a380-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(OBSERVATORY, Misc::uuid("{fe4d013e-1e9c-11e0-bb5a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GATEWAY, Misc::uuid("{fe86fefc-1e9c-11e0-8f35-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PHOTON_CANNON, Misc::uuid("{feba4230-1e9c-11e0-b33b-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CYBERNETICS_CORE, Misc::uuid("{fef029fe-1e9c-11e0-8b05-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CITADEL_OF_ADUN, Misc::uuid("{ff22ac4e-1e9c-11e0-9001-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TEMPLAR_ARCHIVES, Misc::uuid("{ff6418d2-1e9c-11e0-946d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FORGE, Misc::uuid("{ff9b88ee-1e9c-11e0-adb3-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(STARGATE, Misc::uuid("{ffd27278-1e9c-11e0-9788-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLEET_BEACON, Misc::uuid("{000f99be-1e9d-11e0-9277-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARBITER_TRIBUNAL, Misc::uuid("{00499c2c-1e9d-11e0-b4d0-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ROBOTICS_SUPPORT_BAY, Misc::uuid("{0089abbe-1e9d-11e0-99d1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SHIELD_BATTERY, Misc::uuid("{00c7ec76-1e9d-11e0-a06f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PSIONIC_STORM, Misc::uuid("{01044950-1e9d-11e0-a122-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HALLUCINATION, Misc::uuid("{013ed124-1e9d-11e0-8476-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(RECALL, Misc::uuid("{01771ade-1e9d-11e0-aaee-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(STASIS_FIELD, Misc::uuid("{01b2e87a-1e9d-11e0-98d8-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DISRUPTION_WEB, Misc::uuid("{01f1ca0e-1e9d-11e0-b94a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MIND_CONTROL, Misc::uuid("{023252a4-1e9d-11e0-9dd1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MAELSTROM, Misc::uuid("{026bb058-1e9d-11e0-86fc-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SINGULARITY_CHARGE, Misc::uuid("{029f9346-1e9d-11e0-a52c-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LEG_ENHANCEMENTS, Misc::uuid("{02d371a2-1e9d-11e0-9f24-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCARAB_DAMAGE, Misc::uuid("{030afd34-1e9d-11e0-be05-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(REAVER_CAPACITY, Misc::uuid("{0340b53c-1e9d-11e0-a1a5-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GRAVITIC_DRIVE, Misc::uuid("{0374960e-1e9d-11e0-a2cf-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SENSOR_ARRAY, Misc::uuid("{03af5dde-1e9d-11e0-beb4-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GRAVITIC_BOOSTERS, Misc::uuid("{03e77e1c-1e9d-11e0-b23d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(KHAYDARIN_AMULET, Misc::uuid("{041e6cba-1e9d-11e0-a4b0-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(APIAL_SENSORS, Misc::uuid("{045530ec-1e9d-11e0-bca8-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GRAVITIC_THRUSTERS, Misc::uuid("{048d8334-1e9d-11e0-aafe-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CARRIER_CAPACITY, Misc::uuid("{04c30f7c-1e9d-11e0-b90f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(KHAYDARIN_CORE, Misc::uuid("{04fbfc38-1e9d-11e0-90c4-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARGUS_JEWEL, Misc::uuid("{0539a09c-1e9d-11e0-9c04-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARGUS_TALISMAN, Misc::uuid("{056b0fb0-1e9d-11e0-8f0f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARMOR_1, Misc::uuid("{05a4e172-1e9d-11e0-a597-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARMOR_2, Misc::uuid("{05e0b68e-1e9d-11e0-9a1a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARMOR_3, Misc::uuid("{061976ae-1e9d-11e0-8b5a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLATING_1, Misc::uuid("{06519d7c-1e9d-11e0-aa93-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLATING_2, Misc::uuid("{0691c7a8-1e9d-11e0-a23a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLATING_3, Misc::uuid("{06cd86b2-1e9d-11e0-b197-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GROUND_WEAPONS_1, Misc::uuid("{0705b55a-1e9d-11e0-9c40-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GROUND_WEAPONS_2, Misc::uuid("{0740e184-1e9d-11e0-a530-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GROUND_WEAPONS_3, Misc::uuid("{077d4f34-1e9d-11e0-8b96-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(AIR_WEAPONS_1, Misc::uuid("{07b13650-1e9d-11e0-9ea7-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(AIR_WEAPONS_2, Misc::uuid("{07ef99a4-1e9d-11e0-a053-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(AIR_WEAPONS_3, Misc::uuid("{082c09ca-1e9d-11e0-b556-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLASMA_SHIELDS_1, Misc::uuid("{0869ad70-1e9d-11e0-bd7a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLASMA_SHIELDS_2, Misc::uuid("{08a136e6-1e9d-11e0-ba1a-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLASMA_SHIELDS_3, Misc::uuid("{08db19c4-1e9d-11e0-810f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DRONE, Misc::uuid("{09163be4-1e9d-11e0-b48b-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GAS_DRONE, Misc::uuid("{094aba72-1e9d-11e0-b9df-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DRONE_FROM_GAS_TO_MINERALS, Misc::uuid("{0987c188-1e9d-11e0-af20-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LARVA, Misc::uuid("{09bf5206-1e9d-11e0-b4f9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ZERGLING, Misc::uuid("{09f1576a-1e9d-11e0-86cf-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HYDRALISK, Misc::uuid("{0a2402a0-1e9d-11e0-8496-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ULTRALISK, Misc::uuid("{0a509220-1e9d-11e0-aa73-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEFILER, Misc::uuid("{550753d4-1e9e-11e0-b132-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LURKER, Misc::uuid("{564a8644-1e9e-11e0-a6bc-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(OVERLORD, Misc::uuid("{575386e4-1e9e-11e0-a378-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MUTALISK, Misc::uuid("{5786a5a6-1e9e-11e0-bb30-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GUARDIEN, Misc::uuid("{582deac8-1e9e-11e0-8691-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(QUEEN, Misc::uuid("{585154cc-1e9e-11e0-a5c6-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCOURGE, Misc::uuid("{587905b2-1e9e-11e0-aca1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEVOURER, Misc::uuid("{589c5dbe-1e9e-11e0-b9af-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(EXTRACTOR, Misc::uuid("{58c236ec-1e9e-11e0-a844-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEPLETED_EXTRACTOR, Misc::uuid("{58e599d4-1e9e-11e0-b3f4-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HATCHERY, Misc::uuid("{590ad546-1e9e-11e0-b503-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LAIR, Misc::uuid("{592db3d6-1e9e-11e0-8ec9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HIVE, Misc::uuid("{59510c14-1e9e-11e0-b6d1-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NYDUS_CANAL, Misc::uuid("{59795548-1e9e-11e0-9383-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HYDRALISK_DEN, Misc::uuid("{59a2deb8-1e9e-11e0-860f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DEFILER_MOUND, Misc::uuid("{59d3a78c-1e9e-11e0-a2dd-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GREATER_SPIRE, Misc::uuid("{59f49ed8-1e9e-11e0-8b29-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(QUEENS_NEST, Misc::uuid("{5a1bb518-1e9e-11e0-bb3e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(EVOLUTION_CHAMBER, Misc::uuid("{5a40ea22-1e9e-11e0-9352-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ULTRALISK_CAVERN, Misc::uuid("{5a694ce2-1e9e-11e0-879b-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPIRE, Misc::uuid("{5a8f08ce-1e9e-11e0-a76b-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPAWNING_POOL, Misc::uuid("{5ab6b432-1e9e-11e0-ae15-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CREEP_COLONY, Misc::uuid("{5adeeccc-1e9e-11e0-885e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPORE_COLONY, Misc::uuid("{5b0b8890-1e9e-11e0-bedc-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SUNKEN_COLONY, Misc::uuid("{5b33d1ba-1e9e-11e0-b633-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(VENTRAL_SACKS, Misc::uuid("{5b5f2694-1e9e-11e0-88da-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ANTENNAE, Misc::uuid("{5b7fbd0a-1e9e-11e0-91cc-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PNEUMATIZED_CARAPACE, Misc::uuid("{5ba9066a-1e9e-11e0-a2cb-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(METABOLIC_BOOST, Misc::uuid("{5bcdb1fe-1e9e-11e0-acb8-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ADRENAL_GLANDS, Misc::uuid("{5bf54e80-1e9e-11e0-8017-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MUSCULAR_AUGMENTS, Misc::uuid("{5c1c33c4-1e9e-11e0-96de-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GROOVED_SPINES, Misc::uuid("{5c443932-1e9e-11e0-92ca-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GAMETE_MEIOSIS, Misc::uuid("{5c6d8e86-1e9e-11e0-a0ad-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(METASYNAPTIC_NODE, Misc::uuid("{5c9f9fac-1e9e-11e0-852d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CHITINOUS_PLATING, Misc::uuid("{5ccaf4cc-1e9e-11e0-b280-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ANABOLIC_SYNTHESIS, Misc::uuid("{5cf471f8-1e9e-11e0-ad8d-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BURROWING, Misc::uuid("{5d17d9fe-1e9e-11e0-8c0c-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPAWN_BROODLING, Misc::uuid("{5d432d70-1e9e-11e0-9fa0-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PLAGUE, Misc::uuid("{5d6e84fc-1e9e-11e0-a1ba-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CONSUME, Misc::uuid("{5d9b11b6-1e9e-11e0-9d95-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ENSNARE, Misc::uuid("{5dc97128-1e9e-11e0-9a49-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LURKER_ASPECT, Misc::uuid("{5df12b78-1e9e-11e0-aec9-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CARAPACE_1, Misc::uuid("{5e134e6a-1e9e-11e0-84fa-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CARAPACE_2, Misc::uuid("{ae3cd744-1e9e-11e0-bcd2-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CARAPACE_3, Misc::uuid("{af170d06-1e9e-11e0-8c6f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLYER_CARAPACE_1, Misc::uuid("{af5b6898-1e9e-11e0-bbef-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLYER_CARAPACE_2, Misc::uuid("{af900dbe-1e9e-11e0-aa1f-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLYER_CARAPACE_3, Misc::uuid("{afbd1516-1e9e-11e0-b1b6-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MELEE_ATTACKS_1, Misc::uuid("{afeeb7c4-1e9e-11e0-adf2-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MELEE_ATTACKS_2, Misc::uuid("{b01b3178-1e9e-11e0-a50e-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MELEE_ATTACKS_3, Misc::uuid("{b048f838-1e9e-11e0-9884-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MISSILE_ATTACKS_1, Misc::uuid("{b076b2b4-1e9e-11e0-ab7c-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MISSILE_ATTACKS_2, Misc::uuid("{b0a5c810-1e9e-11e0-af91-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(MISSILE_ATTACKS_3, Misc::uuid("{b0d56fde-1e9e-11e0-a6d8-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLYER_ATTACKS_1, Misc::uuid("{b105906a-1e9e-11e0-8546-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLYER_ATTACKS_2, Misc::uuid("{b1383c36-1e9e-11e0-8375-0025d338d400}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FLYER_ATTACKS_3, Misc::uuid("{b16c1aa6-1e9e-11e0-bd55-0025d338d400}")));*/
	return unitMap;
}


const std::list<boost::shared_ptr<const UnitType> > StarCraft2::init_unittypelist_helper() {
	std::list<boost::shared_ptr<const UnitType> > unitTypeList;
	

	
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NONE], "None", neutralRace)));
	/*unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LOCATION_PRIORITY], "Set priority", neutralRace))); // TODO set priority
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
	// TODO optimize!


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GAS], "Gas", neutralRace, 
		boost::assign::list_of
			(UnitResourceType(RESOURCE_RESOURCES, 1, boost::assign::list_of
			(boost::assign::list_of(unit_id_map[REFINERY])(unit_id_map[GAS_SCV])(unit_id_map[COMMAND_CENTER])) 
			(boost::assign::list_of(unit_id_map[ASSIMILATOR])(unit_id_map[GAS_PROBE])(unit_id_map[NEXUS]))
			(boost::assign::list_of(unit_id_map[EXTRACTOR])(unit_id_map[GAS_DRONE])(unit_id_map[HATCHERY])) 
			(boost::assign::list_of(unit_id_map[EXTRACTOR])(unit_id_map[GAS_DRONE])(unit_id_map[LAIR])) 
			(boost::assign::list_of(unit_id_map[EXTRACTOR])(unit_id_map[GAS_DRONE])(unit_id_map[HIVE])) 
		))
		)));

	// TODO all combinations!	

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MINERAL_PATCH], "Mineral Patch", neutralRace,

		boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[SCV])(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[PROBE])(unit_id_map[NEXUS]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[HATCHERY]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[LAIR]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[HIVE]))))
		(UnitResourceType::NOT_BUILDABLE_TYPE)		
		)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEPLETED_MINERAL_PATCH], "Depleted Mineral Patch", neutralRace,

		boost::assign::list_of
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[SCV])(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[PROBE])(unit_id_map[NEXUS]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[HATCHERY]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[LAIR]))))
		(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[HIVE]))))
		(UnitResourceType::NOT_BUILDABLE_TYPE)		
		)));
			
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VESPENE_GEYSIR], "Vespene Geysir", neutralRace)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEPLETED_VESPENE_GEYSIR], "Depleted Vespene Geysir", neutralRace)));


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[TERRAN_SUPPLY], "Terran Supply", terraRace, 
		boost::assign::list_of
			(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER])(unit_id_map[SUPPLY_DEPOT]))))
			(UnitResourceType::NOT_BUILDABLE_TYPE),
		false, 200
		)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PROTOSS_SUPPLY], "Protoss Supply", protossRace, 
		boost::assign::list_of
			(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[NEXUS])(unit_id_map[PYLON]))))
			(UnitResourceType::NOT_BUILDABLE_TYPE),
		false, 200
		)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ZERG_SUPPLY], "Zerg Supply", zergRace, 
		boost::assign::list_of
			(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[OVERLORD])(unit_id_map[HATCHERY])(unit_id_map[LAIR])(unit_id_map[HIVE]))))
			(UnitResourceType::NOT_BUILDABLE_TYPE),
		false, 200
		)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCV_FROM_GAS_TO_MINERALS], "Move Gas SCV to Minerals", terraRace))); // TODO
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PROBE_FROM_GAS_TO_MINERALS], "Move Gas Probe to Minerals", protossRace)));
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DRONE_FROM_GAS_TO_MINERALS], "Move Gas Drone to Minerals", zergRace)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCV], "SCV", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))

		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[MINERAL_PATCH])(unit_id_map[COMMAND_CENTER]))
																	   (boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DEPLETED_MINERAL_PATCH])(unit_id_map[COMMAND_CENTER])) // TODO evtl eigenes "DEPELETED_GATHERER_RESOURCES"
		)),
		true, 0, 300, GROUND_MOVEMENT_TYPE, 120, 120
		))); // TODO all combinations?


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GAS_SCV], "Gas SCV", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
//		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))) TODO?
		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])(unit_id_map[REFINERY])(unit_id_map[COMMAND_CENTER]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[DEPLETED_REFINERY])(unit_id_map[COMMAND_CENTER]))
		)),
		true, 0, 10, GROUND_MOVEMENT_TYPE, 120, 120
		))); // TODO all combinations?

	
		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SPACE_MARINE], "Space Marine", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
		true, 0, 360, GROUND_MOVEMENT_TYPE, 100, 140	
		)));



// idea: Like the siege tank *morph* units into different attack modes

		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GHOST], "Ghost", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_CO]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 25, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 100, 100)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VULTURE], "Vulture", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 450, GROUND_MOVEMENT_TYPE, 155, 225)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GOLIATH], "Goliath", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 600, GROUND_MOVEMENT_TYPE, 112, 112)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SIEGE_TANK], "Siege Tank", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY_MS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 98, 98)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FIREBAT], "Firebat", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 25, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 360, GROUND_MOVEMENT_TYPE, 100, 140)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MEDIC], "Medic", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 25, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 450, GROUND_MOVEMENT_TYPE, 100, 100)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[WRAITH], "Wraith", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 900, GROUND_MOVEMENT_TYPE, 160, 160)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCIENCE_VESSEL], "Science Vessel", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 1200, GROUND_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DROPSHIP], "Dropship", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 131, 131)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[BATTLE_CRUISER], "Battle Cruiser", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_PL]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 6, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 2000, GROUND_MOVEMENT_TYPE, 60, 60)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VALKYRIE], "Valkyrie", terraRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 125, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 3, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 158, 158)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NUCLEAR_WARHEAD], "Nuclear Warhead", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[NUCLEAR_SILO]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER_NS]))))
		// (UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER])))) // TODO?
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(NEED_GLOBAL_SUPPLY_RESOURCE, 8, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),
			
		true, 0, 1500, eUnitMovementType::FLYING_MOVEMENT_TYPE, 10000, 10000))); // TODO...

			
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[REFINERY], "Refinery", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[VESPENE_GEYSIR])))),
		
		true, 0, 600
		)));

		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEPLETED_REFINERY], "Depleted Refinery", terraRace,
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEPLETED_VESPENE_GEYSIR])))),
		
		true, 0, 600
		)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[COMMAND_CENTER], "Command Center", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, 10, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY]))))

		(UnitResourceType(ACCEPTER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[TERRAN_SUPPLY])(unit_id_map[SCV]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_COMMAND_CENTER_ADDON])))),

		true, 0, 1800
		))); // TODO later: also gas etc.



	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SUPPLY_DEPOT], "Supply Depot", terraRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(PRODUCE_SUPPLY_RESOURCE, 8, boost::assign::list_of(boost::assign::list_of(unit_id_map[TERRAN_SUPPLY])))),		
		true, 0, 600
		)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[BARRACKS], "Barracks", terraRace,
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),
		true, 0, 1200
		)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ACADEMY], "Academy", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FACTORY], "Factory", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_FACTORY_ADDON])))),
			
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[STARPORT], "Starport", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_STARPORT_ADDON])))),
		
			true, 0, 1050)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCIENCE_FACILITY], "Science Facility", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_SCIENCE_FACILITY_ADDON])))),
			
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ENGINEERING_BAY], "Engineering Bay", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 125, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),
			
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARMORY], "Armory", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),
			
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MISSILE_TURRET], "Missile Turret", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),
			
			true, 0, 450)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[BUNKER], "Bunker", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[BARRACKS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCV]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),
			
			true, 0, 450)));



		// individual buildings cannot be build, only a combination of e.g. CC and CS can be build -> CC [CS]
		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[COMSAT_STATION], "Comsat Station", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_COMMAND_CENTER_ADDON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER_CS])))),
			
			true, 0, 600)));




		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NUCLEAR_SILO], "Nuclear Silo", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_PL]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER]))))
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_COMMAND_CENTER_ADDON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER_NS])))),
			
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CONTROL_TOWER], "Control Tower", terraRace, 	
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT]))))
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_STARPORT_ADDON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT])))),			
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[COVERT_OPS], "Covert Ops", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_SCIENCE_FACILITY_ADDON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_CO])))),
			
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PHYSICS_LAB], "Physics Lab", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_SCIENCE_FACILITY_ADDON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_PL])))),
			
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MACHINE_SHOP], "Machine Shop", terraRace, 
					boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY]))))
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[F_FACTORY_ADDON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS]))))
		(UnitResourceType(UNIT_CREATE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY_MS])))),
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[COMMAND_CENTER_CS], "Command Center [CS]", terraRace, 
			boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
			true)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[COMMAND_CENTER_NS], "Command Center [NS]", terraRace, 
			boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
			true)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[STARPORT_CT], "Starport [CT]", terraRace, 
			boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
			true)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCIENCE_FACILITY_CO], "Science Facility [CO]", terraRace, 
			boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
			true)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCIENCE_FACILITY_PL], "Science Facility [PL]", terraRace, 
			boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
			true)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FACTORY_MS], "Factory [MS]", terraRace, 
			boost::assign::list_of(UnitResourceType::NOT_BUILDABLE_TYPE),
			true)));

		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[F_FACTORY_ADDON], "Available Factory Addon", terraRace)));
		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[F_STARPORT_ADDON], "Available Starport Addon", terraRace)));
		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[F_COMMAND_CENTER_ADDON], "Available Command Center Addon", terraRace)));
		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[F_SCIENCE_FACILITY_ADDON], "Available Science Facility Addon", terraRace)));

		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[STIM_PACKS], "Stim Packs", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),			
			false, 1, 1200))); // max 1 research


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LOCKDOWN], "Lockdown", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_CO]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COVERT_OPS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[EMP_SHOCKWAVE], "EMP Shockwave", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SPIDER_MINES], "Spider Mines", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY_MS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MACHINE_SHOP]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[TANK_SIEGE_MODE], "Tank Siege Mode", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY_MS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MACHINE_SHOP]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[IRRADIATE], "Irradiate", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[YAMATO_GUN], "Yamato Gun", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_PL]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PHYSICS_LAB]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CLOAKING_FIELD], "Cloaking Field", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CONTROL_TOWER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PERSONNEL_CLOAKING], "Personnel Cloaking", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_CO]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COVERT_OPS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[RESTORATION], "Restoration", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[OPTICAL_FLARE], "Optical Flare", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[U238_SHELLS], "U238 Shells", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ION_THRUSTERS], "Ion Thrusters", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY_MS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MACHINE_SHOP]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[TITAN_REACTOR], "Titan Reactor", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[OCULAR_IMPLANTS], "Ocular Implants", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_CO]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COVERT_OPS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MOEBIUS_REACTOR], "Moebius Reactor", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_CO]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COVERT_OPS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[APOLLO_REACTOR], "Apollo Reactor", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARPORT_CT]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CONTROL_TOWER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[COLOSSUS_REACTOR], "Colossus Reactor", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY_PL]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PHYSICS_LAB]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CADUCEUS_REACTOR], "Caduceus Reactor", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ACADEMY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CHARON_BOOSTER], "Charon Booster", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FACTORY_MS]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MACHINE_SHOP]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[INFANTRY_ARMOR_1], "Infantry Armor 1", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[INFANTRY_ARMOR_2], "Infantry Armor 2", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[INFANTRY_ARMOR_3], "Infantry Armor 3", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[INFANTRY_WEAPONS_1], "Infantry Weapons 1", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[INFANTRY_WEAPONS_2], "Infantry Weapons 2", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[INFANTRY_WEAPONS_3], "Infantry Weapons 3", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ENGINEERING_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VEHICLE_PLATING_1], "Vehicle Plating 1", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VEHICLE_PLATING_2], "Vehicle Plating 2", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VEHICLE_PLATING_3], "Vehicle Plating 3", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VEHICLE_WEAPONS_1], "Vehicle Weapons 1", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VEHICLE_WEAPONS_2], "Vehicle Weapons 2", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VEHICLE_WEAPONS_3], "Vehicle Weapons 3", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIP_PLATING_1], "Ship Plating 1", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIP_PLATING_2], "Ship Plating 2", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIP_PLATING_3], "Ship Plating 3", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIP_WEAPONS_1], "Ship Weapons 1", terraRace, 
			boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIP_WEAPONS_2], "Ship Weapons 2", terraRace,
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIP_WEAPONS_3], "Ship Weapons 3", terraRace, 
			boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SCIENCE_FACILITY]))))
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARMORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 5000)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PROBE], "Probe", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[NEXUS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),		
			
			true, 0, 300, GROUND_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GAS_PROBE], "Gas Probe", protossRace, 

		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])(unit_id_map[ASSIMILATOR])(unit_id_map[NEXUS]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[DEPLETED_ASSIMILATOR])(unit_id_map[NEXUS])))),
			true, 0, 15, GROUND_MOVEMENT_TYPE, 120, 120)));
		

		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DARK_TEMPLAR], "Dark Templar", protossRace, 
		boost::assign::list_of					
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 125, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DARK_ARCHON], "Dark Archon", protossRace, 		
		boost::assign::list_of						
			(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[DARK_TEMPLAR])))),
			true, 0, 300, GROUND_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ZEALOT], "Zealot", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			
			true, 0, 600, GROUND_MOVEMENT_TYPE, 96, 140)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DRAGOON], "Dragoon", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))

		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 125, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 126, 126)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HIGH_TEMPLAR], "High Templar", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 750, GROUND_MOVEMENT_TYPE, 78, 78)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARCHON], "Archon", protossRace, 			
		boost::assign::list_of						
			(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 2, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIGH_TEMPLAR])))),
			true, 0, 300, GROUND_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[REAVER], "Reaver", protossRace, 
		boost::assign::list_of			
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 1050, GROUND_MOVEMENT_TYPE, 44, 44)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HALF_SCARAB], "Half Scarab", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),				
			
			true, 0, 525)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FULL_SCARAB], "Full Scarab", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),				
			
			true, 0, 525)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CORSAIR], "Corsair", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 600, FLYING_MOVEMENT_TYPE, 160, 60)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHUTTLE], "Shuttle", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			
			true, 0, 900, FLYING_MOVEMENT_TYPE, 106, 160))); // TODO 160 unknown


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCOUT], "Scout", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 275, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 125, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 1200, FLYING_MOVEMENT_TYPE, 120, 160))); // TODO 160 unknown


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARBITER], "Arbiter", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 2400, FLYING_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CARRIER], "Carrier", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 350, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 2100, FLYING_MOVEMENT_TYPE, 80, 80)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HALF_INTERCEPTOR], "Half Interceptor", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			true, 0, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FULL_INTERCEPTOR], "Full Interceptor", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),				
			
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[OBSERVER], "Observer", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 25, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 600, FLYING_MOVEMENT_TYPE, 80, 120))); // TODO 120 unknown


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ASSIMILATOR], "Assimilator", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[VESPENE_GEYSIR]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),
			
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEPLETED_ASSIMILATOR], "Depleted Assimilator", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEPLETED_VESPENE_GEYSIR]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NEXUS], "Nexus", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),				
			
			true, 0, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ROBOTICS_FACILITY], "Robotics Facility", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PYLON], "Pylon", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			
			true, 0, 450)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[OBSERVATORY], "Observatory", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ROBOTICS_FACILITY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			
			true, 0, 450)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GATEWAY], "Gateway", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[NEXUS]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PHOTON_CANNON], "Photon Cannon", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
			
			true, 0, 750)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CYBERNETICS_CORE], "Cybernetics Core", protossRace,
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),		
			
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CITADEL_OF_ADUN], "Citatel of Adun", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
				true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[TEMPLAR_ARCHIVES], "Templar Archives", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CITADEL_OF_ADUN]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FORGE], "Forge", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[NEXUS]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[STARGATE], "Stargate", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 1050)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLEET_BEACON], "Fleet Beacon", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARGATE]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARBITER_TRIBUNAL], "Arbiter Tribunal", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[STARGATE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ROBOTICS_SUPPORT_BAY], "Robotics Support Bay", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ROBOTICS_FACILITY]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 450)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SHIELD_BATTERY], "Shield Battery", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GATEWAY]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PROBE]))))
		(UnitResourceType(LOCAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[PYLON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 450)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PSIONIC_STORM], "Psionic Storm", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HALLUCINATION], "Hallucination", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[RECALL], "Recall", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARBITER_TRIBUNAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[STASIS_FIELD], "Stasis Field", protossRace, 
		boost::assign::list_of		
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARBITER_TRIBUNAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DISRUPTION_WEB], "Disruption Web", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MIND_CONTROL], "Mind Control", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MAELSTROM], "Maelstrom", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SINGULARITY_CHARGE], "Singularity Charge", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LEG_ENHANCEMENTS], "Leg Enhancements", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CITADEL_OF_ADUN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCARAB_DAMAGE], "Scarab Damage", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ROBOTICS_SUPPORT_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[REAVER_CAPACITY], "Reaver Capacity", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ROBOTICS_SUPPORT_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GRAVITIC_DRIVE], "Gravitic Drive", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ROBOTICS_SUPPORT_BAY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SENSOR_ARRAY], "Sensor Array", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[OBSERVATORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GRAVITIC_BOOSTERS], "Gravitic Boosters", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[OBSERVATORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[KHAYDARIN_AMULET], "Khaydarin Amulet", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[APIAL_SENSORS], "Apial Sensors", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GRAVITIC_THRUSTERS], "Gravitic Thrusters", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[OBSERVATORY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CARRIER_CAPACITY], "Carrier Capacity", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[KHAYDARIN_CORE], "Khaydarin Core", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ARBITER_TRIBUNAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARGUS_JEWEL], "Argus Jewel", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARGUS_TALISMAN], "Argus Talisman", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARMOR_1], "Armor 1", protossRace, 
		boost::assign::list_of			
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARMOR_2], "Armor 2", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ARMOR_3], "Armor 3", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLATING_1], "Plating 1", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLATING_2], "Plating 2", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLATING_3], "Plating 3", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GROUND_WEAPONS_1], "Ground Weapons 1", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GROUND_WEAPONS_2], "Ground Weapons 2", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GROUND_WEAPONS_3], "Ground Weapons 3", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[AIR_WEAPONS_1], "Air Weapons 1", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[AIR_WEAPONS_2], "Air Weapons 2", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[AIR_WEAPONS_3], "Air Weapons 3", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CYBERNETICS_CORE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLEET_BEACON]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLASMA_SHIELDS_1], "Plasma Shields 1", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLASMA_SHIELDS_2], "Plasma Shields 2", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLASMA_SHIELDS_3], "Plasma Shields 3", protossRace, 
		boost::assign::list_of						
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FORGE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[TEMPLAR_ARCHIVES]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 400, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));





		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DRONE], "Drone", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 300, GROUND_MOVEMENT_TYPE, 120, 120)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GAS_DRONE], "Gas Drone", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))			
		(UnitResourceType(GATHERER_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])(unit_id_map[EXTRACTOR])(unit_id_map[HATCHERY]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[DEPLETED_EXTRACTOR])(unit_id_map[HATCHERY]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[EXTRACTOR])(unit_id_map[LAIR]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[DEPLETED_EXTRACTOR])(unit_id_map[LAIR]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[EXTRACTOR])(unit_id_map[HIVE]))
																	   (boost::assign::list_of(unit_id_map[GAS])(unit_id_map[DEPLETED_EXTRACTOR])(unit_id_map[HIVE]))
																	 )),
			true, 0, 15, GROUND_MOVEMENT_TYPE, 120, 120)));


		

		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LARVA], "Larva", zergRace, 
			boost::assign::list_of
			(UnitResourceType::NOT_BUILDABLE_TYPE),
			true, 0, 300)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ZERGLING], "Zergling", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPAWNING_POOL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 420, GROUND_MOVEMENT_TYPE, 133, 194)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HYDRALISK], "Hydralisk", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HYDRALISK_DEN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 25, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 420, GROUND_MOVEMENT_TYPE, 90, 133)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ULTRALISK], "Ultralisk", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ULTRALISK_CAVERN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 900, GROUND_MOVEMENT_TYPE, 126, 187)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEFILER], "Defiler", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEFILER_MOUND]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 750, GROUND_MOVEMENT_TYPE, 100, 100)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LURKER], "Lurker", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HYDRALISK]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LURKER_ASPECT]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 600, GROUND_MOVEMENT_TYPE, 144, 144)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[OVERLORD], "Overlord", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 600, FLYING_MOVEMENT_TYPE, 20, 100))); // TODO speed?


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MUTALISK], "Mutalisk", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 600, FLYING_MOVEMENT_TYPE, 160, 160)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GUARDIEN], "Guardien", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MUTALISK]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 600, FLYING_MOVEMENT_TYPE, 60, 60)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[QUEEN], "Queen", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[QUEENS_NEST]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 750, FLYING_MOVEMENT_TYPE, 160, 160)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SCOURGE], "Scourge", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LARVA]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 25, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 450, FLYING_MOVEMENT_TYPE, 160, 160)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEVOURER], "Devourer", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MUTALISK]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 600, FLYING_MOVEMENT_TYPE, 120, 120)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[EXTRACTOR], "Extractor", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[VESPENE_GEYSIR]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),		
						
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEPLETED_EXTRACTOR], "Depleted Extractor", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEPLETED_VESPENE_GEYSIR]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),				
						
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HATCHERY], "Hatchery", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),		
						
			true, 0, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LAIR], "Lair", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HATCHERY]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPAWNING_POOL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HIVE], "Hive", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NYDUS_CANAL], "Nydus Canal", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HYDRALISK_DEN], "Hydralisk Den", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[DEFILER_MOUND], "Defiler Mound", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GREATER_SPIRE], "Greater Spire", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[QUEENS_NEST], "Queen's Nest", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 900)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[EVOLUTION_CHAMBER], "Evolution Chamber", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 600)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ULTRALISK_CAVERN], "Ultralisk Cavern", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SPIRE], "Spire", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			true, 0, 1800)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SPAWNING_POOL], "Spawning Pool", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CREEP_COLONY], "Creep Colony", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_LOST_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DRONE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 300)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SPORE_COLONY], "Spore Colony", zergRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CREEP_COLONY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 75, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 300)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SUNKEN_COLONY], "Sunken Colony", zergRace, 
		boost::assign::list_of
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPAWNING_POOL]))))
		(UnitResourceType(FACILITY_IS_MORPHING_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CREEP_COLONY]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 50, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])))),			
						
			true, 0, 300)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[VENTRAL_SACKS], "Ventral Sacks", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2400)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ANTENNAE], "Antennae", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PNEUMATIZED_CARAPACE], "Pneumatized Carapace", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[METABOLIC_BOOST], "Metabolic Boost", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPAWNING_POOL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ADRENAL_GLANDS], "Adrenal Glands", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPAWNING_POOL]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MUSCULAR_AUGMENTS], "Muscular Augments", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HYDRALISK_DEN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GROOVED_SPINES], "Grooved Spines", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HYDRALISK_DEN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GAMETE_MEIOSIS], "Gamete Meiosis", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[QUEENS_NEST]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[METASYNAPTIC_NODE], "Metasynaptic Node", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEFILER_MOUND]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CHITINOUS_PLATING], "Chitinous Plating", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ULTRALISK_CAVERN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ANABOLIC_SYNTHESIS], "Anabolic Synthesis", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[ULTRALISK_CAVERN]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 2000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[BURROWING], "Burrowing", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HATCHERY])(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[SPAWN_BROODLING], "Spawn Broodling", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[QUEENS_NEST]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PLAGUE], "Plague", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEFILER_MOUND]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CONSUME], "Consume", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[DEFILER_MOUND]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ENSNARE], "Ensnare", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[QUEENS_NEST]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1200)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LURKER_ASPECT], "Lurker Aspect", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HYDRALISK_DEN]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 1800)));



		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CARAPACE_1], "Carapace 1", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),		
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CARAPACE_2], "Carapace 2", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CARAPACE_1]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[CARAPACE_3], "Carapace 3", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[CARAPACE_2]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLYER_CARAPACE_1], "Flyer Carapace 1", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE])(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLYER_CARAPACE_2], "Flyer Carapace 2", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE])(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLYER_CARAPACE_1]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 225, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLYER_CARAPACE_3], "Flyer Carapace 3", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE])(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLYER_CARAPACE_2]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 300, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MELEE_ATTACKS_1], "Melee Attacks 1", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MELEE_ATTACKS_2], "Melee Attacks 2", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MELEE_ATTACKS_1]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MELEE_ATTACKS_3], "Melee Attacks 3", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MELEE_ATTACKS_2]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MISSILE_ATTACKS_1], "Missile Attacks 1", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MISSILE_ATTACKS_2], "Missile Attacks 2", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MISSILE_ATTACKS_1]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 150, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[MISSILE_ATTACKS_3], "Missile Attacks 3", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[EVOLUTION_CHAMBER]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MISSILE_ATTACKS_2]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 200, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLYER_ATTACKS_1], "Flyer Attacks 1", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE])(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 100, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4000)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLYER_ATTACKS_2], "Flyer Attacks 2", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE])(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[LAIR])(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLYER_ATTACKS_1]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 175, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 4500)));


		unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[FLYER_ATTACKS_3], "Flyer Attacks 3", zergRace, 
		boost::assign::list_of
		(UnitResourceType(FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[SPIRE])(unit_id_map[GREATER_SPIRE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[HIVE]))))
		(UnitResourceType(GLOBAL_PREREQUISITE_RESOURCE, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[FLYER_ATTACKS_2]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL]))))
		(UnitResourceType(NORMAL_GLOBAL_RESOURCE, 250, boost::assign::list_of(boost::assign::list_of(unit_id_map[GAS])))),				
						
			false, 1, 5000)));

			*/


	return unitTypeList;
}
