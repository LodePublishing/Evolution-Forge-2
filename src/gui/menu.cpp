#include "menu.hpp"

Menu::Menu(SDL_Object* const menu_parent, 
				const Rect& rect, 
				const Size distance_bottom_right, 
				const ePositionMode position_mode, 
				bool choose_menu, 
				const boost::shared_ptr<const ObjectSize>& object_size, 
				const boost::shared_ptr<const ButtonColors>& button_colors,
				const boost::shared_ptr<const WindowColors>& window_colors,
				std::vector<boost::shared_ptr<const Text> > strings,
				eMenuType menu_type) :
	Object(menu_parent, rect, distance_bottom_right, position_mode),
	menuEntries(),
	menuLevel(0),
	pressedItem(-1),
	markedItem(-1),
	height(0),
	chooseMenu(choose_menu),
	p1(),
	p2(),
	menuChanged(false),
	objectSize(object_size),
	buttonColors(button_colors),
	windowColors(window_colors),
	menuType(menu_type)
{
	if(strings.size() > 0)
	{
		for(std::vector<boost::shared_ptr<const Text> >::const_iterator i = strings.begin(); i != strings.end(); i++) {
			menuEntries.push_back(new MenuEntry(this, Rect(), button_colors, *i));
		}
		updateItemSizes(objectSize->getWidth());
		updateItemPositions();
	}
	Hide();
}

Menu::~Menu()
{
	for(std::list<MenuEntry*>::const_iterator m = menuEntries.begin(); m != menuEntries.end(); ++m) {
		delete *m;	
	}
}

void Menu::reloadOriginalSize() {

	updateItemSizes(objectSize->getWidth());

	updateItemPositions();
	Object::reloadOriginalSize();	 //?
}

void Menu::updateItemSizes(const Uint16 width)
{
	for(std::list<MenuEntry*>::iterator m=menuEntries.begin(); m!=menuEntries.end(); ++m) {
		(*m)->setOriginalSize(Size(width, 0));
	}
}

void Menu::updateItemPositions()
{
	unsigned int i = 0;
	height = 0;
//	Size s;
//	if(positionMode == TOTAL_CENTERED) // TODO
//		s = 
		
	switch(menuType)
	{
		case CUSTOM_MENU:break;
		case ONE_COLOUMN_MENU:
		for(std::list<MenuEntry*>::iterator m = menuEntries.begin(); m != menuEntries.end(); ++m)
			if((*m)->isShown())
			{
				Uint16 item_height = (*m)->getHeight();

				(*m)->setOriginalPosition(Point(0, i*(item_height+(*m)->getDistanceBottomRight().getHeight())) + Size(3,3));
				i++;
				height++;
			}
		break;			 
		case TWO_COLOUMNS_MENU:
		for(std::list<MenuEntry*>::iterator m = menuEntries.begin(); m != menuEntries.end(); ++m)
			if((*m)->isShown())
			{
				Uint16 item_height = (*m)->getHeight();

				(*m)->setOriginalPosition(Point((i%2) * ((*m)->getWidth() + (*m)->getDistanceBottomRight().getWidth()), (i/2)*(item_height+(*m)->getDistanceBottomRight().getHeight())) + Size(3,3));
				i++;
				if(i%2==0) {
					height++;
				}
			}
		break;
		case HORIZONTAL_MENU:
		for(std::list<MenuEntry*>::iterator m = menuEntries.begin(); m != menuEntries.end(); ++m)
			if((*m)->isShown())
			{
				(*m)->setOriginalPosition(Point(i * ((*m)->getWidth() + (*m)->getDistanceBottomRight().getWidth()), 0)  + Size(3,3));
				i++;
			}
		height = 1;
		break;	
		default:break;
	}

	Uint16 max_width = 0;
	Uint16 max_height = 0;
	Object* tmp = (Object*)getChildren();
	if(tmp == NULL) {
		return;
	}
	do
	{
		if(tmp->isShown())
		{
			Rect r = tmp->getTargetRect();
			if((r.getRight() > 0) && ((Sint16)max_width < r.getRight())) {
				max_width = r.getRight();
			}
			if((r.getBottom() > 0) && ((Sint16)max_height < r.getBottom())) {
				max_height = r.getBottom();
			}
		}
		tmp = (Object*)(tmp->getNextBrother());
	}

	while(tmp!=(Object*)getChildren());
	
	Size s = Size(max_width+7, max_height+7);
//	setOriginalSize(s);
	adjustRelativeRect(Rect(getTargetPosition(), s));

}

