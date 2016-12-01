#ifndef _CORE_PATH_HPP
#define _CORE_PATH_HPP 

#define MAX_MAP_DISTANCE 9999

#include <misc/uuid.hpp>

class Path : public UUID<Path>
{
public:
	Path(const boost::uuids::uuid id,
		const boost::uuids::uuid sourceLocationId, 
		const boost::uuids::uuid targetLocationId,
		const unsigned int locationDistance);
	Path(const boost::uuids::uuid sourceLocationId, 
		const boost::uuids::uuid targetLocationId,
		const unsigned int locationDistance);
	~Path();

	bool operator< (const Path& ld) {
		return locationDistance < ld.locationDistance;
	}

	const boost::uuids::uuid getSourceLocationId() const;
	const boost::uuids::uuid getTargetLocationId() const;
	unsigned int getDistance() const;
	const std::string toString() const;

private:
	const boost::uuids::uuid sourceLocationId;
	const boost::uuids::uuid targetLocationId;
	const unsigned int locationDistance;

	Path& operator=(const Path& other);
};

inline unsigned int Path::getDistance() const {
	return locationDistance;
}

inline const boost::uuids::uuid Path::getSourceLocationId() const {
	return sourceLocationId;
}

inline const boost::uuids::uuid Path::getTargetLocationId() const {
	return targetLocationId;
}


#endif // _CORE_PATH_HPP
