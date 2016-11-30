#include "processedgoal.hpp"

ProcessedGoal::ProcessedGoal(const bool isHaveable, const bool isBuildable):
	haveable(isHaveable),
	buildable(isBuildable),
	checked(false)
{}

ProcessedGoal::ProcessedGoal():
	haveable(false),
	buildable(false),
	checked(false)
{
}