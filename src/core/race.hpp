#ifndef _CORE_RACE_HPP
#define _CORE_RACE_HPP

#include <string>

#include <misc/uuid.hpp>


class Race : public UUID<Race>
{
public:
	Race(const boost::uuids::uuid id, const std::string& name);
	Race(const std::string& name);
	~Race();

	const std::string& getName() const;

private:	
	const std::string name;

	Race& operator=(const Race& other);
};

inline const std::string& Race::getName() const {
	return name;
}

#endif // _CORE_RACE_HPP
