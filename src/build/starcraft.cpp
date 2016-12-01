//TODO: Problem: auf goals muessen sowohl ueber jeweiligen Ort (also gGoal[MAX_LOCATIONS][MAX_GOALS]), als auch einzelne Goals, wenn z.B. nach 5 und 10 Minuten 3 und 5 Marines an einem Ort sein sollen...

#include "starcraft.hpp"
#include <string>

const std::string CORE_VERSION="Beta 1.64";

/*const unsigned int MAX_RACES = 3;
const unsigned int UNIT_TYPE_COUNT = 105;
const unsigned int MAX_LOCATIONS = 20;

const unsigned int MAX_GAME_TABS = 6;
const unsigned int MAX_SIMULTANEOUS_GAMES = 2;
const unsigned int MAX_GAME = MAX_SIMULTANEOUS_GAMES * MAX_GAME_TABS;
const unsigned int MAX_PLAYER = 4;
const unsigned int MAX_INTERNAL_PLAYER = 5;
const unsigned int GLOBAL = 0;*/

//const unsigned int MAX_LOCATIONS = 9;
const unsigned int MIN_LOCATIONS = 0; //this does not mean that maps with 0 locations can exist....

//const unsigned int MAX_PLAYER = 3;
const unsigned int MIN_PLAYER = 1;

//const unsigned int MAX_GOAL_ENTRIES = 25;
const unsigned int MIN_GOAL_ENTRIES = 0;

const unsigned int MAX_MINERALS = 5000000;
const unsigned int MAX_GAS = 5000000;

//const unsigned int MAX_PROGRAMS = 128; //must be multiplier of (16*player)
const unsigned int LARVA_MAX = 200;
//const unsigned int UNIT_TYPE_COUNT = 105;
//const unsigned int MAX_GOALS = 100; // count of possible different goals
//const unsigned int MAX_HARVEST_SPEEDS = 100;
const unsigned int MAX_SUPPLY = 200;

const unsigned int MAX_TOTAL_UNITS = 600; // 600 because larva max is 600... in addition 600 should be low enough to find bugs concerning uninitialized values

const unsigned int MAX_GENERATIONS = 10000;
const unsigned int MIN_GENERATIONS = 100;



//const unsigned int MAX_TIME = 3600;
const unsigned int MIN_TIME = 300;

const unsigned int MAX_TIMEOUT = 266;
const unsigned int MIN_TIMEOUT = 40;



//const unsigned int MAX_LENGTH = 96;
const unsigned int MIN_LENGTH = 32;

//const unsigned int MAX_RUNS = 10;
const unsigned int MIN_RUNS = 1;

const unsigned int MAX_TFITNESS = 99999;
const unsigned int MAX_PFITNESS = 99999;

//const unsigned int MAX_START_CONDITIONS = 99; // ~~

const std::string raceString[MAX_RACES] = 
{ "Terra", "Protoss", "Zerg" };

//std::list<unsigned int> influenceList[MAX_RACES][UNIT_TYPE_COUNT];

