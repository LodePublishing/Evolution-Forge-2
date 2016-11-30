#pragma warning(push, 0)  
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#pragma warning(pop)

#include "random_fixture.hpp"
#include <time.h>

Random_Fixture::Random_Fixture():
	seed(time(0)),
	generator(static_cast<boost::uint32_t>(seed)),
	distribution(1, 100),
	rndgenerator(generator,  distribution)
{
	std::cout << "[Fixture seed " << seed << "]" << std::endl;
}

unsigned int Random_Fixture::rnd() {
	return rndgenerator();
}