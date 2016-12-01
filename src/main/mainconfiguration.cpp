#include "mainconfiguration.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <misc/miscellaneous.hpp>
#include <misc/io.hpp>

#pragma warning(push, 0)
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

MainConfiguration::MainConfiguration()
{ 
	loadFromXML(this, DATA_FILE_NAME, DATA_FILE_IDENTIFIER);
}

MainConfiguration::~MainConfiguration()
{ 
	saveToXML(this, DATA_FILE_NAME, DATA_FILE_IDENTIFIER);
}

const boost::shared_ptr<const MainConfiguration> MainConfiguration::defaultConfiguration = boost::shared_ptr<const MainConfiguration>(new 
	MainConfiguration(Misc::uuid("5e856d90-261b-11e0-ac64-0800200c9a66"), Size(640, 480), DEPTH_32BIT, false, 30, 75, false, true, false, boost::uuids::nil_uuid(), true, true, true, true));

const std::string MainConfiguration::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of("settings")) + "main.xml";
const std::string MainConfiguration::DATA_FILE_IDENTIFIER = "MainConfiguration";