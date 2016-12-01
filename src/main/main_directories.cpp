#include "main_directories.hpp"
#include <guicore/guicore_directories.hpp>
#include <lang/language_directories.hpp>
#include <gui/gui_directories.hpp>
#include <misc/singlestorage.hpp>
#include <misc/io.hpp>

class MainConfiguration;

void MainDirectories::init() {
	SingleStorage<MainConfiguration>::DATA_FILE_NAME = SingleStorage<MainConfiguration>::DATA_FILE_NAME_BASE;

	GuiDirectories::init();
	GuiCoreDirectories::init();
	LanguageDirectories::init();
}

void MainDirectories::initTemp(const std::string prefixDirectory) {
	SingleStorage<MainConfiguration>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<MainConfiguration>::DATA_FILE_NAME_BASE;

	GuiDirectories::init();
	GuiCoreDirectories::init();
	LanguageDirectories::init();
}