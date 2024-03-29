#ifndef _UI_BOENTRY_HPP
#define _UI_BOENTRY_HPP

#if 0

#include <gui/button.hpp>
#include "../core/program.hpp"

class BoEntry : public Button
{
	public:
		BoEntry(Object* bo_parent, const Point top_left, const Size distance_bottom_right, const std::string& bo_unit, const PROGRAM& bo_program, const unsigned int unit_count, const unsigned int my_id);
		~BoEntry();

		const unsigned int changed();
		void process();
		void draw() const;
//		void lock(const bool close=true);
//		void unlock(const bool open=true);
//		const bool locked() const;

		PROGRAM program;
		
		void setId(const unsigned int my_id);
		const unsigned int getId() const;

		void setCount(const unsigned int unit_count);
		const unsigned int getCount() const;

		static bool doLockSound;		
		static bool entryIsMoving;
	private:
		unsigned int id;
		unsigned int count;
//		bool fixed;
//		Button* addUnit;
//		Button* subUnit;
//		Button* cancelUnit; TODO
		BoEntry(const BoEntry& object);
		BoEntry& operator=(const BoEntry& object);

};

inline void BoEntry::setId(const unsigned int my_id) {
	id = my_id;
}

inline const unsigned int BoEntry::getId() const {
	return(id);
}

inline void BoEntry::setCount(const unsigned int unit_count) {
	count = unit_count;
}

inline const unsigned int BoEntry::getCount() const {
	return(count);
}

#endif

#endif // _UI_BOENTRY_HPP

