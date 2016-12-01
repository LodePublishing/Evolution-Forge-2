#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include "warcraft.hpp"
#include "enums/warcraftraces.hpp"
#include "enums/warcraftunits.hpp"

#include <misc/miscellaneous.hpp>

WarCraft::WarCraft():
	GameData(init_raceidmap_helper(), init_unitidmap_helper()),
	neutralRace(boost::shared_ptr<const Race>(new Race(race_id_map[NEUTRAL_RACE], "Neutral"))),
	humanRace(boost::shared_ptr<const Race>(new Race(race_id_map[HUMAN_RACE], "Human"))),
	orcRace(boost::shared_ptr<const Race>(new Race(race_id_map[ORC_RACE], "Orc")))
{ 	
	rules = boost::shared_ptr<const Rules>(new Rules(Misc::uuid("{20651090-3194-11e0-91fa-0800200c9a66}"), "WarCraft", init_racelist_helper(), init_unittypelist_helper()));
	initRules();	
}

WarCraft::~WarCraft()
{ }

const std::list<boost::shared_ptr<const Race> > WarCraft::init_racelist_helper() const {
	std::list<boost::shared_ptr<const Race> > raceList;

	raceList.push_back(neutralRace);
	raceList.push_back(humanRace);
	raceList.push_back(orcRace);

	return raceList;
}


const std::map<const unsigned int, const boost::uuids::uuid> WarCraft::init_raceidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> raceIdMap;

	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NEUTRAL_RACE, Misc::uuid("{af54caa0-3196-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_RACE, Misc::uuid("{bc862c00-3196-11e0-91fa-0800200c9a66}")));
	raceIdMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_RACE, Misc::uuid("{bfd07500-3196-11e0-91fa-0800200c9a66}")));

	return raceIdMap;
}

