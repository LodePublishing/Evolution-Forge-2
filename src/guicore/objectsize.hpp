#ifndef _GUICORE_OBJECTSIZE_HPP
#define _GUICORE_OBJECTSIZE_HPP

#include <geometry/size.hpp>

#include <misc/uuid.hpp>

class ObjectSize : public UUID<ObjectSize>
{
public:
	ObjectSize(const boost::uuids::uuid id, const Uint16 width, const Uint16 height);
	ObjectSize(const Uint16 width, const Uint16 height);
	~ObjectSize();

	operator Size() const;
	Size operator->() const;

	Uint16 getWidth() const {return size.getWidth();}
	Uint16 getHeight() const {return size.getHeight();}

private:


	const Size size;
};

inline ObjectSize::operator Size() const { 
	return size;
}

inline Size ObjectSize::operator->() const {
	return size;
}

#endif // _GUICORE_OBJECTSIZE_HPP