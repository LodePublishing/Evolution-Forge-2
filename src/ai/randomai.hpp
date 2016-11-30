#ifndef _AI_RANDOMAI_HPP
#define _AI_RANDOMAI_HPP

#include "baseai.hpp"

class RandomAI : public BaseAI
{
public:
	RandomAI();
	~RandomAI();

	const std::vector<unsigned int> getCurrentCode() const;
	
	// check if code is completed for all branches (i.e. this AI is completely passive, calculation can be ended)
	const bool isFinished() const;
	
	// progress the code counter
	void progressCode(const unsigned int location);

	void initialize();
private:
};

#endif // _AI_RANDOMAI_HPP
