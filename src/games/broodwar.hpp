#ifndef _GAMEBROODWAR_BROODWAR_HPP
#define _GAMEBROODWAR_BROODWAR_HPP
// TODO abstrakte Klasse f�r alle Games

#include "gamedata.hpp"

class Broodwar : public GameData
{
public:
	Broodwar();
	~Broodwar();	
	const boost::shared_ptr<const Rules> getRules() const;
	enum eBroodwarUnits
	{
		NONE,
	
		LOCATION_PRIORITY,
		WAIT,
		BREAK_UP_BUILDING,		


		MINERAL,
		GAS,

		MINERAL_PATCH,
		DEPLETED_MINERAL_PATCH,
		VESPENE_GEYSIR,
		DEPLETED_VESPENE_GEYSIR,

		TERRAN_SUPPLY,
		PROTOSS_SUPPLY,
		ZERG_SUPPLY,

		SCV_FROM_GAS_TO_MINERALS,
		PROBE_FROM_GAS_TO_MINERALS,
		DRONE_FROM_GAS_TO_MINERALS,

		SCV,
		GAS_SCV,
		

		SPACE_MARINE,
		GHOST,
		VULTURE,
		GOLIATH,
		SIEGE_TANK,
		FIREBAT,
		MEDIC,
		WRAITH,
		SCIENCE_VESSEL,
		DROPSHIP,
		BATTLE_CRUISER,
		VALKYRIE,
		NUCLEAR_WARHEAD,

		REFINERY,
		DEPLETED_REFINERY,
		COMMAND_CENTER,
		SUPPLY_DEPOT,
		BARRACKS,
		ACADEMY,
		FACTORY,
		STARPORT,
		SCIENCE_FACILITY,
		ENGINEERING_BAY,
		ARMORY,
		MISSILE_TURRET,
		BUNKER,

		COMSAT_STATION,
		NUCLEAR_SILO,
		CONTROL_TOWER,
		COVERT_OPS,
		PHYSICS_LAB,
		MACHINE_SHOP,

		COMMAND_CENTER_CS, // connected structure!
		COMMAND_CENTER_NS,
		STARPORT_CT,
		SCIENCE_FACILITY_CO,
		SCIENCE_FACILITY_PL,
		FACTORY_MS,

		F_FACTORY_ADDON,
		F_STARPORT_ADDON,
		F_COMMAND_CENTER_ADDON,
		F_SCIENCE_FACILITY_ADDON,

		STIM_PACKS,
		LOCKDOWN,
		EMP_SHOCKWAVE,
		SPIDER_MINES,
		TANK_SIEGE_MODE,
		IRRADIATE,
		YAMATO_GUN,
		CLOAKING_FIELD,
		PERSONNEL_CLOAKING,
		RESTORATION,
		OPTICAL_FLARE,
		U238_SHELLS,
		ION_THRUSTERS,
		TITAN_REACTOR,
		OCULAR_IMPLANTS,
		MOEBIUS_REACTOR,
		APOLLO_REACTOR,
		COLOSSUS_REACTOR,
		CADUCEUS_REACTOR,
		CHARON_BOOSTER,

		INFANTRY_ARMOR_1,
		INFANTRY_ARMOR_2,
		INFANTRY_ARMOR_3,
		INFANTRY_WEAPONS_1,
		INFANTRY_WEAPONS_2,
		INFANTRY_WEAPONS_3,
		VEHICLE_PLATING_1,
		VEHICLE_PLATING_2,
		VEHICLE_PLATING_3,
		VEHICLE_WEAPONS_1,
		VEHICLE_WEAPONS_2,
		VEHICLE_WEAPONS_3,
		SHIP_PLATING_1,
		SHIP_PLATING_2,
		SHIP_PLATING_3,
		SHIP_WEAPONS_1,
		SHIP_WEAPONS_2,
		SHIP_WEAPONS_3,


		PROBE,
		GAS_PROBE,
		

		DARK_TEMPLAR,
		DARK_ARCHON,
		ZEALOT,
		DRAGOON,
		HIGH_TEMPLAR,
		ARCHON,
		REAVER,
		HALF_SCARAB,
		FULL_SCARAB,
		CORSAIR,
		SHUTTLE,
		SCOUT,
		ARBITER,
		CARRIER,
		HALF_INTERCEPTOR,
		FULL_INTERCEPTOR,
		OBSERVER,

