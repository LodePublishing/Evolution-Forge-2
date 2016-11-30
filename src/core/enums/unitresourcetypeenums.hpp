#ifndef _CORE_UNITRESOURCETYPEENUMS_HPP
#define _CORE_UNITRESOURCETYPEENUMS_HPP

enum eUnitResourceType
{
	// most units
	NEED_GLOBAL_SUPPLY_RESOURCE,
	
	// supply depot, command center, overlord etc.
	PRODUCE_SUPPLY_RESOURCE,
	
	// for the supply resource
	SUPPLY_PROVIDER,

	// Mineral
	NORMAL_GLOBAL_RESOURCE,
	
	// for units of the whole resource gathering chain
	ACCEPTER_RESOURCES, // resource, source, gatherer
	GATHERER_RESOURCES, // resource, source, accepter
	SOURCE_RESOURCES,   // resource, gatherer, accepter
	RESOURCE_RESOURCES, // source, gatherer, accepter

/*	RESOURCE_ACCEPTER,
	ACCEPTER_RESOURCE,
	GATHERER_ACCEPTER,
	ACCEPTER_GATHERER,
	ACCEPTER_SOURCE,
	SOURCE_ACCEPTER,	

	RESOURCE_SOURCE,
	SOURCE_RESOURCE,
	RESOURCE_GATHERER,
	GATHERER_RESOURCE,

	SOURCE_GATHERER,
	GATHERER_SOURCE,*/
	
	

// technology
	GLOBAL_PREREQUISITE_RESOURCE,
// e.g. a probe, needed only a short time
	LOCAL_PREREQUISITE_RESOURCE, 

// facility is lost immediately after construction is started
	FACILITY_IS_LOST_RESOURCE,
// neutral facility is lost immediately after construction is started TODO Example?
	NEUTRAL_FACILITY_IS_LOST_RESOURCE,
// neutral facility (e.g. vespene geysir, gold mine etc.) is needed as long as this building stands
	NEUTRAL_FACILITY_IS_NEEDED_ALWAYS_RESOURCE,
// facility continues to exist (i.e. provide technology, supply etc.) until construction is complete
	FACILITY_IS_MORPHING_RESOURCE,
// facility is used during the building but is not lost at the end
// TODO später: Mehrere alternative facilities erlauben
	FACILITY_IS_NEEDED_UNTIL_COMPLETE_RESOURCE,
// facility can build only one item, stays unavailable even after construction is finished (e.g. silos, scarabs, interceptors)
	FACILITY_IS_NEEDED_ALWAYS_RESOURCE,
// global facility continues to exist until construction is complete (e.g. researches)
	GLOBAL_FACILITY_IS_MORPHING_RESOURCE,

	// this unit gets created when the construction is finished
	UNIT_CREATE_RESOURCE,

	// create one unit every X time units, e.g. larvae, but also resource points (CoH)
	UNIT_CREATE_REGULARLY_RESOURCE, 

	// e.g. new local harvesting technology
	AFFECTS_RESOURCE_GATHERING_LOCALLY,
	// e.g. new harvesting technology
	AFFECTS_RESOURCE_GATHERING_GLOBALLY,

	IS_SPEED_UPGRADE, // count = time (e.g. stim), 0 = permanent

	NOT_BUILDABLE,


	MAX_GAME_RESOURCE_TYPES
};

// TODO später noch in strings umwandeln oder so... für XML Dateien

#endif