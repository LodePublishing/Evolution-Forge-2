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

#include <uuid.hpp>

class Path : public UUID<Path>
{
public:
	Path(const boost::uuids::uuid id,
		const unsigned int sourceLocationPosition, 
		const unsigned int targetLocationPosition,
		const unsigned int locationDistance);
	Path(const unsigned int sourceLocationPosition, 
		const unsigned int targetLocationPosition,
		const unsigned int locationDistance);
	~Path();

	bool operator< (const Path& ld) {
		return locationDistance < ld.locationDistance;
	}

	unsigned int getSourceLocationPosition() const;
	unsigned int getTargetLocationPosition() const;
	unsigned int getDistance() const;
	const std::string toString() const;

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Path* path, const unsigned int version) { 

		const boost::uuids::uuid& id = path->getId();
		const unsigned int& sourceLocationPosition = path->getSourceLocationPosition();
		const unsigned int& targetLocationPosition = path->getTargetLocationPosition();
		const unsigned int& locationDistance = path->getDistance();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(sourceLocationPosition)
		   & BOOST_SERIALIZATION_NVP(targetLocationPosition)
		   & BOOST_SERIALIZATION_NVP(locationDistance);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Path*& path, const unsigned int version)
	{
		boost::uuids::uuid id;
		unsigned int sourceLocationPosition;
		unsigned int targetLocationPosition;
		unsigned int locationDistance;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(sourceLocationPosition)
		   & BOOST_SERIALIZATION_NVP(targetLocationPosition)
		   & BOOST_SERIALIZATION_NVP(locationDistance);

		if(version > 0) {
		}

		::new(path)Path(id, sourceLocationPosition, targetLocationPosition, locationDistance);
	}

	const unsigned int sourceLocationPosition;
	const unsigned int targetLocationPosition;
	const unsigned int locationDistance;

	Path& operator=(const Path& other);
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