bool Menu::isOpen() const
{
	if(menuLevel == 0) {
		return false;
	} else {
		return true;
	}
}

signed int Menu::getPressedItem()
{
	signed int p = pressedItem;
	pressedItem = -1;
	return p;
}

Uint16 Menu::getHeight() const
{
	if(!isOpen()) {
		return 0;
	} else {
		return height;
	}
}


void Menu::open()
{
	if(menuLevel == 0) {
		menuLevel = 1;
	} else if(menuLevel == 1) {
		menuLevel = 0;
	} else {
		menuLevel = 1;
	}

	setMenuHasChanged();


	if(menuLevel) {
		Show();
	} else {
		Hide();
	}

	if(isShown())
	{
		Object* tmp = (Object*)getChildren();  
		if (tmp) {
			do {
				tmp->resetBrightness();
				tmp = (Object*)(tmp->getNextBrother());
			} while (tmp != (Object*)getChildren());
		}
	}
}

void Menu::close()
{
	if(menuLevel!=0) {
		setMenuHasChanged();
	}
	menuLevel=0;
	Hide();
}

void Menu::setMenuLevel(const unsigned int menu_level)
{
	if(menuLevel == menu_level) {
		return;
	}
	menuLevel = menu_level;
	setMenuHasChanged();
}

void Menu::setMenuHasChanged(const bool has_changed)
{
	if(has_changed == menuChanged) {
		return;
	}

	menuChanged = has_changed;
	makePufferInvalid();
}

void Menu::process()
{
	markedItem = -1;
	if(!isShown()) {
		return;
	}

	setMenuHasChanged(false);
	
	Object::process();
	
	p1 = Point(9999, 9999);
	p2 = Point(0, 0);

	unsigned int i = 0;

	for(std::list<MenuEntry*>::const_iterator m=menuEntries.begin(); m!=menuEntries.end(); ++m)
	{
		if(!(*m)->isShown())
		{
			(*m)->setPosition(Point(0, 0));
			(*m)->frameReset();
		}
		else
		{
			if((*m)->getAbsoluteLeftBound() < p1.getX()) {
				p1.setX((*m)->getAbsoluteLeftBound());
			}

			if((*m)->getAbsoluteUpperBound() < p1.getY()) {
				p1.setY((*m)->getAbsoluteUpperBound());
			}

			if((*m)->getAbsoluteRightBound() > p2.getX()) {
				p2.setX((*m)->getAbsoluteRightBound());
			}

			if((*m)->getAbsoluteLowerBound() > p2.getY()) {
				p2.setY((*m)->getAbsoluteLowerBound());
			}

			if ((*m)->isLeftClicked()) {
				pressedItem = i;
			}

			if ((*m)->isCurrentlyHighlighted()) {
				markedItem = i;
			}
		}
		++i;
	}

	if((pressedItem >= 0) && (chooseMenu)) {
		close();
	}
}

void Menu::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	if(p1 > p2) {
		return;
	}
	Rect edge = Rect(p1 - Size(3,3), Size(p2.getX() - p1.getX(), 
		p2.getY() - p1.getY()) + Size(6,6) );

	dc->setBrush(windowColors->getBackgroundBrush());
	dc->setPen(windowColors->getHighlightedBorderPen());
	dc->DrawRoundedRectangle(edge, 4);

	Object::draw(dc);
}


void Menu::forcePressItem(const unsigned int number)
{
	BOOST_ASSERT(number < menuEntries.size());

	pressedItem = number;
	if(chooseMenu) {
		close();
	}
/*	unsigned int n = 0;
	for(std::list<MenuEntry*>::const_iterator m=menuEntries.begin(); m!=menuEntries.end(); ++m)
		if((*m)->isShown())
		{
			if(n == number)
			{
				(*m)->forcePress();
				return;
			}
			n++;
		}*/
}


