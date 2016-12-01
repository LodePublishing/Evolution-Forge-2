#include "tooltip.hpp"

#pragma warning(push, 0)  
#include <boost/assert.hpp>
#pragma warning(pop)

// TODO gemeinsame abstrakte Basisklasse mit statictext...
ToolTip::ToolTip(SDL_Object* const parent_object, 
			const boost::shared_ptr<const Text>& text, 
			const std::list<std::string>& parameterList,
			const boost::shared_ptr<const WindowColors>& window_colors, 
			const boost::shared_ptr<const ObjectSize>& object_size):
	MultiLineText(
		parent_object, 
		Rect(3, 3, object_size->getWidth() , 0), 
		text,
		parameterList,
		window_colors),
		boxSize(),
		objectSize(object_size)
{ }

	
ToolTip::~ToolTip()
{ 
}

void ToolTip::reloadOriginalSize()
{
	setOriginalSize(Size(objectSize->getWidth(), 0));
	MultiLineText::reloadOriginalSize();
}

void ToolTip::process()
{
	MultiLineText::process();
}
                                                                                
void ToolTip::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);
	MultiLineText::draw(dc);
}

