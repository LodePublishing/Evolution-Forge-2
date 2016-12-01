#ifndef _GUI_STORAGES_GUI_STORAGE_HPP
#define _GUI_STORAGES_GUI_STORAGE_HPP

#include <misc/singlestorage.hpp>

class Gui;

class GuiStorage : public SingleStorage<Gui>
{ };

#endif // _GUI_STORAGES_GUI_STORAGE_HPP