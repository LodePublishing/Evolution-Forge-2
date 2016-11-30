#ifndef _AI_BASEAI_HPP
#define _AI_BASEAI_HPP

abstract class BaseAI
{
public:
	const std::vector<unsigned int> getCurrentCode() const;
	
	// check if code is completed for all branches (i.e. this AI is completely passive, calculation can be ended)
	const bool isFinished() const;
	
	// progress the code counter
	void progressCode(const unsigned int location);

	void initialize();
	
	void reward();
	/*
	Gebe Liste an baubaren BOs rein, Funktion w�hlt zuf�llig eine g�ltige aus
		Oder: Auf Basis des aktuellen Baupfads w�hle 

	G�ltige BO muss jede AI erzeugen!
	Ben�tigt auf jeden Fall Constants und GOAL! (buildable)
	*/
protected:
	BaseAI();
	~BaseAI();

private:
	
};


#endif // _AI_BASEAI_HPP