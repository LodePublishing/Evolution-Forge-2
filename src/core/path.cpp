#include <sstream>

#include "path.hpp"

Path::Path(const boost::uuids::uuid sourceLocationId, 
	const boost::uuids::uuid targetLocationId,
	const unsigned int locationDistance):

sourceLocationId(sourceLocationId),
	targetLocationId(targetLocationId),
	locationDistance(locationDistance)
{ }

Path::Path(const boost::uuids::uuid id,
	const boost::uuids::uuid sourceLocationId, 
	const boost::uuids::uuid targetLocationId,
	const unsigned int locationDistance):
UUID<Path>(id),
	sourceLocationId(sourceLocationId),
	targetLocationId(targetLocationId),
	locationDistance(locationDistance)
{ }

Path::~Path() 
{ }

const std::string Path::toString() const
{
	std::ostringstream os;
	os << sourceLocationId << " -> " << targetLocationId << " [" << locationDistance << "km]";
	return os.str();
}

