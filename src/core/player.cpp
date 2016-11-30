#pragma warning(push, 0) 
#include <boost/assert.hpp>
#pragma warning(pop)

#include "player.hpp"

Player::Player(const std::string& name,
		const boost::shared_ptr<const Government> government,
		const boost::shared_ptr<const Units> startingUnits):
	name(name),
	government(government),
	governmentId(government->getId()),
	startingUnits(startingUnits)
{}

Player::Player(const boost::uuids::uuid id,
		const std::string& name,
		const boost::shared_ptr<const Government> government,
		const boost::shared_ptr<const Units> startingUnits):
	UUID<Player>(id),
	name(name),
	government(government),
	governmentId(government->getId()),
	startingUnits(startingUnits)
{}

Player::~Player()
{}