#ifndef _CORE_ID_HPP
#define _CORE_ID_HPP

#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

// CRTP pattern

template <typename T> class ID
{
public:
	ID():id(ID_counter++) {}
	ID(const unsigned int id):id(id) {}

	virtual ~ID() {}

	unsigned int getId() const { return this->id; }
	const ID& operator=(const ID& other) { this->id = other.id; return *this; }

	static void resetCounter() { ID_counter = 0;}

protected:
	friend class boost::serialization::access;
	
	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(id);
		if(version > 0) {
		}
	}

	const unsigned int id;

	static unsigned int ID_counter;
};

template <typename T> unsigned int ID<T>::ID_counter = 0;


#endif // _CORE_ID_HPP