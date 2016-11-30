#include <sstream>

#include "path.hpp"
#include "location.hpp"

Path::Path(const unsigned int sourceLocationPosition, const unsigned int targetLocationPosition,
		const unsigned int locationDistance):
	sourceLocationPosition(sourceLocationPosition),
	targetLocationPosition(targetLocationPosition),
	locationDistance(locationDistance)
{
}

Path::Path(const boost::uuids::uuid id,
	const unsigned int sourceLocationPosition, 
	const unsigned int targetLocationPosition,
	const unsigned int locationDistance):
	UUID<Path>(id),
	sourceLocationPosition(sourceLocationPosition),
	targetLocationPosition(targetLocationPosition),
	locationDistance(locationDistance)
{
}

Path::~Path() 
{}

const std::string Path::toString() const
{
	std::ostringstream os;
	os << sourceLocationPosition << " -> " << targetLocationPosition << " [" << locationDistance << "km]";
	return os.str();
}