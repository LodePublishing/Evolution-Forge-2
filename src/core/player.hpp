#ifndef _CORE_PLAYER_HPP
#define _CORE_PLAYER_HPP

#include <misc/uuid.hpp>

#include "government.hpp"

/**
* Player holds global information unique to each player like
* global resources, global units, technology, race etc.
*/

class Player : public UUID<Player>
{
public:
	Player(const std::string& name,
		const boost::shared_ptr<const Government> government);

	Player(const boost::uuids::uuid id,
		const std::string& name,
		const boost::shared_ptr<const Government> government);

	~Player();	

	const std::string& getName() const;
	const boost::shared_ptr<const Government> getGovernment() const;
	boost::uuids::uuid getGovernmentId() const;

private:
	const std::string name;
	const boost::shared_ptr<const Government> government;
	const boost::uuids::uuid governmentId;

	Player& operator=(const Player& other);
};

inline const std::string& Player::getName() const {
	return name;
}

inline const boost::shared_ptr<const Government> Player::getGovernment() const {
	return government;
}

inline boost::uuids::uuid Player::getGovernmentId() const {
	return governmentId;
}



#endif
