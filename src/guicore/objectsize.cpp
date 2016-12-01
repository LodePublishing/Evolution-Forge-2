#include "objectsize.hpp"

ObjectSize::ObjectSize(Uint16 width, Uint16 height):
	UUID<ObjectSize>(),
	size(Size(width, height))
{ }

ObjectSize::ObjectSize(const boost::uuids::uuid id, const Uint16 width, const Uint16 height):
	UUID<ObjectSize>(id),
	size(Size(width, height))
{ }

ObjectSize::~ObjectSize()
{ }

