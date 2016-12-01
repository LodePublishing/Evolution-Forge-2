#include "text.hpp"

#include <misc/miscellaneous.hpp>


Text::Text(const std::map<const boost::uuids::uuid, const std::string>& textMap):
	UUID<Text>(),
	textMap(textMap),
	languageId(textMap.begin()->first)
{ }

Text::Text(const boost::uuids::uuid id, const std::map<const boost::uuids::uuid, const std::string>& textMap):
	UUID<Text>(id),
	textMap(textMap),
	languageId(textMap.begin()->first)
{ }
