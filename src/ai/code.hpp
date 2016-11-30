#ifndef _AI_CODE_HPP
#define _AI_CODE_HPP

#include <list>

// contains directly the unitTypeId, not just some genotype
class Code 
{
public:
	Code();
	~Code();
	void moveToNextInstruction();
	const unsigned int getCurrentCode() const;
	const bool isCodeFinished() const;
	void resetInstructionPointer();
	const unsigned int getLength() const;

private:
	std::list<unsigned int> geneList;
	std::list<unsigned int>::iterator IP;

};

inline void Code::moveToNextInstruction() {
	if(IP != geneList.end()) {
		++IP;
	}
}

inline const bool Code::isCodeFinished() const {
	return IP == geneList.end();
}

inline void Code::resetInstructionPointer() {
	IP = geneList.begin();
}

inline const unsigned int Code::getCurrentCode() const
{
	// TODO
	if(isCodeFinished()) {
		return 0;
	}
	
	return *IP;
}

inline const unsigned int Code::getLength() const
{
	return geneList.size();
}

#endif // _AI_CODE_HPP