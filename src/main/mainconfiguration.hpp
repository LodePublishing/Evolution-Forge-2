#ifndef _MAIN_CONFIGURATION_HPP
#define _MAIN_CONFIGURATION_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>

#include <guicore/bitmap.hpp>

class MainConfiguration : public UUID<MainConfiguration>
{
public:
	MainConfiguration(const boost::uuids::uuid id, const boost::uuids::uuid languageId, const boost::uuids::uuid guiId, const boost::shared_ptr<const Bitmap> backgroundBitmap, bool dnaSpiral);
	MainConfiguration(const boost::uuids::uuid languageId, const boost::uuids::uuid guiId, const boost::shared_ptr<const Bitmap> backgroundBitmap, bool dnaSpiral);

	const boost::uuids::uuid& getLanguageId() const;
	const boost::uuids::uuid& getGuiId() const;
	const boost::shared_ptr<const Bitmap> getBackgroundBitmap() const;
	bool isDnaSpiral() const;
	
	~MainConfiguration();
private:

	const boost::uuids::uuid languageId;
	const boost::uuids::uuid guiId;
	const boost::shared_ptr<const Bitmap> backgroundBitmap;
	const bool dnaSpiral;

	MainConfiguration();
};

inline const boost::uuids::uuid& MainConfiguration::getLanguageId() const {
	return languageId;
}

inline const boost::uuids::uuid& MainConfiguration::getGuiId() const {
	return guiId;
}

inline const boost::shared_ptr<const Bitmap> MainConfiguration::getBackgroundBitmap() const {
	return backgroundBitmap;
}

inline bool MainConfiguration::isDnaSpiral() const {
	return dnaSpiral;
}

#endif // _MAIN_CONFIGURATION_HPP