		ASSIMILATOR,
		DEPLETED_ASSIMILATOR,
		NEXUS,
		ROBOTICS_FACILITY,
		PYLON,
		OBSERVATORY,
		GATEWAY,
		PHOTON_CANNON,
		CYBERNETICS_CORE,
		CITADEL_OF_ADUN,
		TEMPLAR_ARCHIVES,
		FORGE,
		STARGATE,
		FLEET_BEACON,
		ARBITER_TRIBUNAL,
		ROBOTICS_SUPPORT_BAY,
		SHIELD_BATTERY,

		PSIONIC_STORM,
		HALLUCINATION,
		RECALL,
		STASIS_FIELD,
		DISRUPTION_WEB,
		MIND_CONTROL,
		MAELSTROM,
		SINGULARITY_CHARGE,
		LEG_ENHANCEMENTS,
		SCARAB_DAMAGE,
		REAVER_CAPACITY,
		GRAVITIC_DRIVE,
		SENSOR_ARRAY,
		GRAVITIC_BOOSTERS,
		KHAYDARIN_AMULET,
		APIAL_SENSORS,
		GRAVITIC_THRUSTERS,
		CARRIER_CAPACITY,
		KHAYDARIN_CORE,
		ARGUS_JEWEL,
		ARGUS_TALISMAN,

		ARMOR_1,
		ARMOR_2,
		ARMOR_3,
		PLATING_1,
		PLATING_2,
		PLATING_3,
		GROUND_WEAPONS_1,
		GROUND_WEAPONS_2,
		GROUND_WEAPONS_3,
		AIR_WEAPONS_1,
		AIR_WEAPONS_2,
		AIR_WEAPONS_3,
		PLASMA_SHIELDS_1,
		PLASMA_SHIELDS_2,
		PLASMA_SHIELDS_3,

		DRONE,
		GAS_DRONE,
		

		LARVA,
		ZERGLING,
		HYDRALISK,
		ULTRALISK,
		DEFILER,
		LURKER,
		OVERLORD,
		MUTALISK,
		GUARDIEN,
		QUEEN,
		SCOURGE,
		DEVOURER,

		EXTRACTOR,
		DEPLETED_EXTRACTOR,
		HATCHERY,
		LAIR,
		HIVE,
		NYDUS_CANAL,
		HYDRALISK_DEN,
		DEFILER_MOUND,
		GREATER_SPIRE,
		QUEENS_NEST,
		EVOLUTION_CHAMBER,
		ULTRALISK_CAVERN,
		SPIRE,
		SPAWNING_POOL,
		CREEP_COLONY,
		SPORE_COLONY,
		SUNKEN_COLONY,

		VENTRAL_SACKS,
		ANTENNAE,
		PNEUMATIZED_CARAPACE,
		METABOLIC_BOOST,
		ADRENAL_GLANDS,
		MUSCULAR_AUGMENTS,
		GROOVED_SPINES,
		GAMETE_MEIOSIS,
		METASYNAPTIC_NODE,
		CHITINOUS_PLATING,
		ANABOLIC_SYNTHESIS,
		BURROWING,
		SPAWN_BROODLING,
		PLAGUE,
		CONSUME,
		ENSNARE,
		LURKER_ASPECT,

		CARAPACE_1,
		CARAPACE_2,
		CARAPACE_3,
		FLYER_CARAPACE_1,
		FLYER_CARAPACE_2,
		FLYER_CARAPACE_3,
		MELEE_ATTACKS_1,
		MELEE_ATTACKS_2,
		MELEE_ATTACKS_3,
		MISSILE_ATTACKS_1,
		MISSILE_ATTACKS_2,
		MISSILE_ATTACKS_3,
		FLYER_ATTACKS_1,
		FLYER_ATTACKS_2,
		FLYER_ATTACKS_3,

		MAX_UNIT_TYPE_NUM

	};
	std::map<unsigned int, boost::uuids::uuid> unit_id_map;

private:


	const boost::shared_ptr<const Race> neutralRace;
	const boost::shared_ptr<const Race> terraRace;
	const boost::shared_ptr<const Race> protossRace;
	const boost::shared_ptr<const Race> zergRace;

	const boost::shared_ptr<const Rules> rules;

	Broodwar& operator=(const Broodwar& other);
	Broodwar(const Broodwar& other);

	const std::list<boost::shared_ptr<const Race> > init_racelist_helper() const;
	const std::map<const unsigned int, const boost::uuids::uuid> init_unitidmap_helper() const;
	const std::list<boost::shared_ptr<const UnitType> > init_unittypelist_helper();	
};

inline const boost::shared_ptr<const Rules> Broodwar::getRules() const {
	return rules;
}

#endif
