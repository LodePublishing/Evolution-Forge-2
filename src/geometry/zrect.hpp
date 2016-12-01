#ifndef _GEOMETRY_ZRECT_HPP
#define _GEOMETRY_ZRECT_HPP

#include <list>

#include "rect.hpp"

#include <misc/uuid.hpp>

class ZRect : public UUID<ZRect>
{
	friend std::ostream& operator<<(std::ostream& out, ZRect val) {out << val.toString();return out;}
	public:
		ZRect(const boost::uuids::uuid id, const Rect& rect, const signed int z);
		ZRect(const Rect& rect, const signed int z);
		~ZRect();
	
		static bool isInFrontOf(const ZRect& r1, const ZRect& r2);
		static void eraseOverlappingRects(std::list<ZRect>& rect_list);
		static void eraseOverlappingRects(std::list<ZRect>& old_rect_list, std::list<ZRect>& new_rect_list);
		static void connectRects(std::list<ZRect>& rect_list);

		const Rect& getRect() const;
		signed int getZ() const;

		const std::string toString() const;

	private:
		const Rect rect;
		const signed int z;
};

inline const Rect& ZRect::getRect() const {
	return rect;
}

inline signed int ZRect::getZ() const {
	return z;
}

#endif // _GEOMETRY_ZRECT_HPP