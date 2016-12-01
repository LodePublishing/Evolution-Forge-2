#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE Core

#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)

#include <corefixture/game_fixture.hpp>
#include <corefixture/player_fixture.hpp>
#include <corefixture/rules_fixture.hpp>
#include <corefixture/map_fixture.hpp>
#include <corefixture/government_fixture.hpp>
#include <corefixture/location_fixture.hpp>
#include <corefixture/path_fixture.hpp>
#include <corefixture/race_fixture.hpp>
#include <corefixture/unittype_fixture.hpp>
#include <corefixture/unit_fixture.hpp>
#include <corefixture/startcondition_fixture.hpp>
#include <corefixture/unitresourcetype_fixture.hpp>
#include <corefixture/units_fixture.hpp>

#include <games/enums/broodwarunits.hpp>

#include <core/government_storage.hpp>
#include <core/location_storage.hpp>
#include <core/map_storage.hpp>
#include <core/game_storage.hpp>
#include <core/player_storage.hpp>
#include <core/race_storage.hpp>
#include <core/rules_storage.hpp>
#include <core/startcondition_storage.hpp>
#include <core/units_storage.hpp>
#include <core/unittype_storage.hpp>


BOOST_FIXTURE_TEST_SUITE( Government_test, Government_Fixture )

	BOOST_AUTO_TEST_CASE (Government_constructor)
{
	BOOST_CHECK_EQUAL(test_government->getName(), test_government_name);
}

BOOST_AUTO_TEST_CASE (Government_storage)
{
	BOOST_CHECK_EQUAL(GovernmentStorage::instance().get(test_government->getId())->getName(), test_government_name);

	GovernmentStorage::saveToXML();
	GovernmentStorage::reset();

	BOOST_CHECK_EQUAL(GovernmentStorage::instance().get(test_government->getId())->getName(), test_government_name);
}

BOOST_AUTO_TEST_SUITE_END( )


	BOOST_FIXTURE_TEST_SUITE( Location_test, Location_Fixture )

	BOOST_AUTO_TEST_CASE (Location_constructor)
{	
	BOOST_CHECK_EQUAL(test_location->getName(), test_name);		
	BOOST_CHECK_EQUAL(test_location->getX(), test_x);
	BOOST_CHECK_EQUAL(test_location->getY(), test_y);
	BOOST_REQUIRE(test_location->getPaths().size() > 0);
	BOOST_CHECK_EQUAL(test_location->getPaths().front()->getSourceLocationId(), test_location->getId());
	BOOST_CHECK_EQUAL(test_location->getPaths().front()->getTargetLocationId(), test_target_location->getId());
	BOOST_CHECK_EQUAL(test_location->getPaths().front()->getDistance(), test_path->getDistance());
}

BOOST_AUTO_TEST_CASE (Location_toString)
{
	std::ostringstream os;
	os << "Location Name: " << test_name << std::endl << "Distances: ";
	for(std::list<boost::shared_ptr<const Path> >::const_iterator i = test_location->getPaths().begin(); i != test_location->getPaths().end(); i++) {
		os << (*i)->toString() << ", ";
	}
	os << std::endl;	
	BOOST_CHECK_EQUAL(test_location->toString(), os.str());
}

