#include "mainconfiguration.hpp"
#include <misc/io.hpp>
#include <misc/miscellaneous.hpp>

MainConfiguration::MainConfiguration(
	const boost::uuids::uuid languageId, 
	const boost::uuids::uuid guiId, 
	const boost::uuids::uuid soundConfigurationId,
	const bool firstStart,
	const boost::shared_ptr<const Bitmap> backgroundBitmap,
	const bool dnaSpiral
	):
	UUID<MainConfiguration>(),
	languageId(languageId),
	guiId(guiId),
	soundConfigurationId(soundConfigurationId),
	firstStart(firstStart),
	backgroundBitmap(backgroundBitmap),
	dnaSpiral(dnaSpiral)
{ }

MainConfiguration::MainConfiguration(
        const boost::uuids::uuid id, 
		const boost::uuids::uuid languageId, 
		const boost::uuids::uuid guiId, 
		const boost::uuids::uuid soundConfigurationId,
		const bool firstStart,
		const boost::shared_ptr<const Bitmap> backgroundBitmap,
		const bool dnaSpiral
        ):
	UUID<MainConfiguration>(id),	
	languageId(languageId),
	guiId(guiId),
	soundConfigurationId(soundConfigurationId),
	firstStart(firstStart),
	backgroundBitmap(backgroundBitmap),
	dnaSpiral(dnaSpiral)
{ }

MainConfiguration::~MainConfiguration()
{ }