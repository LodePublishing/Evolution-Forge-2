#ifndef _CORE_PLAYER_HPP
#define _CORE_PLAYER_HPP

#include "government.hpp"
#include "id.hpp"
#include "goalentry.hpp"
#include "units.hpp"

#include "globalstorage.hpp"

/**
* Player holds global information unique to each player like
* global resources, global units, technology, race etc.
*/

class Player : public ID<Player>
{
public:
	Player(const std::string& name,
		const boost::shared_ptr<const Government> government,
		const boost::shared_ptr<const GoalEntry> goalEntry,
		const boost::shared_ptr<const Units> startingUnits);

	Player(const unsigned int id,
		const std::string& name,
		const boost::shared_ptr<const Government> government,
		const boost::shared_ptr<const GoalEntry> goalEntry,
		const boost::shared_ptr<const Units> startingUnits);

	~Player();	
	
	const std::string& getName() const;
	const boost::shared_ptr<const Government> getGovernment() const;
	unsigned int getGovernmentId() const;
	const boost::shared_ptr<const GoalEntry> getGoalEntry()  const;
	unsigned int getGoalEntryId() const;
	const boost::shared_ptr<const Units> getStartingUnits() const;

private:
	friend class boost::serialization::access;

	template<class Archive> 
	void serialize(Archive &ar, const unsigned int version)
	{ }

	template<class Archive>
	friend inline void save_construct_data(Archive &ar, const Player* player, const unsigned int version) { 

		const unsigned int& id = player->getId();
		const std::string& name = player->getName();
		const unsigned int& governmentId = player->getGovernmentId();
		const unsigned int& goalEntryId = player->getGoalEntryId();
		const boost::shared_ptr<const Units>& startingUnits = player->getStartingUnits();

		if(version > 0) {
		}

		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(governmentId)
		   & BOOST_SERIALIZATION_NVP(goalEntryId)
		   & BOOST_SERIALIZATION_NVP(startingUnits);
	}

	template<class Archive> 
	inline friend void load_construct_data(Archive& ar, Player*& player, const unsigned int version)
	{
		unsigned int id;
		std::string name;
		unsigned int governmentId;
		unsigned int goalEntryId;
		boost::shared_ptr<const Units> startingUnits;
		
		ar & BOOST_SERIALIZATION_NVP(id)
		   & BOOST_SERIALIZATION_NVP(name)
		   & BOOST_SERIALIZATION_NVP(governmentId)
		   & BOOST_SERIALIZATION_NVP(goalEntryId)
		   & BOOST_SERIALIZATION_NVP(startingUnits);
		   
		if(version > 0) {
		}

		::new(player)Player(id, name, GLOBAL_STORAGE.getGovernment(governmentId), GLOBAL_STORAGE.getGoalEntry(goalEntryId), startingUnits);
	}

	const std::string name;
	const boost::shared_ptr<const Government> government;
	const unsigned int governmentId;
	const boost::shared_ptr<const GoalEntry> goalEntry;
	const unsigned int goalEntryId;
	const boost::shared_ptr<const Units> startingUnits;

	Player& operator=(const Player& other);
};

inline const std::string& Player::getName() const {
	return name;
}

inline const boost::shared_ptr<const Government> Player::getGovernment() const {
	return government;
}

inline unsigned int Player::getGovernmentId() const {
	return governmentId;
}

inline const boost::shared_ptr<const GoalEntry> Player::getGoalEntry()  const {
	return goalEntry;
}

inline unsigned int Player::getGoalEntryId() const {
	return goalEntryId;
}

inline const boost::shared_ptr<const Units> Player::getStartingUnits() const {
	return startingUnits;
}

#endif
