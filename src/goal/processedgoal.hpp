#ifndef _CORE_PROCESSEDGOAL_HPP
#define _CORE_PROCESSEDGOAL_HPP

class ProcessedGoal
{
public:
	ProcessedGoal();
	ProcessedGoal(const bool isHaveable, const bool isBuildable, const bool isBuildableAtStart);//, const bool isCheckedAtStart);
	~ProcessedGoal() {}

	bool isHaveable() const;
	bool isBuildable() const;
	bool isBuildableAtStart() const;

	void setHaveable(const bool haveable);
	void setBuildable(const bool buildable);
	void setBuildableAtStart(const bool buildableAtStart);

	// temporary variable to prevent endless recursion in case of a set field 'create' TODO
	//const bool isCheckedAtStart() const;

private:
	bool haveable; // all buildable units XOR all starting units
	//bool goal; // all units that give points
	bool buildable; // all buildable units
	// temporary variables for faster calculation
	bool buildableAtStart;
	
	//bool checkedAtStart;  TODO?
	bool bonus;

	// no "bonus", the tree is generated completely (so all solutions are valid)
};


inline bool ProcessedGoal::isHaveable() const {
	return haveable;
}

inline bool ProcessedGoal::isBuildable() const {
	return buildable;
}

inline bool ProcessedGoal::isBuildableAtStart() const {
	return buildableAtStart;
}

inline void ProcessedGoal::setHaveable(const bool haveable) {
	this->haveable = haveable;
	if(!haveable) {
		buildableAtStart = false;
		buildable = false;
	}
}

inline void ProcessedGoal::setBuildable(const bool buildable) {
	this->buildable = buildable;
	if(buildable) {
		haveable = true;
	} else {
		buildableAtStart = false;
	}
}

inline void ProcessedGoal::setBuildableAtStart(const bool buildableAtStart) {
	this->buildableAtStart = buildableAtStart;
	if(buildableAtStart) {
		buildable = true;
		haveable = true;
	}
}


#endif // _CORE_PROCESSEDGOAL_HPP