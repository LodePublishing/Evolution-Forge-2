#ifndef _CORE_PATH_HPP
#define _CORE_PATH_HPP 

#define MAX_MAP_DISTANCE 9999

#include <sstream>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include "id.hpp"

class Path : public ID<Path>
{
public:

	Path(const unsigned int sourceLocationPosition, const unsigned int targetLocationPosition,
		const unsigned int locationDistance);
	~Path();

	bool operator< (const Path& ld) {
		return locationDistance < ld.locationDistance;
	}

	unsigned int getSourceLocationPosition() const;
	unsigned int getTargetLocationPosition() const;
	unsigned int getDistance() const;
	const std::string toString() const;

	

	static const char* const Source_tag_string;
	static const char* const Target_tag_string;
	static const char* const Distance_tag_string;

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Source_tag_string, sourceLocationPosition);
		ar & boost::serialization::make_nvp(Target_tag_string, targetLocationPosition);
		ar & boost::serialization::make_nvp(Distance_tag_string, locationDistance);
		// targetLocation needs to be reassigned!
		if(version > 0) {
		}
	}
	// only use for serialization / deserialization
	Path() {}

	unsigned int sourceLocationPosition;
	unsigned int targetLocationPosition;
	unsigned int locationDistance;
	
};


inline unsigned int Path::getDistance() const {
	return locationDistance;
}

inline unsigned int Path::getSourceLocationPosition() const {
	return sourceLocationPosition;
}

inline unsigned int Path::getTargetLocationPosition() const {
	return targetLocationPosition;
}

#endif // _CORE_PATH_HPP