BOOST_AUTO_TEST_CASE (Location_storage)
{
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getName(), test_name);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getName(), test_target_name);

	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getX(), test_x);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getY(), test_y);
	BOOST_REQUIRE(LocationStorage::instance().get(test_location->getId())->getPaths().size() > 0);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getPaths().front()->getSourceLocationId(), test_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getPaths().front()->getTargetLocationId(), test_target_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getPaths().front()->getDistance(), test_path->getDistance());

	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getX(), test_target_x);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getY(), test_target_y);
	BOOST_REQUIRE(LocationStorage::instance().get(test_target_location->getId())->getPaths().size() > 0);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getPaths().front()->getSourceLocationId(), test_target_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getPaths().front()->getTargetLocationId(), test_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getPaths().front()->getDistance(), test_path->getDistance());

	LocationStorage::saveToXML();
	LocationStorage::reset();

	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getName(), test_name);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getName(), test_target_name);

	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getX(), test_x);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getY(), test_y);
	BOOST_REQUIRE(LocationStorage::instance().get(test_location->getId())->getPaths().size() > 0);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getPaths().front()->getSourceLocationId(), test_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getPaths().front()->getTargetLocationId(), test_target_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_location->getId())->getPaths().front()->getDistance(), test_path->getDistance());

	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getX(), test_target_x);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getY(), test_target_y);
	BOOST_REQUIRE(LocationStorage::instance().get(test_target_location->getId())->getPaths().size() > 0);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getPaths().front()->getSourceLocationId(), test_target_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getPaths().front()->getTargetLocationId(), test_location->getId());
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_target_location->getId())->getPaths().front()->getDistance(), test_path->getDistance());
}



BOOST_AUTO_TEST_SUITE_END( )


	BOOST_FIXTURE_TEST_SUITE( Map_test, Map_Fixture )

	BOOST_AUTO_TEST_CASE ( Map_constructor_test )
{
	BOOST_CHECK_EQUAL(test_map->getName(), test_map_name);
	BOOST_CHECK_EQUAL(test_map->getLocationVector().size(), 4);

	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(0)->getAirDistance(test_map->getLocationByIndex(1)), 999);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(0)->getAirDistance(test_map->getLocationByIndex(2)), 2234);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(0)->getAirDistance(test_map->getLocationByIndex(3)), 999);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(1)->getAirDistance(test_map->getLocationByIndex(2)), 1413);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(1)->getAirDistance(test_map->getLocationByIndex(3)), 1412);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(2)->getAirDistance(test_map->getLocationByIndex(3)), 1999);

	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(0)->getGroundDistance(test_map->getLocationByIndex(1)), 1100);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(0)->getGroundDistance(test_map->getLocationByIndex(2)), 2300);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(0)->getGroundDistance(test_map->getLocationByIndex(3)), 1400);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(1)->getGroundDistance(test_map->getLocationByIndex(2)), 1200);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(1)->getGroundDistance(test_map->getLocationByIndex(3)), 2400);
	BOOST_CHECK_EQUAL(test_map->getLocationByIndex(2)->getGroundDistance(test_map->getLocationByIndex(3)), 1300);
}

BOOST_AUTO_TEST_CASE( Map_invalid_locations_test )
{
	const boost::shared_ptr<Location> ind_location(boost::shared_ptr<Location>(new Location("test", 3, 3)));
	BOOST_CHECK_THROW(test_map->getLocationByIndex(0)->getGroundDistance(ind_location), std::exception);
}

BOOST_AUTO_TEST_CASE( Map_location_index_test ) 
{
	BOOST_CHECK_THROW(test_map->getLocationIndex(boost::uuids::nil_uuid()), std::exception);
}

BOOST_AUTO_TEST_CASE( Map_location_position_test ) 
{
	BOOST_CHECK_THROW(test_map->getLocation(boost::uuids::nil_uuid()), std::exception);
}

BOOST_AUTO_TEST_CASE( Map_location_id_test ) 
{
	BOOST_CHECK_THROW(test_map->getLocationId(99), std::exception);
}

