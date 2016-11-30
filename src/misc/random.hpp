#include <time.h>

#pragma warning(push, 0) 
#include <boost/random.hpp>
#pragma warning(pop)

boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die( boost::mt19937(time(0)), boost::uniform_int<>(1, 100) );
boost::variate_generator<boost::mt19937&, boost::uniform_int<> > zero_die( boost::mt19937(time(0)), boost::uniform_int<>(0, 100) );