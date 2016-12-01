#ifndef _CORE_GOVERNMENT_HPP
#define _CORE_GOVERNMENT_HPP

#include <string>
#include <misc/uuid.hpp>

class Government : public UUID<Government>
{
public:
	Government(const std::string name);
	Government(const boost::uuids::uuid id, const std::string name);
	~Government();

	const std::string& getName() const;

private:
	const std::string name;

	Government& operator=(const Government& other);
	Government(const Government& other);
};

inline const std::string& Government::getName() const {
	return name;
}


#endif // _CORE_GOVERNMENT_HPP