BOOST_AUTO_TEST_CASE (Map_storage)
{
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getName(), test_map_name);
	BOOST_CHECK_EQUAL(LocationStorage::instance(test_locationMap).get(test_locations[0]->getId())->getName(), test_location_name[0]);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[1]->getId())->getName(), test_location_name[1]);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[2]->getId())->getName(), test_location_name[2]);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[3]->getId())->getName(), test_location_name[3]);

	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocation(test_locations[2]->getId())->getName(), test_location_name[2]);

	MapStorage::saveToXML();
	MapStorage::reset();

	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getName(), test_map_name);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[0]->getId())->getName(), test_location_name[0]);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[1]->getId())->getName(), test_location_name[1]);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[2]->getId())->getName(), test_location_name[2]);
	BOOST_CHECK_EQUAL(LocationStorage::instance().get(test_locations[3]->getId())->getName(), test_location_name[3]);

	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocation(test_locations[2]->getId())->getName(), test_location_name[2]);

	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(0)->getAirDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(1)), 999);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(0)->getAirDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(2)), 2234);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(0)->getAirDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(3)), 999);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(1)->getAirDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(2)), 1413);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(1)->getAirDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(3)), 1412);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(2)->getAirDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(3)), 1999);

	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(0)->getGroundDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(1)), 1100);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(0)->getGroundDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(2)), 2300);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(0)->getGroundDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(3)), 1400);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(1)->getGroundDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(2)), 1200);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(1)->getGroundDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(3)), 2400);
	BOOST_CHECK_EQUAL(MapStorage::instance().get(test_map->getId())->getLocationByIndex(2)->getGroundDistance(MapStorage::instance().get(test_map->getId())->getLocationByIndex(3)), 1300);
}

BOOST_AUTO_TEST_SUITE_END( )


	BOOST_FIXTURE_TEST_SUITE( Path_test, Path_Fixture )

	BOOST_AUTO_TEST_CASE (Path_constructor )
{
	BOOST_CHECK_EQUAL(test_path->getDistance(), test_distance);
	BOOST_CHECK_EQUAL(test_path->getSourceLocationId(), test_source_location_id);
	BOOST_CHECK_EQUAL(test_path->getTargetLocationId(), test_target_location_id);
}

BOOST_AUTO_TEST_CASE (Path_toString )
{
	std::ostringstream os;
	os << test_source_location_id << " -> " << test_target_location_id << " [" << test_distance << "km]";

	BOOST_CHECK_EQUAL(test_path->toString(), os.str());
}

BOOST_AUTO_TEST_SUITE_END( )


	BOOST_FIXTURE_TEST_SUITE( Player_test, Player_Fixture )

	BOOST_AUTO_TEST_CASE (Player_constructor)
{
	BOOST_CHECK_EQUAL(test_player->getName(), test_player_name);
	BOOST_CHECK_EQUAL(test_player->getGovernment()->getName(), governmentFixture.test_government_name);
}


BOOST_AUTO_TEST_CASE (Player_storage)
{
	BOOST_CHECK_EQUAL(PlayerStorage::instance().get(test_player->getId())->getName(), test_player_name);
	BOOST_CHECK_EQUAL(PlayerStorage::instance().get(test_player->getId())->getGovernment()->getName(), governmentFixture.test_government_name);

	PlayerStorage::saveToXML();
	PlayerStorage::reset();

	BOOST_CHECK_EQUAL(PlayerStorage::instance().get(test_player->getId())->getName(), test_player_name);
	BOOST_CHECK_EQUAL(PlayerStorage::instance().get(test_player->getId())->getGovernment()->getName(), governmentFixture.test_government_name);
}

BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE( Race_test, Race_Fixture )

	BOOST_AUTO_TEST_CASE (Race_constructor )
{
	BOOST_CHECK_EQUAL(test_race->getName(), test_race_name);
}

BOOST_AUTO_TEST_CASE (Race_storage)
{
	BOOST_CHECK_EQUAL(RaceStorage::instance().get(test_race->getId())->getName(), test_race_name);

	RaceStorage::saveToXML();
	RaceStorage::reset();

	BOOST_CHECK_EQUAL(RaceStorage::instance().get(test_race->getId())->getName(), test_race_name);
}


