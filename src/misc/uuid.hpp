#ifndef _MISC_UUID_HPP
#define _MISC_UUID_HPP

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include <boost/uuid/uuid_serialize.hpp>
#pragma warning(pop)


template <typename T> 
class UUID
{
public:
	UUID():uuid(boost::uuids::random_generator()()) {}
	UUID(const boost::uuids::uuid uuid):uuid(uuid) {}

	virtual ~UUID() {}

	const boost::uuids::uuid getId() const { return this->uuid; }
	const UUID& operator=(const UUID& other) { this->uuid = other.uuid; return *this; }	

protected:
	friend class boost::serialization::access;
	
	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(uuid);
		if(version > 0) {
		}
	}

	const boost::uuids::uuid uuid;
};

#endif // _MISC_UUID_HPP