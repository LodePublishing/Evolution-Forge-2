#pragma warning(push, 0) 
#include <boost/assert.hpp>
#pragma warning(pop)

#include "player.hpp"

Player::Player(const std::string& name,
	const boost::shared_ptr<const Government> government):
name(name),
	government(government),
	governmentId(government->getId())
{ }

Player::Player(const boost::uuids::uuid id,
	const std::string& name,
	const boost::shared_ptr<const Government> government):
UUID<Player>(id),
	name(name),
	government(government),
	governmentId(government->getId())
{ }

Player::~Player()
{ }