BOOST_AUTO_TEST_SUITE_END( )


	BOOST_FIXTURE_TEST_SUITE( StartCondition_test, StartCondition_Fixture )

	BOOST_AUTO_TEST_CASE (StartCondition_constructor)
{
	BOOST_CHECK_EQUAL(test_startcondition->getName(), test_name);
	BOOST_CHECK_EQUAL(test_startcondition->getStartingTime(), test_startingTime);
	BOOST_CHECK_EQUAL(test_startcondition->getPlayer(unitsFixture.playerFixture.test_player->getId())->getId(), unitsFixture.playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(test_startcondition->getPlayerIdList().back(), unitsFixture.playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(test_startcondition->getUnitsId(), unitsFixture.test_units->getId());
	BOOST_CHECK_EQUAL(test_startcondition->getUnits()->getId(), unitsFixture.test_units->getId());
}

BOOST_AUTO_TEST_CASE (StartCondition_storage)
{
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getName(), test_name);
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getStartingTime(), test_startingTime);
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getPlayer(unitsFixture.playerFixture.test_player->getId())->getId(), unitsFixture.playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getPlayerIdList().back(), unitsFixture.playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getUnitsId(), unitsFixture.test_units->getId());
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getUnits()->getId(), unitsFixture.test_units->getId());

	StartConditionStorage::saveToXML();
	StartConditionStorage::reset();

	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getName(), test_name);
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getStartingTime(), test_startingTime);
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getPlayer(unitsFixture.playerFixture.test_player->getId())->getId(), unitsFixture.playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getPlayerIdList().back(), unitsFixture.playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getUnitsId(), unitsFixture.test_units->getId());
	BOOST_CHECK_EQUAL(StartConditionStorage::instance().get(test_startcondition->getId())->getUnits()->getId(), unitsFixture.test_units->getId());
}


BOOST_AUTO_TEST_SUITE_END( )



	BOOST_FIXTURE_TEST_SUITE( UnitResourceType_test, UnitResourceType_Fixture )

	BOOST_AUTO_TEST_CASE (UnitResourceType_constructor)
{
	BOOST_CHECK_EQUAL(test_unitResourceType->getResourceType(), test_eUnitResourceType);
	BOOST_CHECK_EQUAL(test_unitResourceType->getAmount(), test_amount);
	BOOST_REQUIRE_EQUAL(test_unitResourceType->getUnitTypeIdList().size(), test_unitTypeIdList.size());
	BOOST_CHECK_EQUAL(test_unitResourceType->getUnitTypeIdList().front().front(), test_unitTypeIdList.front().front());
	BOOST_CHECK_EQUAL(test_unitResourceType->getUnitTypeIdList().front().back(), test_unitTypeIdList.front().back());
	BOOST_CHECK_EQUAL(test_unitResourceType->getUnitTypeIdList().back().front(), test_unitTypeIdList.back().front());

}


BOOST_AUTO_TEST_SUITE_END( )


	BOOST_FIXTURE_TEST_SUITE( Units_test, Units_Fixture )

	BOOST_AUTO_TEST_CASE (Units_constructor )
{
	//TODO evtl UNITs einzeln direkt nur intern in 'units' erstellen...

	const UnitLocalKey localKey1 = test_unit1->getLocalKey();
	const UnitLocalKey localKey2 = test_unit2->getLocalKey();
	const UnitLocalKey localKey3 = test_unit3->getLocalKey();

	const UnitGlobalKey globalKey1 = test_unit1->getGlobalKey();
	const UnitGlobalKey globalKey2 = test_unit2->getGlobalKey();
	const UnitGlobalKey globalKey3 = test_unit3->getGlobalKey();

	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey3), 1);

	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey3), 1);

	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey3), 1);

	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey1), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey2), 2);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey3), 1);
}

