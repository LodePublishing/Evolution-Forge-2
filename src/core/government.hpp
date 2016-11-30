#ifndef _CORE_GOVERNMENT_HPP
#define _CORE_GOVERNMENT_HPP

#include <string>

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include <uuid.hpp>

class Government : public UUID<Government>
{
public:
	Government(const std::string name);
	Government(const boost::uuids::uuid id, const std::string name);
	~Government();
	
	const std::string& getName() const;

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }	

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Government* government, const unsigned int version) { 

		const boost::uuids::uuid& id = government->getId();
		const std::string& name = government->getName();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Government*& government, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name);
		
		if(version > 0) {
		}

		::new(government)Government(id, name);
	}

	const std::string name;

	Government& operator=(const Government& other);
};

inline const std::string& Government::getName() const {
	return name;
}


#endif // _CORE_GOVERNMENT_HPP