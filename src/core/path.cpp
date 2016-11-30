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

Path::~Path() 
{}

const std::string Path::toString() const
{
	std::ostringstream os;
	os << sourceLocationPosition << " -> " << targetLocationPosition << " [" << locationDistance << "km]";
	return os.str();
}

const char* const Path::Source_tag_string = "source";
const char* const Path::Target_tag_string = "target";
const char* const Path::Distance_tag_string = "distance";