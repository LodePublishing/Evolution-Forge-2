#include "processedgoal.hpp"

ProcessedGoal::ProcessedGoal(const bool isHaveable, const bool isBuildable, const bool isBuildableAtStart)://, const bool isBonus)://, const bool isCheckedAtStart):
	haveable(isHaveable),
	buildable(isBuildable),
	buildableAtStart(isBuildableAtStart)
	//, bonus(isBonus)	
	//, checkedAtStart(isCheckedAtStart)
{}

ProcessedGoal::ProcessedGoal():
	haveable(false),
	buildable(false),
	buildableAtStart(false)
{
}