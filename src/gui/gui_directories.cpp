#include "gui_directories.hpp"
#include <guicore/guicore_directories.hpp>
#include <lang/language_directories.hpp>
#include <misc/singlestorage.hpp>
#include <misc/io.hpp>

class GuiConfiguration;

void GuiDirectories::init() {
	SingleStorage<GuiConfiguration>::DATA_FILE_NAME = SingleStorage<GuiConfiguration>::DATA_FILE_NAME_BASE;

	GuiCoreDirectories::init();
	LanguageDirectories::init();
}

void GuiDirectories::initTemp(const std::string prefixDirectory) {
	SingleStorage<GuiConfiguration>::DATA_FILE_NAME = IO::getDirectory(boost::assign::list_of(prefixDirectory)) + SingleStorage<GuiConfiguration>::DATA_FILE_NAME_BASE;

	GuiCoreDirectories::init();
	LanguageDirectories::init();
}