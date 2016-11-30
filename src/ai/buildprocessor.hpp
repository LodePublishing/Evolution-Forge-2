#ifndef _AI_BUILDPROCESSOR_HPP
#define _AI_BUILDPROCESSOR_HPP

#include <vector>
#include "buildorder.hpp"

class BuildProcessor
{
public:
	BuildProcessor();
	~BuildProcessor();
	
	// the vector corresponds to the location vector
	void tryBuilding(std::vector<unsigned int> buildList);
private:

};

#endif // _AI_BUILDPROCESSOR_HPP
