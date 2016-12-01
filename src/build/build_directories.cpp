#include "build_directories.hpp"

#include <core/core_directories.hpp>
#include <lang/language_directories.hpp>

#include <misc/singlestorage.hpp>
#include <misc/io.hpp>

#include "buildconfiguration.hpp"

class BuildConfiguration;

void BuildDirectories::init() {
	SingleStorage<BuildConfiguration>::DATA_FILE_NAME = SingleStorage<BuildConfiguration>::DATA_FILE_NAME_BASE;

	CoreDirectories::init();
	LanguageDirectories::init();
}

void BuildDirectories::initTemp(const std::string prefixDirectory) {
	SingleStorage<BuildConfiguration>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<BuildConfiguration>::DATA_FILE_NAME_BASE;

	CoreDirectories::init();
	LanguageDirectories::init();
}