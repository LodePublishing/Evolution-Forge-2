#include "language.hpp"
#include "text.hpp"

Language::Language(const boost::uuids::uuid& id, const boost::shared_ptr<const Text>& name):
UUID<Language>(id),
	name(name),
	nameId(name->getId())
{ }

Language::Language(const boost::shared_ptr<const Text>& name):
	UUID<Language>(),
	name(name),
	nameId(name->getId())
{ }