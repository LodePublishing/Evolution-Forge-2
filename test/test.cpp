#pragma warning(push, 0)  
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include <fstream>
#include <iostream>
#include <string>

class Object
{
public:
	Object(const unsigned int id,
		const std::string& name);
	~Object() {}	

	unsigned int getId() const {return id;}
	const std::string& getName() const {return name;}
	
private:
	friend class boost::serialization::access;
	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version) {
			// hier nur: Superklassen aufrufen! UUID etc.
		//ar  & BOOST_SERIALIZATION_BASE_OBJECT_NVP(UUID o.ae.);
	}

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Object *object, const unsigned int version) { 
		const unsigned int& id = object->getId();
		const std::string& name = object->getName();

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name);
	} 

	template<class Archive>
	friend inline void load_construct_data(Archive& ar, Object*& t, const unsigned int version) {
		unsigned int id;
		std::string name;

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name);
		
		::new(t)Object(id, name);
	}


    const unsigned int id;
	const std::string name;

	Object& operator=(const Object& other);
};

Object::Object(
	const unsigned int id,
	const std::string& name):
	id(id),
	name(name)
{ }

void saveToXML(const Object* tis , const std::string& filename, const std::string& name) {
	std::ofstream ofs(filename.c_str());
	boost::archive::xml_oarchive oa(ofs);
	oa << BOOST_SERIALIZATION_NVP(tis);
	ofs.close();
}

void loadFromXML(Object*& tis, const std::string& filename, const std::string& name) {
	std::ifstream ifs(filename.c_str());
	boost::archive::xml_iarchive ia(ifs);
	ia >> BOOST_SERIALIZATION_NVP(tis);
	ifs.close();
}


int main()
{
	// remove previously written files
	std::remove("test.txt");
	Object* object = new Object(1, "testobject");
	// save the object
	saveToXML(object, "test.txt", "testname");
	delete object;

	// reload the map
	Object* new_object2 = NULL;
	loadFromXML(new_object2, "test.txt", "testname");
	const boost::shared_ptr<Object> new_object(new_object2);

	std::remove("test.txt");
	std::cout << new_object->getId() << " / " << new_object->getName() << std::endl;
	int i;
	std::cin >> i;
}

