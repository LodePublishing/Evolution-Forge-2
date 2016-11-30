#pragma warning(push, 0) 
#include <boost/assert.hpp>
#pragma warning(pop)

#include "player.hpp"

Player::Player(const std::string& name,
		const Government& government,
		const GoalEntry* const goalEntry):
	name(name),
	government(new Government(government)),
	goalEntry(goalEntry),
	goalEntryID(goalEntry->getID())
{}

Player::~Player()
{
	delete government;
}

// needs to be called after deserialization
void Player::setGoalEntry(const GoalEntry* const goalEntry) {
	BOOST_ASSERT(goalEntry->getID() == goalEntryID);

	this->goalEntry = goalEntry;
}

const char* const Player::Name_tag_string = "name";
const char* const Player::Government_tag_string = "government";
const char* const Player::GoalEntryID_tag_string = "goalentry";