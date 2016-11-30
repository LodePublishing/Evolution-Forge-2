#ifndef _MISCFIXTURE_RANDOMFIXTURE_HPP
#define _MISCFIXTURE_RANDOMFIXTURE_HPP

#pragma warning(push, 0)
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp> 
#pragma warning(pop)

class Random_Fixture
{
protected:
	Random_Fixture();
	virtual ~Random_Fixture() {}

	unsigned int rnd();
private:
	time_t seed;
	boost::mt19937 generator;
	boost::uniform_int<> distribution;
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rndgenerator;
};

#endif // _MISCFIXTURE_RANDOMFIXTURE_HPP