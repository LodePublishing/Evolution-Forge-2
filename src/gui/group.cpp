#include "group.hpp"

Group::Group(SDL_Object* const group_parent, 
		const Rect& initial_rect, 
		const Size bottom_right_distance, 
		const eGroupType group_type, 
		const boost::shared_ptr<const WindowColors>& windowColors,
		const boost::shared_ptr<const Text>& titleText,
		bool draw_background, 
		const ePositionMode position_mode

	) :
	SDL_Object(group_parent, initial_rect, bottom_right_distance, position_mode, NOTHING),
	title(new Title(this, titleText, std::list<std::string>(), windowColors)), // no variable parameters here
	highlighted(false),
	groupType(group_type),
	drawBackground(draw_background)
{
	//StaticText(this, title_text, Rect(Point(0,0) - Size(3, 14), Size(0,0)), Size(0,0), font, font_color, DO_NOT_ADJUST):NULL;
// BRIGHT_TEXT_COLOR, SMALL_BOLD_FONT
	setDrawType(TRANSPARENT_OBJECT);
}

Group::~Group() 
{
	delete title;
}

void Group::calculateBoxSize()
{
	if(getChildren() == NULL) {
		return;
	}
	Object* tmp = (Object*)getChildren();
	
	Uint16 i = 0;
	Uint16 current_height = 2;
	do
	{
		if((tmp == title) || (!tmp->isShown())) 
		{
			tmp = (Object*)(tmp->getNextBrother());
			continue;
		}
		switch(groupType)
		{
			case CUSTOM_GROUP:break;
			case ONE_COLOUMN_GROUP:
			{
				tmp->setOriginalPosition(Point(2, current_height + tmp->getDistanceBottomRight().getHeight()));
				current_height += tmp->getHeight() + tmp->getDistanceBottomRight().getHeight();
			}break;			 
			case TWO_COLOUMNS_GROUP:
			{
				tmp->setOriginalPosition(Point(2 + (i%2) * (tmp->getWidth() + tmp->getDistanceBottomRight().getWidth() + 5), (i/2)*(tmp->getHeight()+tmp->getDistanceBottomRight().getHeight()+5  + tmp->getDistanceBottomRight().getHeight())));
				i++;
			}break;
			case HORIZONTAL_GROUP:
			{
				tmp->setOriginalPosition(Point(i * (tmp->getWidth() + tmp->getDistanceBottomRight().getWidth()) + 2, 3 + tmp->getDistanceBottomRight().getHeight() ));
				i++;
			}break;	
			case TWO_LINES_GROUP:
			{
				tmp->setOriginalPosition(Point(
							i/2 * (tmp->getWidth() + tmp->getDistanceBottomRight().getWidth() + 5), 
							(i%2)*(tmp->getHeight() + tmp->getDistanceBottomRight().getHeight()+5)
				));
				i++;
			}break;
		}
		tmp = (Object*)(tmp->getNextBrother());
	} while(tmp != (Object*)getChildren());
	
	Uint16 maxWidth = 0;
	Uint16 maxHeight = 0;
	tmp = (Object*)getChildren();
	do
	{
		if((tmp->isShown())&&(tmp!=title))
		{
			Rect r = tmp->getTargetRect();
			if((r.getRight()>0) && (maxWidth < (unsigned int)(r.getRight()))) {
				maxWidth = r.getRight();
			}
			if((r.getBottom()>0) && (maxHeight < (unsigned int)(r.getBottom()))) {
				maxHeight = r.getBottom();
			}
		}
		tmp = (Object*)(tmp->getNextBrother());
	} while(tmp != (Object*)getChildren());
	Size s = Size(maxWidth+7, maxHeight+7);

	setOriginalSize(s); // ?
//	adjustRelativeRect(Rect(getTargetPosition(), s));
}

void Group::alignWidth(const Uint16 width)
{
	Object* tmp = (Object*)getChildren();
	do
	{
		if((tmp->isShown()) && (tmp!=title)) {
			tmp->setOriginalWidth(width);
		}
		tmp = (Object*)(tmp->getNextBrother());
	} while(tmp!=(Object*)getChildren());
}

void Group::reloadOriginalSize()
{
	SDL_Object::reloadOriginalSize();
	calculateBoxSize();
}

void Group::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);


	if(drawBackground)
	{
		if(highlighted) {
			dc->setPen(highlightedPen);
		}
		//*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
		else {
			dc->setPen(pen);
		}
		//*gui.lookUpPen(INNER_BORDER_PEN));
		dc->setBrush(brush);
		//*gui.lookUpBrush(WINDOW_FOREGROUND_BRUSH));
		dc->DrawEdgedRoundedRectangle(Point(0,0), getSize()+Size(6,0), 4);
	}
	SDL_Object::draw(dc);
}

void Group::process()
{
//	if(!isShown())
//		return; //?
	SDL_Object::process();
//	calculateBoxSize(); ?
//	nur aufrufen wenn: child added/removed, child size changed

	if(wereChildrenChanged())
	{
		calculateBoxSize();
		setChildrenWereChanged(false);
	}
	/*if(gui.isMouseInside(getAbsoluteRect()))
	{
		if(!highlighted)
		{
			highlighted = true;
			makePufferInvalid();
		}
	} else
	{
		if(highlighted)
		{
			makePufferInvalid();
			highlighted = false;
		}
	}*/ // TODO
}



