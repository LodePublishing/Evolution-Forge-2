#include "core_directories.hpp"
#include <misc/singlestorage.hpp>
#include <misc/io.hpp>

class Game;
class Government;
class Location;
class Map;
class Player;
class Race;
class Rules;
class StartCondition;
class Units;
class UnitType;


void CoreDirectories::init() {
	SingleStorage<Game>::DATA_FILE_NAME = SingleStorage<Game>::DATA_FILE_NAME_BASE;
	SingleStorage<Government>::DATA_FILE_NAME = SingleStorage<Government>::DATA_FILE_NAME_BASE;
	SingleStorage<Location>::DATA_FILE_NAME = SingleStorage<Location>::DATA_FILE_NAME_BASE;
	SingleStorage<Map>::DATA_FILE_NAME = SingleStorage<Map>::DATA_FILE_NAME_BASE;
	SingleStorage<Player>::DATA_FILE_NAME = SingleStorage<Player>::DATA_FILE_NAME_BASE;
	SingleStorage<Race>::DATA_FILE_NAME = SingleStorage<Race>::DATA_FILE_NAME_BASE;
	SingleStorage<Rules>::DATA_FILE_NAME = SingleStorage<Rules>::DATA_FILE_NAME_BASE;
	SingleStorage<StartCondition>::DATA_FILE_NAME = SingleStorage<StartCondition>::DATA_FILE_NAME_BASE;
	SingleStorage<Units>::DATA_FILE_NAME = SingleStorage<Units>::DATA_FILE_NAME_BASE;
	SingleStorage<UnitType>::DATA_FILE_NAME = SingleStorage<UnitType>::DATA_FILE_NAME_BASE;
}

void CoreDirectories::initTemp(const std::string prefixDirectory) {
	SingleStorage<Game>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Game>::DATA_FILE_NAME_BASE;
	SingleStorage<Government>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Government>::DATA_FILE_NAME_BASE;
	SingleStorage<Location>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Location>::DATA_FILE_NAME_BASE;
	SingleStorage<Map>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Map>::DATA_FILE_NAME_BASE;
	SingleStorage<Player>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Player>::DATA_FILE_NAME_BASE;
	SingleStorage<Race>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Race>::DATA_FILE_NAME_BASE;
	SingleStorage<Rules>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Rules>::DATA_FILE_NAME_BASE;
	SingleStorage<StartCondition>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<StartCondition>::DATA_FILE_NAME_BASE;
	SingleStorage<Units>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<Units>::DATA_FILE_NAME_BASE;
	SingleStorage<UnitType>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<UnitType>::DATA_FILE_NAME_BASE;
}