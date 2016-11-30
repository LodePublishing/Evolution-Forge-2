#ifndef _GOAL_PROCESSEDGOAL_HPP
#define _GOAL_PROCESSEDGOAL_HPP

class ProcessedGoal
{
public:
	ProcessedGoal();
	ProcessedGoal(const bool isHaveable, const bool isBuildable);
	~ProcessedGoal() {}

	bool isHaveable() const;
	bool isBuildable() const;
	bool wasChecked() const;

	void setHaveable(const bool haveable);
	void setBuildable(const bool buildable);
	bool setWasChecked(const bool checked);
	
private:
	bool haveable; // all buildable units XOR all starting units
	bool buildable; // all buildable units
	
	// temporary item to finalize the values
	bool checked;

	// no "bonus", the tree is generated completely (so all solutions are valid) TODO?
};


inline bool ProcessedGoal::isHaveable() const {
	return haveable;
}

inline bool ProcessedGoal::isBuildable() const {
	return buildable;
}

inline bool ProcessedGoal::wasChecked() const {
	return checked;
}

inline bool ProcessedGoal::setWasChecked(const bool checked) {
	if(this->checked != checked) {
		this->checked = checked;
		return true;
	} else {
		return false;
	}
}

inline void ProcessedGoal::setHaveable(const bool haveable) {
	this->haveable = haveable;
	if(!haveable) {		
		buildable = false;
	}
}

inline void ProcessedGoal::setBuildable(const bool buildable) {
	this->buildable = buildable;
	if(buildable) {
		haveable = true;
	}
}



#endif // _GOAL_PROCESSEDGOAL_HPP