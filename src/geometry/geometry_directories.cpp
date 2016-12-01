#include "geometry_directories.hpp"
#include <misc/singlestorage.hpp>
#include <misc/io.hpp>

class WindowLayout;

void GeometryDirectories::init() {
	SingleStorage<WindowLayout>::DATA_FILE_NAME = SingleStorage<WindowLayout>::DATA_FILE_NAME_BASE;
}

void GeometryDirectories::initTemp(const std::string prefixDirectory) {
	SingleStorage<WindowLayout>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<WindowLayout>::DATA_FILE_NAME_BASE;
}