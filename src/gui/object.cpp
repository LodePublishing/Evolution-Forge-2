#include "object.hpp"

#include <misc/exceptions.hpp>

#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

Object::Object(SDL_Object* const parent_object, const Rect& relative_rect, const Size& distance_bottom_right, const ePositionMode position_mode, const eAutoSize auto_size) :
	SDL_Object(parent_object, relative_rect, distance_bottom_right, position_mode, auto_size),
	toolTipText(boost::shared_ptr<const Text>()),
	brightness(0)
{ }


Object::~Object()
{ }


bool Object::addKey(unsigned int key, unsigned int mod)
{
	return false;
}


void Object::process()
{
	SDL_Object::process();
}

// returns the object the mouse cursor is currently over and owns a tooltip
const Object* Object::checkToolTip(const Point& mouse) const
{
	if(!isShown()) {
		return NULL;
	}

	Object* tmp = (Object*)getChildren();  // process all children of gadget
	
	if(!tmp) {
		return NULL; // return 0 as this is an object and no button!
	}
	const Object* result = NULL;
	do 
	{
		result = tmp->checkToolTip(mouse);
		if(result != NULL && !result->hasToolTip()) {
			result = NULL;
		}
		tmp = (Object*)(tmp->getNextBrother());
	} while((tmp != (Object*)getChildren())&&(result == NULL));
	
	return result;
}



void Object::draw(DC* const dc) const {
	BOOST_ASSERT(dc);

	SDL_Object::draw(dc);
}

void Object::updateToolTipParameter(const boost::uuids::uuid languageId, const std::list<std::string>& toolTipStringList) {
	if(!hasToolTip()) {
		throw GUIException("ERROR (Object::updateToolTipParameter()): Could not set parameters to a non existing text.");
	}
	this->toolTipStringList.clear();
	this->toolTipStringList.insert(this->toolTipStringList.begin(), toolTipStringList.begin(), toolTipStringList.end());
}
