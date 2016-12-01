#ifndef _BUILD_STORAGES_BUILDCONFIGURATION_STORAGE_HPP
#define _BUILD_STORAGES_BUILDCONFIGURATION_STORAGE_HPP

#include <misc/singlestorage.hpp>

class BuildConfiguration;

class BuildConfigurationStorage : public SingleStorage<BuildConfiguration>
{ };

#endif // _BUILD_STORAGES_BUILDCONFIGURATION_STORAGE_HPP