/*void fillInfluenceList()
{
	for(int i=0;i<MAX_RACES; ++i)
	{
		for(unsigned int j=0;j<UNIT_TYPE_COUNT; ++j)
		{
			for(int k=0;k<3; ++k)
			{
				if(stats[i][j].prerequisite[k])
					influenceList[i][stats[i][j].prerequisite[k]].push_front(j);
				if(stats[i][j].facility[k])
					influenceList[i][stats[i][j].facility[k]].push_front(j);
			}
			for(int k=0;k<2; ++k)
				if(stats[i][j].upgrade[k])
					influenceList[i][stats[i][j].upgrade[k]].push_front(j);
		}
	}
}*/
// BUILD FREE ADDON PLACE FOR FACTORY, STARPORT ETC. WIE BEI RESEARCHES
const UNIT_STATISTICS stats[MAX_RACES][UNIT_TYPE_COUNT]=
{
{//n                          t     m     g  ns hs uc up      prere       fac     fac2    facility_type         create speed  unit type
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 100, REMAINING_UNIT_TYPE, 0},
{"SCV"	,					 20, 5000,    0,  1, 0, 0, {0, 0}, {0 ,0, 0}, {COMMAND_CENTER, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, WORKER_UNIT_TYPE, 0},
{"Space Marine", 		 		 24, 5000,    0,  1, 0, 0, {0, 0}, {0 ,0, 0}, {BARRACKS, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Ghost",					 50, 2500, 7500,  1, 0, 0, {0, 0}, {ACADEMY ,SCIENCE_FACILITY_CO, 0}, {BARRACKS, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Vulture",					 30, 7500,    0,  2, 0, 0, {0, 0}, {0, 0, 0}, {FACTORY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Goliath",					 40,10000, 5000,  2, 0, 0, {0, 0}, {ARMORY, 0, 0}, {FACTORY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Siege Tank", 				 50,15000,10000,  2, 0, 0, {0, 0}, {0 ,0, 0}, {FACTORY_MS, 0, 0}, FACTORY, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Firebat",					 24, 5000, 2500,  1, 0, 0, {0, 0}, {ACADEMY ,0, 0}, {BARRACKS, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Medic", 					 30, 5000, 2500,  1, 0, 0, {0, 0}, {ACADEMY ,0, 0}, {BARRACKS, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 1},
{"Wraith", 					 60,15000,10000,  2, 0, 0, {0, 0}, {0 ,0, 0}, {STARPORT, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Science Vessel", 			 80,10000,22500,  2, 0, 0, {0, 0}, {SCIENCE_FACILITY, 0, 0}, {STARPORT_CT, 0, 0}, STARPORT, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Dropship", 				 50,10000,10000,  2, 0, 0, {0, 0}, {0, 0, 0}, {STARPORT_CT, 0, 0}, STARPORT, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Battle Cruiser",			133,40000,30000,  6, 0, 0, {0, 0}, {SCIENCE_FACILITY_PL, 0, 0}, {STARPORT_CT, 0, 0}, STARPORT, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Valkyrie", 				 50,25000,12500,  3, 0, 0, {0, 0}, {ARMORY, 0, 0}, {STARPORT_CT, 0, 0}, STARPORT, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 1},
{"Nuclear Warhead",			100,20000,20000,  8, 0, 0, {0, 0}, {0, 0, 0}, {NUCLEAR_SILO, 0, 0}, 0, NEEDED_ALWAYS, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Supply Depot", 			 40,10000,    0,  0, 8, 0, {0, 0}, {0, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 0, SUPPLY_UNIT_TYPE, 0},
{"Barracks", 				 80,15000,    0,  0, 0, 0, {0, 0}, {0, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 10, PRODUCE_UNIT_TYPE, 0},
{"Academy", 				 80,15000,    0,  0, 0, 0, {0, 0}, {BARRACKS ,0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Factory", 				 80,20000,10000,  0, 0, 0, {0, 0}, {BARRACKS ,0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, F_FACTORY_ADDON, 10, PRODUCE_UNIT_TYPE, 0},
{"Command Center",			120,40000,    0,  0,10, 0, {0, 0}, {0, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, F_COMMAND_CENTER_ADDON, 10, SUPPLY_UNIT_TYPE, 0},
{"Starport", 				 70,15000,10000,  0, 0, 0, {0, 0}, {FACTORY ,0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, F_STARPORT_ADDON, 10, PRODUCE_UNIT_TYPE, 0},
{"Science Facility", 		 60,10000,15000,  0, 0, 0, {0, 0}, {STARPORT ,0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, F_SCIENCE_FACILITY_ADDON, 10, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Engineering Bay", 		 60,12500,    0,  0, 0, 0, {0, 0}, {0, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 10, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Armory", 					 80,10000, 5000,  0, 0, 0, {0, 0}, {FACTORY, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Missile Turret", 			 30, 7500,    0,  0, 0, 0, {0, 0}, {ENGINEERING_BAY, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Bunker", 					 30,10000,    0,  0, 0, 0, {0, 0}, {BARRACKS, 0, 0}, {SCV, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Comsat Station",  		  0,    0,    0,  0, 0, 0, {0, 0}, {COMSAT_STATION, COMMAND_CENTER_CS, 0}, {0, 0 ,0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0}, 
{"Nuclear Silo",  			  0,    0,    0,  0, 0, 0, {0, 0}, {NUCLEAR_SILO, COMMAND_CENTER_NS, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Control Tower",  			  0,    0,    0,  0, 0, 0, {0, 0}, {CONTROL_TOWER, STARPORT_CT, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Covert Ops",  			  0,    0,    0,  0, 0, 0, {0, 0}, {COVERT_OPS, SCIENCE_FACILITY_CO, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Physics Lab",  			  0,    0,    0,  0, 0, 0, {0, 0}, {PHYSICS_LAB, SCIENCE_FACILITY_PL, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Machine Shop",  			  0,    0,    0,  0, 0, 0, {0, 0}, {MACHINE_SHOP, FACTORY_MS, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Command Center[CS]", 		 40, 5000, 5000,  0,10, 0, {0, 0}, {ACADEMY, 0, 0}, {COMMAND_CENTER, 0, 0}, F_COMMAND_CENTER_ADDON, NEEDED_UNTIL_COMPLETE, COMSAT_STATION, 0, ADD_ON_UNIT_TYPE, 0}, //TODO: Beim Abheben zerstoeren...
{"Command Center[NS]", 		 40,10000,10000,  0,10, 0, {0, 0}, {SCIENCE_FACILITY_CO, 0, 0}, {COMMAND_CENTER, 0, 0}, F_COMMAND_CENTER_ADDON, NEEDED_UNTIL_COMPLETE, NUCLEAR_SILO, 0, ADD_ON_UNIT_TYPE, 0},
{"Starport[CT]", 			 80, 5000, 5000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {STARPORT, 0, 0}, F_STARPORT_ADDON, NEEDED_UNTIL_COMPLETE, CONTROL_TOWER, 0, ADD_ON_UNIT_TYPE, 0},
{"Science Facility[CO]", 	 40, 5000, 5000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SCIENCE_FACILITY, 0, 0}, F_SCIENCE_FACILITY_ADDON, NEEDED_UNTIL_COMPLETE, COVERT_OPS, 0, ADD_ON_UNIT_TYPE, 0},
{"Science Facility[PL]", 	 40, 5000, 5000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SCIENCE_FACILITY, 0, 0}, F_SCIENCE_FACILITY_ADDON, NEEDED_UNTIL_COMPLETE, PHYSICS_LAB, 0, ADD_ON_UNIT_TYPE, 0},
{"Factory[MS]", 			 40, 5000, 5000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {FACTORY, 0, 0}, F_FACTORY_ADDON, NEEDED_UNTIL_COMPLETE, MACHINE_SHOP, 0, ADD_ON_UNIT_TYPE, 0},
{"Stim Packs", 				 80,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ACADEMY, 0, 0}, R_STIM_PACKS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Lockdown",				100,20000,20000,  0, 0, 0, {0, 0}, {SCIENCE_FACILITY_CO, 0, 0}, {COVERT_OPS, 0, 0}, R_LOCKDOWN, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"EMP Shockwave",			120,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SCIENCE_FACILITY, 0, 0}, R_EMP_SHOCKWAVE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Spider Mines", 			 80,10000,10000,  0, 0, 0, {0, 0}, {FACTORY_MS ,0, 0}, {MACHINE_SHOP, 0, 0}, R_SPIDER_MINES, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Siege Mode", 				 80,15000,15000,  0, 0, 0, {0, 0}, {FACTORY_MS ,0, 0}, {MACHINE_SHOP, 0, 0}, R_TANK_SIEGE_MODE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Irradiate", 				 80,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SCIENCE_FACILITY, 0, 0}, R_IRRADIATE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Yamato Gun",				120,10000,10000,  0, 0, 0, {0, 0}, {SCIENCE_FACILITY_PL ,0, 0}, {PHYSICS_LAB, 0, 0}, R_YAMATO_GUN, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Cloaking Field",			100,15000,15000,  0, 0, 0, {0, 0}, {STARPORT_CT ,0, 0}, {CONTROL_TOWER, 0, 0}, R_CLOAKING_FIELD, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Personnel Cloaking", 		 80,10000,10000,  0, 0, 0, {0, 0}, {SCIENCE_FACILITY_CO ,0, 0}, {COVERT_OPS, 0, 0}, R_PERSONNEL_CLOAKING, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Restoration", 			 80,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ACADEMY, 0, 0}, R_RESTORATION, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Optical Flare",			120,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ACADEMY, 0, 0}, R_OPTICAL_FLARE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"U-238 Shells",			100,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ACADEMY, 0, 0}, R_U238_SHELLS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Ion Thrusters",			100,10000,10000,  0, 0, 0, {0, 0}, {FACTORY_MS ,0, 0}, {MACHINE_SHOP, 0, 0}, R_ION_THRUSTERS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Titan Reactor",			166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SCIENCE_FACILITY, 0, 0}, R_TITAN_REACTOR, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Ocular Implants",			166,10000,10000,  0, 0, 0, {0, 0}, {SCIENCE_FACILITY_CO ,0, 0}, {COVERT_OPS, 0, 0}, R_OCULAR_IMPLANTS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Moebius Reactor",			166,20000,20000,  0, 0, 0, {0, 0}, {SCIENCE_FACILITY_CO ,0, 0}, {COVERT_OPS, 0, 0}, R_MOEBIUS_REACTOR, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Apollo Reactor",			166,20000,20000,  0, 0, 0, {0, 0}, {STARPORT_CT ,0, 0}, {CONTROL_TOWER, 0, 0}, R_APOLLO_REACTOR, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Colossus Reactor",		166,15000,15000,  0, 0, 0, {0, 0}, {SCIENCE_FACILITY_PL ,0, 0}, {PHYSICS_LAB, 0, 0}, R_COLOSSUS_REACTOR, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Caduceus Reactor",		166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ACADEMY, 0, 0}, R_CADUCEUS_REACTOR, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Charon Booster",			133,10000,10000,  0, 0, 0, {0, 0}, {FACTORY_MS ,0, 0}, {MACHINE_SHOP, 0, 0}, R_CHARON_BOOSTER, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Infantry Armor",			266,10000,10000,  0, 0, 7500, {SCIENCE_FACILITY, SCIENCE_FACILITY}, {0 ,0, 0}, {ENGINEERING_BAY, 0, 0}, R_INFANTRY_ARMOR, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Infantry Weapons",		266,10000,10000,  0, 0, 7500, {SCIENCE_FACILITY, SCIENCE_FACILITY}, {0 ,0, 0}, {ENGINEERING_BAY, 0, 0}, R_INFANTRY_WEAPONS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Vehicle Plating",			266,10000,10000,  0, 0, 7500, {SCIENCE_FACILITY, SCIENCE_FACILITY}, {0 ,0, 0}, {ARMORY, 0, 0}, R_VEHICLE_PLATING, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Vehicle Weapons",			266,10000,10000,  0, 0, 7500, {SCIENCE_FACILITY, SCIENCE_FACILITY}, {0 ,0, 0}, {ARMORY, 0, 0}, R_VEHICLE_WEAPONS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Ship Plating",			266,15000,15000,  0, 0, 7500, {SCIENCE_FACILITY, SCIENCE_FACILITY}, {0 ,0, 0}, {ARMORY, 0, 0}, R_SHIP_PLATING, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Ship Weapons",			266,10000,10000,  0, 0, 5000, {SCIENCE_FACILITY, SCIENCE_FACILITY}, {0 ,0, 0}, {ARMORY, 0, 0}, R_SHIP_WEAPONS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Refinery", 				 40,10000,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SCV, 0, 0}, 0/*VESPENE_GEYSIR*/, NEEDED_UNTIL_COMPLETE_IS_LOST/*_IS_LOST*/, GAS_SCV, 0, SUPPLY_UNIT_TYPE, 0}, //~~~ueberlegen...
{"Gas SCV",					  3,    0,    0,  0, 0, 0, {0, 0}, {REFINERY ,0, 0}, {SCV/*REFINERY*/, 0, 0}, /*SCV*/0, /*NEEDED_ONCE_*/IS_MORPHING, 0, 0, GAS_MINER_UNIT_TYPE, 0},	//~~~~  warum 3,0,0,1?
{"Build parallel 2",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 4",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 8",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 16",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Send all Gas to Minerals",			  3,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {GAS_SCV, 0, 0}, 0, IS_MORPHING, 0, 0, WORKER_UNIT_TYPE, 0},
{"Move to here",			  3,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},

{"Vespene Geysir",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Minerals",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Stim Packs",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Lockdown",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_EMP Shockwave",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Spider Mines",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Siege Mode",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Irradiate",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Yamato Gun",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Cloaking Field",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Personnel Cloaking",	  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Restoration",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Optical Flare",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_U-238 Shells",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ion Thrusters",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Titan Reactor",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ocular Implants",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Moebius Reactor",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Apollo Reactor",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Colossus Reactor",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Caduceus Reactor",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Charon Booster",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Infantry Armor",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Infantry Weapons",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Vehicle Plating",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Vehicle Weapons",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ship Plating",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ship Weapons",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},

{"F_Factory Addon",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"F_Starport Addon",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"F_Command Center Addon",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"F_Science Facility Addon",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"INTRON",					  0,    0,    0,  0, 0, 0, {0, 0}, {0, 0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0}
},

 //for colors... 0= rest, 1= scv, 2= gas scv, 3= combat units, 4=support, 5=supply/refinery, 6=produce buildings, 7=research buildigns, 8= addons, 9=researchs, 10= special


{
{"NULL",  					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Probe",					 20, 5000,    0,  1, 0, 0, {0, 0}, {0 ,0, 0}, {NEXUS, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, WORKER_UNIT_TYPE, 0},
{"Dark Templar",			 50,12500,10000,  2, 0, 0, {0, 0}, {TEMPLAR_ARCHIVES ,0, 0}, {GATEWAY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 1},
{"Dark Archon",				 20,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DARK_TEMPLAR, 0, 0}, DARK_TEMPLAR, IS_MORPHING, 0, 100, COMBAT_UNIT_TYPE, 1},
{"Zealot",					 40,10000,    0,  2, 0, 0, {0, 0}, {0 ,0, 0}, {GATEWAY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Dragoon",					 50,12500, 5000,  2, 0, 0, {0, 0}, {CYBERNETICS_CORE ,0, 0}, {GATEWAY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"High Templar",			 50, 5000,15000,  2, 0, 0, {0, 0}, {TEMPLAR_ARCHIVES ,0, 0}, {GATEWAY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Archon",					 20,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {HIGH_TEMPLAR, 0, 0}, HIGH_TEMPLAR, IS_MORPHING, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Reaver",					 70,20000,10000,  4, 0, 0, {0, 0}, {ROBOTICS_SUPPORT_BAY ,0, 0}, {ROBOTICS_FACILITY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0}, 
{"5xScarab",				 35, 7500,    0,  0, 0, 0, {0, 0}, {0, 0, 0}, {REAVER, 0, 0}, 0, NEEDED_ALWAYS, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"10xScarab",				 35, 7500,    0,  0, 0, 0, {0, 0}, {REAVER_CAPACITY, 0, 0}, {HALF_SCARAB, 0, 0}, 0, IS_LOST, 0, 0, SPECIAL_UNIT_TYPE, 0}, //~~ special rule... reaver is no longer availible :/
{"Corsair",					 40,15000,10000,  2, 0, 0, {0, 0}, {0 ,0, 0}, {STARGATE, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 1},
{"Shuttle",					 60,20000,    0,  2, 0, 0, {0, 0}, {0 ,0, 0}, {ROBOTICS_FACILITY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Scout",					 80,27500,12500,  3, 0, 0, {0, 0}, {0 ,0, 0}, {STARGATE, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Arbiter",					160,10000,35000,  4, 0, 0, {0, 0}, {ARBITER_TRIBUNAL ,0, 0}, {STARGATE, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Carrier",					140,35000,25000,  6, 0, 0, {0, 0}, {FLEET_BEACON ,0, 0}, {STARGATE, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, COMBAT_UNIT_TYPE, 0},
{"5xInterceptor",			100,25000,    0,  0, 0, 0, {0, 0}, {0, 0, REMAINING_UNIT_TYPE}, {CARRIER, 0, 0}, 0, NEEDED_ALWAYS, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"8xInterceptor",			 60,15000,    0,  0, 0, 0, {0, 0}, {CARRIER_CAPACITY, 0, REMAINING_UNIT_TYPE}, {HALF_INTERCEPTOR, 0, 0}, 0, IS_LOST, 0, 0, SPECIAL_UNIT_TYPE, 0}, //~~~ Special rule... carrier is no longer availible :/
{"Observer",				 40, 2500, 7500,  1, 0, 0, {0, 0}, {OBSERVATORY ,0, 0}, {ROBOTICS_FACILITY, 0, 0}, 0, NEEDED_UNTIL_COMPLETE, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Nexus",					120,40000,    0,  0, 9, 0, {0, 0}, {0 ,0, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, SUPPLY_UNIT_TYPE, 0},
{"Robotics Facility",		 80,20000,20000,  0, 0, 0, {0, 0}, {CYBERNETICS_CORE ,PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, PRODUCE_UNIT_TYPE, 0},
{"Pylon",					 30,10000,    0,  0, 8, 0, {0, 0}, {0 ,0, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, SUPPLY_UNIT_TYPE, 0},
{"Observatory",				 30, 5000,10000,  0, 0, 0, {0, 0}, {ROBOTICS_FACILITY ,PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Gateway",					 60,15000,    0,  0, 0, 0, {0, 0}, {PYLON ,0, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, PRODUCE_UNIT_TYPE, 0},
{"Photon Cannon",			 50,15000,    0,  0, 0, 0, {0, 0}, {FORGE, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Cybernetics Core",		 60,20000,    0,  0, 0, 0, {0, 0}, {GATEWAY, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Citadel Of Adun",			 60,15000,10000,  0, 0, 0, {0, 0}, {CYBERNETICS_CORE, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Templar Archives",		 60,15000,20000,  0, 0, 0, {0, 0}, {CITADEL_OF_ADUN, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Forge",					 40,15000,    0,  0, 0, 0, {0, 0}, {PYLON, 0, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Stargate",				 70,15000,15000,  0, 0, 0, {0, 0}, {CYBERNETICS_CORE, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, PRODUCE_UNIT_TYPE, 0},
{"Fleet Beacon",			 60,30000,20000,  0, 0, 0, {0, 0}, {STARGATE, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Arbiter Tribunal",		 60,20000,15000,  0, 0, 0, {0, 0}, {TEMPLAR_ARCHIVES, STARGATE, PYLON}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Robotics Support Bay",	 30,15000,10000,  0, 0, 0, {0, 0}, {ROBOTICS_FACILITY, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Shield Battery",			 30,10000,    0,  0, 0, 0, {0, 0}, {GATEWAY, PYLON, 0}, {PROBE, 0, 0}, 0, NEEDED_ONCE, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Psionic Storm",			120,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {TEMPLAR_ARCHIVES, 0, 0}, R_PSIONIC_STORM, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Hallucination",			 80,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {TEMPLAR_ARCHIVES, 0, 0}, R_HALLUCINATION, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Recall",					120,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ARBITER_TRIBUNAL, 0, 0}, R_RECALL, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Stasis Field",			100,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ARBITER_TRIBUNAL, 0, 0}, R_STASIS_FIELD, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Disruption Web",			 80,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {FLEET_BEACON, 0, 0}, R_DISRUPTION_WEB, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Mind Control",			120,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {TEMPLAR_ARCHIVES, 0, 0}, R_MIND_CONTROL, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Maelstrom",				100,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {TEMPLAR_ARCHIVES, 0, 0}, R_MAELSTROM, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Singularity Charge",		166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {CYBERNETICS_CORE, 0, 0}, R_SINGULARITY_CHARGE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Leg Enhancements",		133,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {CITADEL_OF_ADUN, 0, 0}, R_LEG_ENHANCEMENTS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Scarab Damage",			166,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ROBOTICS_SUPPORT_BAY, 0, 0}, R_SCARAB_DAMAGE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Reaver Capacity",			166,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ROBOTICS_SUPPORT_BAY, 0, 0}, R_REAVER_CAPACITY, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Gravitic Drive",			166,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ROBOTICS_SUPPORT_BAY, 0, 0}, R_GRAVITIC_DRIVE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Sensor Array",			133,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {OBSERVATORY, 0, 0}, R_SENSOR_ARRAY, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Gravitic Boosters",		133,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {OBSERVATORY, 0, 0}, R_GRAVITIC_BOOSTERS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Khaydarin Amulet",		166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {TEMPLAR_ARCHIVES, 0, 0}, R_KHAYDARIN_AMULET, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Apial Sensors",			166,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {FLEET_BEACON, 0, 0}, R_APIAL_SENSORS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Gravitic Thrusters",		166,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {FLEET_BEACON, 0, 0}, R_GRAVITIC_THRUSTERS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Carrier Capacity",		100,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {FLEET_BEACON, 0, 0}, R_CARRIER_CAPACITY, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Khaydarin Core",			166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ARBITER_TRIBUNAL, 0, 0}, R_KHAYDARIN_CORE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1}, //?
{"Argus Jewel",				166,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {FLEET_BEACON, 0, 0}, R_ARGUS_JEWEL, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Argus Talisman",			166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {TEMPLAR_ARCHIVES, 0, 0}, R_ARGUS_TALISMAN, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Armor",					266,10000,10000,  0, 0, 7500, {TEMPLAR_ARCHIVES, TEMPLAR_ARCHIVES}, {0 ,0, 0}, {FORGE, 0, 0}, R_ARMOR, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Plating",					266,15000,15000,  0, 0, 7500, {FLEET_BEACON, FLEET_BEACON}, {0 ,0, 0}, {CYBERNETICS_CORE, 0, 0}, R_PLATING, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Ground Weapons",			266,10000,10000,  0, 0, 5000, {TEMPLAR_ARCHIVES, TEMPLAR_ARCHIVES}, {0 ,0, 0}, {FORGE, 0, 0}, R_GROUND_WEAPONS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Air Weapons",				266,10000,10000,  0, 0, 7500, {FLEET_BEACON, FLEET_BEACON}, {0 ,0, 0}, {CYBERNETICS_CORE, 0, 0}, R_AIR_WEAPONS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Plasma Shields",			266,20000,20000,  0, 0, 10000, {0, 0}, {0 ,0, 0}, {FORGE, 0, 0}, R_PLASMA_SHIELDS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Assimilator",				 40,10000,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {PROBE, 0, 0}, /*VESPENE_GEYSIR*/0, NEEDED_ONCE/*_IS_LOST*/, 0, 0, SUPPLY_UNIT_TYPE, 0},
{"Gas Probe",				  3,    0,    0,  0, 0, 0, {0, 0}, {ASSIMILATOR ,0, 0}, {PROBE/*ASSIMILATOR*/, 0, 0}, 0/*PROBE*/, /*NEEDED_ONCE_*/IS_MORPHING, 0, 0, GAS_MINER_UNIT_TYPE, 0},	//Needed once? ~~~ wenn hier ne Aenderung, Facility2 in race und anarace wieder auf location availible checken !TODO
{"Build parallel 2",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 4",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 8",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 16",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Send all Gas to Minerals",			  3,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {GAS_SCV, 0, 0}, 0, IS_MORPHING, 0, 0, WORKER_UNIT_TYPE, 0},
{"Move to here",			  3,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},

{"Vespene Geysir",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Minerals",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Psionic Storm",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Hallucination",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Recall",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Stasis Field",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Disruption Web",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Mind Control",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Maelstrom",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Singularity Charge",	  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Leg Enhancements",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Scarab Damage",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Reaver Capacity",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Gravitic Drive",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Sensor Array",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Gravitic Boosters",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Khaydarin Amulet",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Apial Sensors",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Gravitic Thrusters",	  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Carrier Capacity",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Khaydarin Core",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Argus Jewel",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Argus Talisman",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Armor",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Plating",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ground Weapons",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Air Weapons",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Plasma Shields",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"INTRON",					  0,    0,    0,  0, 0, 0, {0, 0}, {0, 0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0}
},
 //for colors... 0= rest, 1= scv, 2= gas scv, 3= combat units, 4=support, 5=supply/refinery, 6=produce buildings, 7=research buildigns, 8= addons, 9=researchs, 10= special
{
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0, 0, 0}, {0 ,0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Drone",					 23, 5000,    0,  1, 0, 0, {0, 0}, {0 ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, WORKER_UNIT_TYPE, 0},
{"Larva",					 20,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NEEDED_ONCE, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Zergling",				 28, 5000,    0,  1, 0, 0, {0, 0}, {SPAWNING_POOL ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, ZERGLING, 100, COMBAT_UNIT_TYPE, 0},
{"Hydralisk",				 28, 7500, 2500,  1, 0, 0, {0, 0}, {HYDRALISK_DEN ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, COMBAT_UNIT_TYPE, 0}, //Hier stand ein Zergling als facility2!?
{"Ultralisk",				 60,20000,20000,  6, 0, 0, {0, 0}, {ULTRALISK_CAVERN ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Defiler",					 50, 5000,15000,  2, 0, 0, {0, 0}, {DEFILER_MOUND ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Lurker",					 40, 5000,10000,  0, 0, 0, {0, 0}, {HYDRALISK_DEN ,LURKER_ASPECT, 0}, {HYDRALISK, 0, 0}, 0, IS_MORPHING, 0, 100, COMBAT_UNIT_TYPE, 1},
{"Overlord",				 40,10000,    0,  0, 8, 0, {0, 0}, {0 ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, SUPPLY_UNIT_TYPE, 0},
{"Mutalisk",				 40,10000,10000,  2, 0, 0, {0, 0}, {SPIRE ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, COMBAT_UNIT_TYPE, 0},
{"Guardien",				 40, 5000,10000,  0, 0, 0, {0, 0}, {GREATER_SPIRE ,0, 0}, {MUTALISK, 0, 0}, 0, IS_MORPHING, 0, 100, COMBAT_UNIT_TYPE, 0}, 
{"Queen",					 50,10000,10000,  2, 0, 0, {0, 0}, {QUEENS_NEST ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, 0, 100, SUPPORT_UNIT_TYPE, 0},
{"Scourge",					 30, 2500, 7500,  1, 0, 0, {0, 0}, {SPIRE ,0, 0}, {LARVA, 0, 0}, 0, IS_LOST, SCOURGE, 100, COMBAT_UNIT_TYPE, 0},
{"Devourer",				 40,10000, 5000,  0, 0, 0, {0, 0}, {GREATER_SPIRE ,0, 0}, {MUTALISK, 0, 0}, 0, IS_MORPHING, 0, 100, COMBAT_UNIT_TYPE, 1}, 
{"Lair",					100,15000,10000,  0, 0, 0, {0, 0}, {SPAWNING_POOL ,0, 0}, {HATCHERY, 0, 0}, 0, IS_MORPHING, 0, 0, ADD_ON_UNIT_TYPE, 0},
{"Hive",					120,20000,15000,  0, 0, 0, {0, 0}, {QUEENS_NEST ,0, 0}, {LAIR, 0, 0}, 0, IS_MORPHING, 0, 0, ADD_ON_UNIT_TYPE, 0},
{"Nydus Canal",				 40,15000,    0,  0, 0, 0, {0, 0}, {HIVE ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Hydralisk den",			 40,10000, 5000,  0, 0, 0, {0, 0}, {SPAWNING_POOL ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Defiler mound",			 60,10000,10000,  0, 0, 0, {0, 0}, {HIVE ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Hatchery",				120,30000,    0,  0, 1, 0, {0, 0}, {0 ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, LARVA, 0, PRODUCE_UNIT_TYPE, 0}, //create 1 Larva when done :-) TODO: add another "create"field for "CREEP"
{"Greater Spire",			120,10000,15000,  0, 0, 0, {0, 0}, {HIVE ,0, 0}, {SPIRE, 0, 0}, 0, IS_MORPHING, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Queen's Nest",			 60,15000,10000,  0, 0, 0, {0, 0}, {LAIR ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Evolution Chamber",		 40, 7500,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Ultralisk Cavern",		 80,15000,20000,  0, 0, 0, {0, 0}, {HIVE ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Spire",					120,20000,15000,  0, 0, 0, {0, 0}, {LAIR ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Spawning Pool",			 80,20000,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, RESEARCH_FACILITY_UNIT_TYPE, 0},
{"Creep Colony",			 20, 7500,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DRONE, 0, 0}, 0, IS_LOST, 0, 0, SUPPORT_UNIT_TYPE, 0},
{"Spore Colony",			 20, 5000,    0,  0, 0, 0, {0, 0}, {EVOLUTION_CHAMBER ,0, 0}, {CREEP_COLONY, 0, 0}, 0, IS_LOST, 0, 0, ADD_ON_UNIT_TYPE, 0},
{"Sunken Colony",			 20, 5000,    0,  0, 0, 0, {0, 0}, {SPAWNING_POOL ,0, 0}, {CREEP_COLONY, 0, 0}, 0, IS_LOST, 0, 0, ADD_ON_UNIT_TYPE, 0},
{"Ventral Sacs",			160,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {LAIR, HIVE, 0}, R_VENTRAL_SACKS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE,0 }, 
{"Antennae",				133,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {LAIR, HIVE, 0}, R_ANTENNAE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Pneumatized Carapace",	133,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {LAIR, HIVE, 0}, R_PNEUMATIZED_CARAPACE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Metabolic Boost",			100,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {SPAWNING_POOL, 0, 0}, R_METABOLIC_BOOST, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Adrenal Glands",			100,20000,20000,  0, 0, 0, {0, 0}, {HIVE ,0, 0}, {SPAWNING_POOL, 0, 0}, R_ADRENAL_GLANDS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Muscular Augments",		100,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {HYDRALISK_DEN, 0, 0}, R_MUSCULAR_AUGMENTS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Grooved Spines",			100,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {HYDRALISK_DEN, 0, 0}, R_GROOVED_SPINES, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Gamete Meiosis",			166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {QUEENS_NEST, 0, 0}, R_GAMETE_MEIOSIS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Metasynaptic Node",		166,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DEFILER_MOUND, 0, 0}, R_METASYNAPTIC_NODE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Chitinous Plating",		133,15000,15000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ULTRALISK_CAVERN, 0, 0}, R_CHITINOUS_PLATING, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Anabolic Synthesis",		133,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {ULTRALISK_CAVERN, 0, 0}, R_ANABOLIC_SYNTHESIS, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1},
{"Burrowing",				 80,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {HATCHERY, LAIR, HIVE}, R_BURROWING, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Spawn Broodling",			 80,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {QUEENS_NEST, 0, 0}, R_SPAWN_BROODLING, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Plague",					100,20000,20000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DEFILER_MOUND, 0, 0}, R_PLAGUE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Consume",					100,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {DEFILER_MOUND, 0, 0}, R_CONSUME, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Ensnare",					 80,10000,10000,  0, 0, 0, {0, 0}, {0 ,0, 0}, {QUEENS_NEST, 0, 0}, R_ENSNARE, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Lurker Aspect",			120,20000,20000,  0, 0, 0, {0, 0}, {LAIR ,0, 0}, {HYDRALISK_DEN, 0, 0}, R_LURKER_ASPECT, NEEDED_UNTIL_COMPLETE_IS_LOST, 0, 0, RESEARCH_UNIT_TYPE, 1}, 
{"Carapace",				266,15000,15000,  0, 0, 7500, {LAIR, HIVE}, {0 ,0, 0}, {EVOLUTION_CHAMBER, 0, 0}, R_CARAPACE, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Flyer Carapace",			266,15000,15000,  0, 0, 7500, {LAIR, HIVE}, {0 ,0, 0}, {SPIRE, GREATER_SPIRE, 0}, R_FLYER_CARAPACE, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Melee Attacks",			266,10000,10000,  0, 0, 5000, {LAIR, HIVE}, {0 ,0, 0}, {EVOLUTION_CHAMBER, 0, 0}, R_MELEE_ATTACKS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Missile Attacks",			266,10000,10000,  0, 0, 5000, {LAIR, HIVE}, {0 ,0, 0}, {EVOLUTION_CHAMBER, 0, 0}, R_MISSILE_ATTACKS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"Flyer Attacks",			266,10000,10000,  0, 0, 7500, {LAIR, HIVE}, {0 ,0, 0}, {SPIRE, GREATER_SPIRE, 0}, R_FLYER_ATTACKS, NEEDED_UNTIL_COMPLETE_IS_LOST_BUT_AVAILIBLE, 0, 0, RESEARCH_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Extractor",				 40, 5000,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {/*VESPENE_GEYSIR*/DRONE, 0, 0}, 0/*DRONE*/, IS_LOST, 0, 0, SUPPLY_UNIT_TYPE, 0}, //~~ //TODO HAE?
{"Gas Drone",				  3,    0,    0,  0, 0, 0, {0, 0}, {EXTRACTOR ,0, 0}, {/*EXTRACTOR*/DRONE, 0, 0}, /*DRONE*/0, /*NEEDED_ONCE_*/IS_MORPHING, 0, 0, GAS_MINER_UNIT_TYPE, 0}, //~~~~
{"Build parallel 2",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 4",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 8",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Build parallel 16",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
{"Send all Gas to Minerals",			  3,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {GAS_SCV, 0, 0}, 0, IS_MORPHING, 0, 0, WORKER_UNIT_TYPE, 0},
{"Move to here",			  3,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, SPECIAL_UNIT_TYPE, 0},
	
{"Vespene Geysir",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Minerals",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"Break up Building",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ventral Sacs",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Antennae",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Pneumati. Carapace",	  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Metabolic Boost",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Adrenal Glands",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Muscular Augments",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Grooved Spines",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Gamete Meiosis",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Metasynaptic Node",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Chitinous Plating",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Anabolic Synthesis",	  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 1},
{"R_Burrowing",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Spawn Broodling",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Plague",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Consume",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Ensnare",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Lurker Aspect",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Carapace",				  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Flyer Carapace",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Melee Attacks",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Missile Attacks",		  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"R_Flyer Attacks",			  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"NULL",					  0,    0,    0,  0, 0, 0, {0, 0}, {0 ,0, 0}, {0, 0, 0}, 0, NO_FACILITY_BEHAVIOUR_DEFINED, 0, 0, REMAINING_UNIT_TYPE, 0},
{"INTRON",					  0,    0 ,   0,  0, 0, 0, {0, 0}, {0, 0, 0}, {0, 0, 0}, 0, NO_FACILITY, 0, 0, REMAINING_UNIT_TYPE, 0}
}
};

// TODO: automatic building units/buildings for spells and larvaes




