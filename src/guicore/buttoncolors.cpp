#include "buttoncolors.hpp"

#include "buttonanimation_storage.hpp"

ButtonColors::ButtonColors(const boost::uuids::uuid id, const unsigned int speed, const eButtonAnimationType animationType, const std::vector<boost::shared_ptr<const ButtonAnimation> >& buttonAnimationVector):
	UUID<ButtonColors>(id),
	speed(speed),
	animationType(animationType),
	buttonAnimationVector(buttonAnimationVector)
{ }

ButtonColors::ButtonColors(const unsigned int speed, const eButtonAnimationType animationType, const std::vector<boost::shared_ptr<const ButtonAnimation> >& buttonAnimationVector):
	speed(speed),
	animationType(animationType),
	buttonAnimationVector(buttonAnimationVector)
{ }

ButtonColors::~ButtonColors()
{ }
