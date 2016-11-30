#ifndef _CORE_PLAYER_HPP
#define _CORE_PLAYER_HPP

#include <uuid.hpp>

#include "government.hpp"
#include "units.hpp"

#include <globalstorage.hpp>

/**
* Player holds global information unique to each player like
* global resources, global units, technology, race etc.
*/

class Player : public UUID<Player>
{
public:
	Player(const std::string& name,
		const boost::shared_ptr<const Government> government,
		const boost::shared_ptr<const Units> startingUnits);

	Player(const boost::uuids::uuid id,
		const std::string& name,
		const boost::shared_ptr<const Government> government,
		const boost::shared_ptr<const Units> startingUnits);

	~Player();	
	
	const std::string& getName() const;
	const boost::shared_ptr<const Government> getGovernment() const;
	boost::uuids::uuid getGovernmentId() const;
	const boost::shared_ptr<const Units> getStartingUnits() const;

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Player* player, const unsigned int version) { 

		const boost::uuids::uuid& id = player->getId();
		const std::string& name = player->getName();
		const boost::uuids::uuid& governmentId = player->getGovernmentId();
		const boost::shared_ptr<const Units>& startingUnits = player->getStartingUnits();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(governmentId)
		   & BOOST_SERIALIZATION_NVP(startingUnits);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Player*& player, const unsigned int version)
	{
		boost::uuids::uuid id;
		std::string name;
		boost::uuids::uuid governmentId;
		boost::shared_ptr<const Units> startingUnits;
		
		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(governmentId)
		   & BOOST_SERIALIZATION_NVP(startingUnits);
		   
		if(version > 0) {
		}

		::new(player)Player(id, name, GlobalStorage::instance().getGovernment(governmentId), startingUnits);
	}

	const std::string name;
	const boost::shared_ptr<const Government> government;
	const boost::uuids::uuid governmentId;
	const boost::shared_ptr<const Units> startingUnits;

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

inline const boost::shared_ptr<const Units> Player::getStartingUnits() const {
	return startingUnits;
}

#endif