const std::map<const unsigned int, const boost::uuids::uuid> WarCraft::init_unitidmap_helper() const {
	std::map<const unsigned int, const boost::uuids::uuid> unitMap;

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NONE, Misc::uuid("{d3f55b20-2199-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(LOCATION_PRIORITY, Misc::uuid("{d8b77710-2199-11e0-ac64-0800200c9a66}"))); 
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WAIT, Misc::uuid("{dbc09860-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BREAK_UP_BUILDING, Misc::uuid("{de6e7a50-2199-11e0-ac64-0800200c9a66}")));


	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GOLD, Misc::uuid("{e17db620-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WOOD, Misc::uuid("{e3dc8db0-2199-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GOLDMINE, Misc::uuid("{e686c620-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TREE, Misc::uuid("{e8c62ed0-2199-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_SUPPLY, Misc::uuid("{eb880df0-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_SUPPLY, Misc::uuid("{ee368c20-2199-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PEASANT_FROM_TREES_TO_GOLDMINE, Misc::uuid("{f16054d0-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PEON_FROM_TREES_TO_GOLDMINE, Misc::uuid("{f3dee960-2199-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PEASANT, Misc::uuid("{f67f5dd0-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TREE_PEASANT, Misc::uuid("{f8fae520-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FOOTMAN, Misc::uuid("{fc871920-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HEAVY_CATAPULT, Misc::uuid("{ffe75b20-2199-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(KNIGHT, Misc::uuid("{02b3e8a0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARCHER, Misc::uuid("{05a27d10-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CONJURER, Misc::uuid("{085f2c10-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CLERIC, Misc::uuid("{0b394e20-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SCORPION, Misc::uuid("{0e3920a0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FIRE_ELEMENTAL, Misc::uuid("{10d416d0-219a-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_FARM, Misc::uuid("{13f6b390-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_TOWNHALL, Misc::uuid("{17083950-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_BARRACKS, Misc::uuid("{196451c0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_LUMBERMILL, Misc::uuid("{1ba42fa0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_BLACKSMITH, Misc::uuid("{1e3cdbe0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_STABLES, Misc::uuid("{2268d250-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_CHURCH, Misc::uuid("{24e80320-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_TOWER, Misc::uuid("{27036910-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_CASTLE, Misc::uuid("{294a72e0-219a-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HEALING, Misc::uuid("{2b901d20-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(FAR_SEEING, Misc::uuid("{2df5f990-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(INVISIBILITY, Misc::uuid("{30250e90-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SUMMON_SCORPIONS, Misc::uuid("{322d3aa0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(RAIN_OF_FIRE, Misc::uuid("{35019050-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SUMMON_ELEMENTAL, Misc::uuid("{3821bc10-219a-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_SHIELDS_1, Misc::uuid("{3a6b0fd0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HUMAN_SHIELDS_2, Misc::uuid("{3cdfb950-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARROWS_1, Misc::uuid("{3f87a7d0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ARROWS_2, Misc::uuid("{41ca44d0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SWORDS_1, Misc::uuid("{43e0efd0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SWORDS_2, Misc::uuid("{46367890-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HORSES_1, Misc::uuid("{48a4b970-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(HORSES_2, Misc::uuid("{4adb6f90-219a-11e0-ac64-0800200c9a66}")));


	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(PEON, Misc::uuid("{4d4a9ad0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(TREE_PEON, Misc::uuid("{4f8b6310-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(GRUNT, Misc::uuid("{517028a0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_CATAPULT, Misc::uuid("{549361a0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(RAIDER, Misc::uuid("{57c95f50-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPEARMAN, Misc::uuid("{5a45f810-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WARLOCK, Misc::uuid("{5cf22c50-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(NECROLYTE, Misc::uuid("{5f34c950-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPIDER, Misc::uuid("{61926860-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DAEMON, Misc::uuid("{639452e0-219a-11e0-ac64-0800200c9a66}")));


	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_FARM, Misc::uuid("{68e4cc20-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_TOWNHALL, Misc::uuid("{6af55ca0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_BARRACKS, Misc::uuid("{6d177950-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_LUMBERMILL, Misc::uuid("{6f3f6260-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_BLACKSMITH, Misc::uuid("{71c59810-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_KENNELS, Misc::uuid("{73f178c0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_TEMPLE, Misc::uuid("{770632d0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_TOWER, Misc::uuid("{79a12900-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_CASTLE, Misc::uuid("{7bdac550-219a-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(RAISE_DEAD, Misc::uuid("{7e12b3f0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DARK_VISION, Misc::uuid("{80472020-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(UNHOLY_ARMOUR, Misc::uuid("{82634960-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SUMMON_SPIDERS, Misc::uuid("{849851d0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(CLOUD_OF_POISON, Misc::uuid("{86e500f0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SUMMON_DAEMON, Misc::uuid("{892701b0-219a-11e0-ac64-0800200c9a66}")));

	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_SHIELDS_1, Misc::uuid("{8b89a9d0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_SHIELDS_2, Misc::uuid("{8daab510-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPEARS_1, Misc::uuid("{8fff0550-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SPEARS_2, Misc::uuid("{929e8f60-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(AXES_1, Misc::uuid("{9598bc90-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(AXES_2, Misc::uuid("{97f3c390-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WOLVES_1, Misc::uuid("{9a11e8a0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WOLVES_2, Misc::uuid("{9c71d1a0-219a-11e0-ac64-0800200c9a66}")));


	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(OGRE, Misc::uuid("{9e8dd3d0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(SLIME, Misc::uuid("{a0a987e0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(BRIGAND, Misc::uuid("{a2fc0360-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(ORC_SKELETON, Misc::uuid("{a55c88a0-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(DUNGEON_SCELETON, Misc::uuid("{a8058890-219a-11e0-ac64-0800200c9a66}")));
	unitMap.insert(std::pair<const unsigned int, const boost::uuids::uuid>(WATER_ELEMENTAL, Misc::uuid("{aa4d0790-219a-11e0-ac64-0800200c9a66}")));



	return unitMap;
}


const std::list<boost::shared_ptr<const UnitType> > WarCraft::init_unittypelist_helper() {
	std::list<boost::shared_ptr<const UnitType> > unitTypeList;

	/*

	#   -=6-1=-  Unit Statistics

	#   -=6-1-1=-  Human unit statistics

	Unit      Attack  Armour  Hit  Minimum  Random   Time  Gold  Lumber  
	Range  Points  Pts   Damage  Damage  Train  Cost    Cost  

	Footman       --       2   60        1       9    600   400      --  
	Peasant       --       0   40       --      --    750   400      --  
	H Catapult     8       0  120       --     255   1000   900     200  
	Knight        --       5   90        1      13    800   850      --     
	Archer         5       1   60        4       0    700   450      50     
	Conjurer       3       0   40        6       0    900   900       0     
	Cleric         1       0   40        6       0    800   700       0     

	#   -=6-1-2=-  Orc unit statistics

	Unit      Attack  Armour  Hit  Minimum  Random   Time  Gold  Lumber   
	Range  Points  Pts   Damage  Damage  Train  Cost    Cost   
	Grunt         --       2   60        1       9    600   400      --     
	Peon          --       0   40       --      --    750   400      --     
	O Catapult     8       0  120       --     255   1000   900     200     
	Raider        --       5   90        1      13    800   850      --     
	Spearman       4       1   60        5       0    700   450      50     
	Warlock        2       0   40        6       0    900   900       0     
	Necrolyte      2       0   40        6       0    800   700       0     

	#   -=6-1-3=-  Creature unit statistics

	Unit              Attack  Armour  Hit  Minimum  Random   Decay
	Range  Points  Pts   Damage  Damage    Rate
	Ogre                  --       0   60        1      12      --
	Spider                --       0   30        1       3      45
	Slime                 --      10  150        1       0      --
	Fire Elemental        --       0  200        0      40      --
	Scorpion              --       0   30        3       0      45
	Brigand               --       4   40        1       9      --
	Orc Skeleton          --       1   40        1       4      45
	Dungeon Skeleton      --       2   30        1       9      --
	Daemon                --       0  300        0      65      45
	Water Elemental        3       0  250       40       0      45

	#   -=6-2=-  Building Statistics

	Building             Hit     Time    Gold   Lumber
	Pts    Build    Cost     Cost
	Farm                 400     1000     500      300
	Townhall            2500     1000     400      400
	Barracks             800     1500     600      500
	Lumbermill           600     1500     600      500
	Blacksmith           800     1500     900      400
	Stables/Kennels      500     1500    1000      400
	Church/Temple        700     2000     800      500
	Tower                900     2000    1400      300
	Castle              5000       --      --       --
	Goldmine           25500       --      --       --

	#   -=6-3=-  Spell Statistics

	Spell               Research    Research    Spell
	Cost        Time    Range
	Healing                  750         120        8
	Far seeing              1500         120       --
	Invisiblity             3000         120        8
	Minor summoning          750         140       --
	Rain of fire            1500         140        9
	Major summoning         3000         140       --
	Raise dead               750         120        5
	Dark vision             1500         120       --
	Unholy armour           3000         120        8
	Cloud of poison         1500         140        9

	#   -=6-4=-  Technology Statistics

	Technology             1st Upgrade   2nd Upgrade   Research
	Gold Cost     Gold Cost       Time
	Shields                        750          1500        120
	Arrows/spears                  750          1500        140
	Swords/axes                    750          1500        120
	Horses/wolves                  750          1500        140*/

	/*
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[NONE], "None", neutralRace)));
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[LOCATION_PRIORITY], "Set priority", neutralRace))); // TODO set priority
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[WAIT], "Wait", neutralRace)));	 // TODO wait command
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[BREAK_UP_BUILDING], "Break up building", neutralRace))); // TODO cancel building command



	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GOLD], "Mineral", neutralRace, 
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


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[WOOD], "Gas", neutralRace, 
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

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[GOLDMINE], "Mineral Patch", neutralRace,

	boost::assign::list_of
	(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[SCV])(unit_id_map[COMMAND_CENTER]))))
	(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[PROBE])(unit_id_map[NEXUS]))))
	(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[HATCHERY]))))
	(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[LAIR]))))
	(UnitResourceType(SOURCE_RESOURCES, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[MINERAL])(unit_id_map[DRONE])(unit_id_map[HIVE]))))
	(UnitResourceType::NOT_BUILDABLE_TYPE)		
	)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[TREE], "Vespene Geysir", neutralRace)));


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[HUMAN_SUPPLY], "Terran Supply", terraRace, 
	boost::assign::list_of
	(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[COMMAND_CENTER])(unit_id_map[SUPPLY_DEPOT]))))
	(UnitResourceType::NOT_BUILDABLE_TYPE),
	false, 200
	)));

	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[ORC_SUPPLY], "Protoss Supply", protossRace, 
	boost::assign::list_of
	(UnitResourceType(SUPPLY_PROVIDER, 1, boost::assign::list_of(boost::assign::list_of(unit_id_map[NEXUS])(unit_id_map[PYLON]))))
	(UnitResourceType::NOT_BUILDABLE_TYPE),
	false, 200
	)));


	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PEASANT_FROM_TREES_TO_GOLDMINE], "Move Gas SCV to Minerals", terraRace))); // TODO
	unitTypeList.push_back(boost::shared_ptr<const UnitType>(new UnitType(unit_id_map[PEON_FROM_TREES_TO_GOLDMINE], "Move Gas Probe to Minerals", protossRace)));



	PEASANT, 
	TREE_PEASANT,
	FOOTMAN,
	HEAVY_CATAPULT,
	KNIGHT,
	ARCHER,
	CONJURER,
	CLERIC,
	SCORPION,
	FIRE_ELEMENTAL,

	HUMAN_FARM,
	HUMAN_TOWNHALL,
	HUMAN_BARRACKS,
	HUMAN_LUMBERMILL,
	HUMAN_BLACKSMITH,
	HUMAN_STABLES,
	HUMAN_CHURCH,
	HUMAN_TOWER,
	HUMAN_CASTLE,

	HEALING,
	FAR_SEEING,
	INVISIBILITY,           
	RAIN_OF_FIRE,
	SUMMON_SCORPIONS,
	SUMMON_ELEMENTAL,

	HUMAN_SHIELDS_1,
	HUMAN_SHIELDS_2,
	ARROWS_1,
	ARROWS_2,
	SWORDS_1,
	SWORDS_2,
	HORSES_1,
	HORSES_2,






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



	PEON,
	TREE_PEON,
	GRUNT,
	ORC_CATAPULT,
	RAIDER,
	SPEARMAN,
	WARLOCK,
	NECROLYTE,
	SPIDER,
	DAEMON,

	ORC_FARM,
	ORC_TOWNHALL,
	ORC_BARRACKS,
	ORC_LUMBERMILL,
	ORC_BLACKSMITH,
	ORC_KENNELS,
	ORC_TEMPLE,
	ORC_TOWER,
	ORC_CASTLE,

	RAISE_DEAD,
	DARK_VISION,
	UNHOLY_ARMOUR,
	CLOUD_OF_POISON,
	SUMMON_SPIDERS,
	SUMMON_DAEMON,
	ORC_SHIELDS_1,
	ORC_SHIELDS_2,
	SPEARS_1,
	SPEARS_2,
	AXES_1,
	AXES_2,
	WOLVES_1,
	WOLVES_2,

	OGRE,		
	SLIME,		
	BRIGAND,
	ORC_SKELETON,
	DUNGEON_SCELETON,
	WATER_ELEMENTAL,


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


	*/



	return unitTypeList;
}
