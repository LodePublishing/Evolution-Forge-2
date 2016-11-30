#ifndef _MISCFIXTURE_RANDOMFIXTURE_HPP
#define _MISCFIXTURE_RANDOMFIXTURE_HPP

#pragma warning(push, 0)
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp> 
#include <boost/uuid/uuid_generators.hpp>
#pragma warning(pop)

#include <singleton.hpp>

class Random_Fixture : public Singleton<Random_Fixture>
{
	friend class Singleton<Random_Fixture>;
public:
	unsigned int rnd();
	const boost::uuids::uuid uuid(std::string string);
	~Random_Fixture();
protected:		
	Random_Fixture(const Random_Fixture& other):seed(other.seed),generator(other.generator),distribution(other.distribution),rndgenerator(other.rndgenerator),gen(){}
private:
	Random_Fixture();
	time_t seed;
	boost::mt19937 generator;
	boost::uniform_int<> distribution;
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rndgenerator;
	boost::uuids::string_generator gen;
};

#endif // _MISCFIXTURE_RANDOMFIXTURE_HPP