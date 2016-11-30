#ifndef _MISC_LOADSAVE_HPP
#define _MISC_LOADSAVE_HPP

#pragma warning(push, 0)
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 
#include <boost/serialization/nvp.hpp>
#pragma warning(pop)

#include <fstream>
#include <iostream>
#include <string>

template <class T>
class LoadSave
{
public:
	static void saveToXML(const T& tis , const std::string& filename, const std::string& name) {
		std::ofstream ofs(filename.c_str());
		boost::archive::xml_oarchive oa(ofs);
		oa << boost::serialization::make_nvp(name.c_str(), tis);
		ofs.close();
	}

	static void loadFromXML(T& tis, const std::string& filename, const std::string& name) {
		std::ifstream ifs(filename.c_str());
		boost::archive::xml_iarchive ia(ifs);
		ia >> boost::serialization::make_nvp(name.c_str(), tis);
		ifs.close();
	}
	static void saveToRAW(const T& tis, const std::string& filename){
		std::ofstream ofs(filename.c_str());
		boost::archive::text_oarchive oa(ofs);
		oa << tis;
		ofs.close();
	}
	static void loadFromRAW(T& tis, const std::string& filename){

		std::ifstream ifs(filename.c_str());
		boost::archive::text_iarchive ia(ifs);
		ia >> tis;
		ifs.close();
	}

protected:
	// ignore warning about non-virtual destructor: If it is protected then it is ok
	~LoadSave() {}
};

#endif // _MISC_LOADSAVE_HPP