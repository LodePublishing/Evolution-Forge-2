#ifndef _UI_UNITMENU_HPP
#define _UI_UNITMENU_HPP

#include <gui/menu.hpp>
#include "../core/anabuildorder.hpp"

class UnitMenu : public Menu
{
	public:
		UnitMenu(Object* unit_parent, const Rect unit_rect, const Size distance_bottom_right, const ePositionMode position_mode);
		~UnitMenu();
		void process();
		void draw() const;
		void setFacilityModus(const bool facility_mode=true);
		void resetData();
		void assignAnarace(ANABUILDORDER* unit_anarace);
		const bool secondLevel() const;

		const bool addKey(unsigned int key, unsigned int mod);
		void reloadOriginalSize();
	private:
		ANABUILDORDER* anarace;
// sort units in the addgoal menu rather by facility than by unitType		
		unsigned int facilityNumber;
		std::vector<unsigned int> facility;
		// facility number -> real facility 
		void processMenu();
		unsigned int lastRace;
		UnitMenu(const UnitMenu& object);
		UnitMenu& operator=(const UnitMenu& object);
};

#endif // _UI_UNITMENU_HPP

