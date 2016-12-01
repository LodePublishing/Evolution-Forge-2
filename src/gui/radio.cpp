#include "radio.hpp"

Radio::Radio(SDL_Object* const radio_parent, 
				const boost::shared_ptr<const WindowColors>& window_colors,
		Rect initial_rect, 
		Size bottom_right_distance, 
		const eGroupType group_type, 
		bool draw_background, 
		const ePositionMode position_mode, 
		const boost::shared_ptr<const Text>& radio_title) :
	Group(radio_parent, initial_rect, bottom_right_distance, group_type, window_colors, radio_title, draw_background, position_mode),
	selectedItemId(boost::uuids::nil_uuid()),
	activatedItemId(boost::uuids::nil_uuid()),
	reorder(false),
	buttonMap()
{ }

Radio::~Radio()
{ }

void Radio::addButton(Button* const button)
{
	BOOST_ASSERT(button);

	button->setParent(this);
	button->radio = this;
	buttonMap[button->getId()] = button;

	calculateBoxSize();
	
	reorder = true;
}

void Radio::removeButton(const boost::uuids::uuid button_id)
{
	BOOST_ASSERT(buttonMap.find(button_id) != buttonMap.end());

	buttonMap[button_id]->setParent(NULL);
	buttonMap[button_id]->radio = NULL;

	buttonMap.erase(button_id);

	if(selectedItemId == button_id) {
		selectedItemId = boost::uuids::nil_uuid();
	}

	calculateBoxSize();
	reorder = true;
}

void Radio::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	Group::draw(dc);
}

void Radio::forceUnpressAll()
{
	if(!getChildren()) {
		return;
	}

	for(std::map<const boost::uuids::uuid, Button*>::iterator i = buttonMap.begin(); i != buttonMap.end(); i++) {
		i->second->forceUnpress();
	}
}


void Radio::process()
{
	// if a button was activated in the last cycle unpress all other buttons
	if(activatedItemId != boost::uuids::nil_uuid()) {
		for(std::map<const boost::uuids::uuid, Button*>::iterator i = buttonMap.begin(); i != buttonMap.end(); i++) {
			if(activatedItemId != i->first) {
				i->second->forceUnpress();	
			}
		}
		selectedItemId = activatedItemId;
		activatedItemId = boost::uuids::nil_uuid();
	}

	Button* lastPressed = NULL;
	for(std::map<const boost::uuids::uuid, Button*>::iterator i = buttonMap.begin(); i != buttonMap.end(); i++) {
		if(i->second->isCurrentlyActivated()) {
			lastPressed = i->second;
			break;
		}
	}

	Group::process();

	if(lastPressed!=NULL)
	{
		bool allUnpressed=true;
		for(std::map<const boost::uuids::uuid, Button*>::iterator i = buttonMap.begin(); i != buttonMap.end(); i++) {
			if(i->second->isCurrentlyActivated()) {
				allUnpressed = false;
				break;
			}
		}
		if(allUnpressed) {
			lastPressed->forcePress();
		}
	}

	if(reorder)
	{ 
		// TODO

		reorder=false;
//		calculateBoxSize(); // TODO
/*		resetMinXY();
		for(unsigned int i = 0; i < RADIO_MAX_BUTTONS; i++)
			if(buttonId[i])
				buttonId[i]->adjustPositionAndSize(ADJUST_ONLY_POSITION);*/
	}
}