BOOST_AUTO_TEST_CASE (Units_addremove ) 
{
	const UnitLocalKey localKey1 = test_unit1->getLocalKey();
	const UnitLocalKey localKey2 = test_unit2->getLocalKey();
	const UnitLocalKey localKey3 = test_unit3->getLocalKey();

	const UnitGlobalKey globalKey1 = test_unit1->getGlobalKey();
	const UnitGlobalKey globalKey2 = test_unit2->getGlobalKey();
	const UnitGlobalKey globalKey3 = test_unit3->getGlobalKey();

	test_units->removeUnit(test_unit2);
	test_units->removeUnit(test_unit3);

	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey3), 0);

	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey3), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey3), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey1), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey2), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey3), 0);

	// start building unit 4 at facility unit 1

	std::list<boost::shared_ptr<Unit> > unit_list;
	unit_list.push_back(test_unit1);

	// unit to build
	boost::shared_ptr<Unit> test_unit4(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(SPACE_MARINE)->second), locationFixture.test_location, test_units, 1, test_construction_time, unit_list)));
	test_units->addUnit(test_unit4);

	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(test_unit1->getLocalKey()), 0);
	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(test_unit4->getLocalKey()), 0);

	BOOST_CHECK_EQUAL(test_units->getLocalTotal(test_unit1->getLocalKey()), 1);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(test_unit4->getLocalKey()), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(test_unit1->getGlobalKey()), 0);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(test_unit4->getGlobalKey()), 0);

	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(test_unit1->getGlobalKey()), 1);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(test_unit4->getGlobalKey()), 0);
	// todo neutral
	// TODO test removing facility where units currently build
	// TODO test removing units that are currently being built
}

BOOST_AUTO_TEST_CASE (Units_add_units ) 
{
	boost::shared_ptr<Units> test_units2(boost::shared_ptr<Units>(new Units()));
	// unit to build
	boost::shared_ptr<Unit> test_unit5(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(SCV)->second), locationFixture.test_location, test_units2)));
	test_units2->addUnit(test_unit5);
	// unit to build
	boost::shared_ptr<Unit> test_unit6(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(SPACE_MARINE)->second), locationFixture.test_location, test_units2)));
	test_units2->addUnit(test_unit6);

	test_units->addUnits(test_units2->getUnitList());

	const UnitLocalKey localKey = test_unit5->getLocalKey();
	const UnitGlobalKey globalKey = test_unit5->getGlobalKey();

	BOOST_CHECK_EQUAL(test_units->getLocalAvailable(localKey), 3);
	BOOST_CHECK_EQUAL(test_units->getLocalTotal(localKey), 3);
	BOOST_CHECK_EQUAL(test_units->getGlobalAvailable(globalKey), 3);
	BOOST_CHECK_EQUAL(test_units->getGlobalTotal(globalKey), 3);
}

