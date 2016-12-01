#ifndef _CORE_STORAGES_GAME_STORAGE_HPP
#define _CORE_STORAGES_GAME_STORAGE_HPP

#include <misc/singlestorage.hpp>

class Game;

class GameStorage : public SingleStorage<Game>
{ };

#endif // _CORE_STORAGES_GAME_STORAGE_HPP