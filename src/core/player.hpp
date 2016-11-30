#ifndef _CORE_PLAYER_HPP
#define _CORE_PLAYER_HPP

#include "government.hpp"
#include "id.hpp"
#include "goalentry.hpp"

/*
1. table-Klassen laden raw-data aus den XMLs (IDs speichern!)
2. Sobald alle geladen sind: IDs bei allen Tabellen nachladen
3. Sobald alle nachgeladen sind: Eigentliche Klassen initialisieren

reloadTables reinmachen

Tabellen:

getById reinmachen

Entries:

assignArray reinmachen*/

/**
* Player holds global information unique to each player like
* global resources, global units, technology, race etc.
*/

class Player : public ID<Player>
{
public:
	Player(const std::string& name,
		const Government& government,
		const GoalEntry* const goalEntry);
	~Player();
	
	
	const std::string& getName() const;
	const Government* getGovernment() const;

	const GoalEntry* getGoalEntry()  const;
	unsigned int getGoalID() const;

	// called after deserialization!
	void setGoalEntry(const GoalEntry* const goalEntry);
	
	static const char* const Name_tag_string;
	static const char* const Government_tag_string;
	static const char* const GoalEntryID_tag_string;

private:
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp(ID_tag_string, id);
		ar & boost::serialization::make_nvp(Name_tag_string, name);
		ar & boost::serialization::make_nvp(Government_tag_string, government);
		ar & boost::serialization::make_nvp(GoalEntryID_tag_string, goalEntryID);
		if(version > 0) {
		}
	}
	// only use for serialization / deserialization
	Player():government(NULL),goalEntry(NULL) {}

	std::string name;
	Government* government;
	unsigned int goalEntryID;

	// temporary variable
	const GoalEntry* goalEntry;

	
};


inline const GoalEntry* Player::getGoalEntry()  const {
	return goalEntry;
}

inline unsigned int Player::getGoalID() const {
	return goalEntryID;
}


inline const Government* Player::getGovernment() const {
	return government;
}

inline const std::string& Player::getName() const {
	return name;
}

#endif
