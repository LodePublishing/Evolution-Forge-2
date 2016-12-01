#include "basictext.hpp"
#include <sstream>

#pragma warning(push, 0)  
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)

BasicText::BasicText(SDL_Object* const bt_parent, 
			const Rect& bt_pos, 
			const Size& distance_bottom_right, 
			const boost::shared_ptr<const Text>& bt_text,
			const std::list<std::string>& parameterList,
			const ePositionMode position_mode,
			const eAutoSize auto_size) :
	Object(bt_parent, bt_pos, distance_bottom_right, position_mode, auto_size),
	text(bt_text)
{ 
	setDrawType(ANTI_ALIASED_OBJECT);   
	text->updateParameters(parameterList);
}

BasicText::~BasicText()
{ }