BOOST_AUTO_TEST_CASE (Units_storage)
{
	const UnitLocalKey localKey1 = test_unit1->getLocalKey();
	const UnitLocalKey localKey2 = test_unit2->getLocalKey();
	const UnitLocalKey localKey3 = test_unit3->getLocalKey();

	const UnitGlobalKey globalKey1 = test_unit1->getGlobalKey();
	const UnitGlobalKey globalKey2 = test_unit2->getGlobalKey();
	const UnitGlobalKey globalKey3 = test_unit3->getGlobalKey();


	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalAvailable(localKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalAvailable(localKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalAvailable(localKey3), 1);

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalTotal(localKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalTotal(localKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalTotal(localKey3), 1);

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalAvailable(globalKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalAvailable(globalKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalAvailable(globalKey3), 1);

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalTotal(globalKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalTotal(globalKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalTotal(globalKey3), 1);


	UnitsStorage::saveToXML();
	UnitsStorage::reset();

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalAvailable(localKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalAvailable(localKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalAvailable(localKey3), 1);

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalTotal(localKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalTotal(localKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getLocalTotal(localKey3), 1);

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalAvailable(globalKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalAvailable(globalKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalAvailable(globalKey3), 1);

	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalTotal(globalKey1), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalTotal(globalKey2), 2);
	BOOST_CHECK_EQUAL(UnitsStorage::instance().get(test_units->getId())->getGlobalTotal(globalKey3), 1);
}

BOOST_AUTO_TEST_SUITE_END( )



	BOOST_FIXTURE_TEST_SUITE( UnitType_test, UnitType_Fixture )

	BOOST_AUTO_TEST_CASE (UnitType_constructor )
{
	BOOST_CHECK_EQUAL(test_unittype->getMovementType(), test_unitMovementType);
	BOOST_CHECK_EQUAL(test_unittype->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(test_unittype->isCorporeal(), true);
	BOOST_CHECK_EQUAL(test_unittype->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(test_unittype->getName(), test_unitName1);
	BOOST_CHECK_EQUAL(test_unittype->getRace()->getName(), raceFixture.test_race_name);

	BOOST_CHECK_EQUAL(test_unittype->getResources().front().getAmount(), test_amount1);
	BOOST_CHECK_EQUAL(test_unittype->getResources().back().getAmount(), test_amount3);

	std::list<UnitResourceType> unitResourceType = test_unittype->getResources();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType1);

	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID1);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().back().front(), test_unitID3);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID4);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().back(), test_unitID5);
}

BOOST_AUTO_TEST_CASE (UnitType_notcorporeal_constructor )
{
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->getName(), test_unitName2);
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->getRace()->getName(), raceFixture.test_race_name);
	BOOST_CHECK_EQUAL(test_unittype_noncorporeal->isCorporeal(), false);

	std::list<UnitResourceType> unitResourceType = test_unittype_noncorporeal->getResources();

	BOOST_CHECK_EQUAL(unitResourceType.front().getAmount(), test_amount1);
	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType1);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID1);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getAmount(), test_amount2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().back().front(), test_unitID3);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getAmount(), test_amount3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID4);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().back(), test_unitID5);
}

BOOST_AUTO_TEST_CASE (UnitType_storage)
{
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getName(), test_unitName1);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype_noncorporeal->getId())->getName(), test_unitName2);

	UnitTypeStorage::saveToXML();
	UnitTypeStorage::reset();

	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getName(), test_unitName1);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype_noncorporeal->getId())->getName(), test_unitName2);

	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getMovementType(), test_unitMovementType);

	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->isCorporeal(), true);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getMaxCount(), test_maxcount);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getName(), test_unitName1);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getRace()->getName(), raceFixture.test_race_name);

	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getResources().front().getAmount(), test_amount1);
	BOOST_CHECK_EQUAL(UnitTypeStorage::instance().get(test_unittype->getId())->getResources().back().getAmount(), test_amount3);

	std::list<UnitResourceType> unitResourceType = UnitTypeStorage::instance().get(test_unittype->getId())->getResources();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType1);

	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID1);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID2);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().back().front(), test_unitID3);
	unitResourceType.pop_front();

	BOOST_CHECK_EQUAL(unitResourceType.front().getResourceType(), test_resourceType3);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().front(), test_unitID4);
	BOOST_CHECK_EQUAL(unitResourceType.front().getUnitTypeIdList().front().back(), test_unitID5);
}

BOOST_AUTO_TEST_SUITE_END( )



	BOOST_FIXTURE_TEST_SUITE( Gametest, Game_Fixture )

	BOOST_AUTO_TEST_CASE (Game_constructor)
{
	BOOST_CHECK_EQUAL(test_game->getMap()->getName(), mapFixture.test_map_name);
	BOOST_CHECK_EQUAL(test_game->getMap()->getId(), mapFixture.test_map->getId());
	BOOST_CHECK_EQUAL(test_game->getRules()->getName(), startConditionFixture.unitsFixture.broodwar.getRules()->getName());
	BOOST_CHECK_EQUAL(test_game->getRules()->getId(), startConditionFixture.unitsFixture.broodwar.getRules()->getId());
	BOOST_CHECK_EQUAL(test_game->getStartCondition()->getName(), startConditionFixture.test_startcondition->getName());
	BOOST_CHECK_EQUAL(test_game->getStartConditionId(), startConditionFixture.test_startcondition->getId());
}


