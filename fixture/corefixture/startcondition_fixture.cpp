#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

#include <misc/randomgenerator.hpp>

#include "startcondition_fixture.hpp"
#include <core/startcondition_storage.hpp>
#include <core/core_directories.hpp>

StartCondition_Fixture::StartCondition_Fixture():
	unitsFixture(),
	test_name("my startcondition" + RandomGenerator::instance().rndString()),
	test_startingTime(RandomGenerator::instance().rnd()),

	test_startcondition(new StartCondition(test_name, test_startingTime, unitsFixture.test_units, init_playerlist_helper())),
	test_startconditionMap(init_startconditionmap_helper())
{ 
	CoreDirectories::initTemp("temp");

	StartConditionStorage::instance(test_startconditionMap);	
}

StartCondition_Fixture::~StartCondition_Fixture()
{ 
	CoreDirectories::initTemp("temp");

	StartConditionStorage::clear();

	CoreDirectories::init();
}

const std::list<boost::shared_ptr<const Player> > StartCondition_Fixture::init_playerlist_helper() {
	std::list<boost::shared_ptr<const Player> > player_list;
	
	player_list.push_back(unitsFixture.playerFixture.test_player);
	
	return player_list;
}


const std::map<const boost::uuids::uuid, const boost::shared_ptr<const StartCondition> > StartCondition_Fixture::init_startconditionmap_helper() {
	std::map<const boost::uuids::uuid, const boost::shared_ptr<const StartCondition> > startConditionMap;
	startConditionMap.insert(std::pair<const boost::uuids::uuid, const boost::shared_ptr<const StartCondition> >(test_startcondition->getId(), test_startcondition));
	return startConditionMap;
}

	/*boost::shared_ptr<Unit> test_unit1(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[VESPENE_GEYSIR]), test_locations[0], test_units));
	boost::shared_ptr<Unit> test_unit2(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[VESPENE_GEYSIR]), test_locations[0], test_units));
	boost::shared_ptr<Unit> test_unit3(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[MINERAL_PATCH]), test_locations[3], test_units));
	boost::shared_ptr<Unit> test_unit4(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map[MINERAL_PATCH]), test_locations[3], test_units));


	playerFixture.test_player->getStartingUnits()->addUnit(test_unit1);
	playerFixture.test_player->getStartingUnits()->addUnit(test_unit2);
	playerFixture.test_player->getStartingUnits()->addUnit(test_unit3);
	playerFixture.test_player->getStartingUnits()->addUnit(test_unit4);*/