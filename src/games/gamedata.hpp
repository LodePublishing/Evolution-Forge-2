#ifndef _GAMES_GAMEDATA_HPP
#define _GAMES_GAMEDATA_HPP

#include <core/rules.hpp>
#include <map>

class GameData
{
public:
	const boost::shared_ptr<const Rules>& getRules() const;

	std::map<const unsigned int, const boost::uuids::uuid> race_id_map;
	std::map<const unsigned int, const boost::uuids::uuid> unit_id_map;
	
protected:
	boost::shared_ptr<const Rules> rules;
	GameData(std::map<const unsigned int, const boost::uuids::uuid> race_id_map,
			std::map<const unsigned int, const boost::uuids::uuid> unit_id_map);
	~GameData();
	
	void initRules();
private:
	
	
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Race> > init_racemap_helper();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Rules> > init_rulesmap_helper();
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const UnitType> > init_unittypemap_helper();

	GameData& operator=(const GameData& other);
	GameData(const GameData& other);
};

inline const boost::shared_ptr<const Rules>& GameData::getRules() const { 
	return rules;
}

#endif // _GAMES_GAMEDATA_HPP