BOOST_AUTO_TEST_CASE (Game_storage)
{
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getMap()->getName(), mapFixture.test_map_name);
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getMap()->getId(), mapFixture.test_map->getId());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getRules()->getName(), startConditionFixture.unitsFixture.broodwar.getRules()->getName());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getRules()->getId(), startConditionFixture.unitsFixture.broodwar.getRules()->getId());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getStartCondition()->getName(), startConditionFixture.test_startcondition->getName());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getStartConditionId(), startConditionFixture.test_startcondition->getId());
	
	GameStorage::saveToXML();
	GameStorage::reset();

	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getMap()->getName(), mapFixture.test_map_name);
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getMap()->getId(), mapFixture.test_map->getId());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getRules()->getName(), startConditionFixture.unitsFixture.broodwar.getRules()->getName());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getRules()->getId(), startConditionFixture.unitsFixture.broodwar.getRules()->getId());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getStartCondition()->getName(), startConditionFixture.test_startcondition->getName());
	BOOST_CHECK_EQUAL(GameStorage::instance().get(test_game->getId())->getStartConditionId(), startConditionFixture.test_startcondition->getId());
}

BOOST_AUTO_TEST_SUITE_END( )



	BOOST_FIXTURE_TEST_SUITE( Rules_test, Rules_Fixture )

	BOOST_AUTO_TEST_CASE (Rules_constructor)
{
	BOOST_CHECK_EQUAL(test_rules->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(test_rules->getRace(unitTypeFixture.raceFixture.test_race->getId())->getName(), unitTypeFixture.raceFixture.test_race->getName());
	BOOST_CHECK_EQUAL(test_rules->getUnitType(unitTypeFixture.test_unittype->getId())->getName(), unitTypeFixture.test_unittype->getName());
	BOOST_CHECK_EQUAL(test_rules->getUnitType(unitTypeFixture.test_unittype_noncorporeal->getId())->getName(), unitTypeFixture.test_unittype_noncorporeal->getName());
}

BOOST_AUTO_TEST_CASE (Rules_storage)
{
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getRace(unitTypeFixture.raceFixture.test_race->getId())->getName(), unitTypeFixture.raceFixture.test_race->getName());
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getUnitType(unitTypeFixture.test_unittype->getId())->getName(), unitTypeFixture.test_unittype->getName());
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getUnitType(unitTypeFixture.test_unittype_noncorporeal->getId())->getName(), unitTypeFixture.test_unittype_noncorporeal->getName());

	RulesStorage::saveToXML();
	RulesStorage::reset();

	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getName(), test_rules_name);
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getRace(unitTypeFixture.raceFixture.test_race->getId())->getName(), unitTypeFixture.raceFixture.test_race->getName());
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getUnitType(unitTypeFixture.test_unittype->getId())->getName(), unitTypeFixture.test_unittype->getName());
	BOOST_CHECK_EQUAL(RulesStorage::instance().get(test_rules->getId())->getUnitType(unitTypeFixture.test_unittype_noncorporeal->getId())->getName(), unitTypeFixture.test_unittype_noncorporeal->getName());
}

BOOST_AUTO_TEST_SUITE_END( )


	// MEMORY LEAK!
	BOOST_FIXTURE_TEST_SUITE( Unit_test, Unit_Fixture )

	BOOST_AUTO_TEST_CASE (Unit_constructor )
{
	BOOST_CHECK_EQUAL(test_unit->isConstructing(), false);
	BOOST_CHECK_EQUAL(test_unit->getUnitTypeId(), test_unitType->getId());
	BOOST_CHECK_EQUAL(test_unit->getRemainingConstructionTime(), 0);
	BOOST_CHECK_EQUAL(test_unit->getLocationId(), mapFixture.test_map->getLocationByIndex(0)->getId());
}

BOOST_AUTO_TEST_CASE(Unit_process)
{
	std::list<boost::shared_ptr<Unit> > unit_list;
	unit_list.push_back(test_unit);

	// marine
	boost::shared_ptr<Unit> test_unit2(boost::shared_ptr<Unit>(new Unit(playerFixture.test_player, broodwar.getRules()->getUnitType(broodwar.unit_id_map.find(SPACE_MARINE)->second), mapFixture.test_map->getLocationByIndex(0), test_units, 1, test_constructionTime, unit_list)));
	test_units->addUnit(test_unit2);

	BOOST_CHECK_EQUAL(test_unit2->getLocation()->getName(), mapFixture.test_map->getLocationByIndex(0)->getName());
	BOOST_CHECK_EQUAL(test_unit2->getPlayerId(), playerFixture.test_player->getId());
	BOOST_CHECK_EQUAL(test_unit2->getRemainingConstructionTime(), test_constructionTime);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingMovementTime(), 0);
	BOOST_CHECK_EQUAL(test_unit2->isUnderConstruction(), true);
	BOOST_CHECK_EQUAL(test_unit->isConstructing(), true);

	for(unsigned int i = 0; i < test_constructionTime; i++) {
		test_units->process();
	}
	BOOST_CHECK_EQUAL(test_unit2->isUnderConstruction(), false);
	BOOST_CHECK_EQUAL(test_unit->isConstructing(), false);

	test_unit->setGoalLocation(mapFixture.test_map->getLocationByIndex(0));
	test_unit2->setGoalLocation(mapFixture.test_map->getLocationByIndex(0));
	BOOST_CHECK_EQUAL(test_unit->getRemainingMovementTime(), 0);
	BOOST_CHECK_EQUAL(test_unit2->getRemainingMovementTime(), 0);

	test_unit->setGoalLocation(mapFixture.test_map->getLocationByIndex(0));
	test_unit2->setGoalLocation(mapFixture.test_map->getLocationByIndex(1));
	unsigned int distance1 = mapFixture.test_map->getLocationByIndex(0)->getGroundDistance(mapFixture.test_map->getLocationByIndex(1));
	unsigned int distance2 = mapFixture.test_map->getLocationByIndex(0)->getAirDistance(mapFixture.test_map->getLocationByIndex(2));
	unsigned int time1 = distance1 / test_unit->getUnitType()->getSpeed();
	unsigned int time2 = distance2 / test_unit2->getUnitType()->getSpeed();

	for(unsigned int i = 0; i < time1; i++) {
		test_unit->process();
	}
	BOOST_CHECK_EQUAL(test_unit->getLocation()->getName(), mapFixture.test_map->getLocationByIndex(0)->getName());

	for(unsigned int i = 0; i < time2; i++) {
		test_unit2->process();
	}
	BOOST_CHECK_EQUAL(test_unit2->getLocation()->getName(), mapFixture.test_map->getLocationByIndex(1)->getName());


	// unit to build and then cancel
	// Unit* test_unit3 = new Unit(unitType2,  test_player, mapFixture.locations[1], test_construction_time, unit_list);

	// Location* temp_location = test_unit3->getLocation();
	// UnitLocalKey localKey = test_unit3->getLocalKey();

	// BOOST_CHECK_EQUAL(temp_location->getGlobalUnits()->getLocalTotal(localKey), 1);
	// BOOST_CHECK_EQUAL(test_unit1->isConstructing(), true);
	// delete test_unit3; // calls cancelConstruction
	// BOOST_CHECK_EQUAL(temp_location->getGlobalUnits()->getLocalTotal(localKey), 0);
	// BOOST_CHECK_EQUAL(test_unit1->isConstructing(), false);
	// TODO
}


BOOST_AUTO_TEST_SUITE_END( )