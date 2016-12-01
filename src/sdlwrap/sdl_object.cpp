#include "sdl_object.hpp"

#include <misc/log.hpp>

#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)




SDL_Object::SDL_Object(SDL_Object* const parent_object, const Rect& relative_rect, const Size& distance_bottom_right, const ePositionMode position_mode, const eAutoSize auto_size) :
UUID<SDL_Object>(),
	ObjectNode(parent_object),
	PositionObject(relative_rect, distance_bottom_right, position_mode, auto_size),

	pufferValid(false),
	drawPuffer(NULL),
	drawType(SOLID_OBJECT),
	wasShown(false),
	wasHidden(true),
	shown(true)
{
	Show();
}



SDL_Object::SDL_Object(const boost::uuids::uuid id, SDL_Object* const parent_object, const Rect& relative_rect, const Size& distance_bottom_right, const ePositionMode position_mode, const eAutoSize auto_size) :
UUID<SDL_Object>(id),
	ObjectNode(parent_object),
	PositionObject(relative_rect, distance_bottom_right, position_mode, auto_size),

	pufferValid(false),
	drawPuffer(NULL),
	drawType(SOLID_OBJECT),
	wasShown(false),
	wasHidden(true),
	shown(true)
{
	Show();
}


SDL_Object::~SDL_Object()
{
	Show(false);

	if(SDL_Object::focus == this) {
		SDL_Object::resetFocus();
	}

	if(SDL_Object::highlighted == this) {
		SDL_Object::resetHighlighted();
	}

}













void SDL_Object::process()
{
	if(!isShown()) {
		return; 
	}

	bool transparent = (getDrawType() == TRANSPARENT_OBJECT) || (getDrawType() == ANTI_ALIASED_OBJECT);
	// 2. Bewege/Vergrößere/Verkleinere Objekte
	move((SDL_Object*)getParent());
	resetMoved();

	if(oldRect.getTopLeft() != getAbsolutePosition()) {
		setMoved();
	}

	if(oldRect.getSize() != getSize())
	{
		// we need to allocate a new draw puffer
		deleteDrawPuffer();
		// we need to inform parents and children about the size change
		signalSizeChange();
	}

	// 3. Falls bewegt, hidden oder (Transparent und invalid) füge Objekt zu OldRects mit altem Rect, ID und Z hinzu
	if((!pufferValid) && transparent || wasMoved() || wasHidden) {
		addToPreviousRects(ZRect(getId(), oldRect, getZ(), transparent));
	}

	if((!pufferValid) || wasMoved() || wasShown) {
		// 4. Falls Puffer invalid oder bewegt markiere TOP Rect als 'to paint'
		addToCurrentRects(ZRect(getId(), getAbsoluteRect(), getZ(), transparent, true));
	} else {
		// 5. Füge Objekt zu TOP Rects mit neuem Rect, ID, Z und Transparency hinzu
		addToCurrentRects(ZRect(getId(), getAbsoluteRect(), getZ(), transparent));
	}

	wasHidden = false;
	wasShown = false;

	// 1. Setze oldRect = aktuelles Rect, needs to be here at the end because process of the parent class might have changed the size or position!
	oldRect = getAbsoluteRect();

	// process children - targetsize and targetposition might change
	ObjectNode* tmp = getChildren();  // process all children of gadget
	if (tmp) {
		do {
			((SDL_Object*)tmp)->process();
			tmp = tmp->getNextBrother();
		} while (tmp != getChildren());
	}
}


void SDL_Object::processRects() {

	// TODO optimize
	for(std::list<ZRect>::const_iterator i = newRectList.begin(); i != newRectList.end(); i++) {
		if(i->isMarked()) {
			// 6. Betrachte alle "to paint" TOP Rects, markiere transparente Schnittrects darüberliegender TOP Rects als 'to paint'
			for(std::list<ZRect>::iterator j = newRectList.begin(); j != newRectList.end(); ) {
				if(i == j || !i->getRect().isTouched(j->getRect())) {
					j++;
					continue;
				}

				if((!j->isMarked()) && j->isTransparent() && j->isInFrontOf(*i)) {
					Rect cr = j->getRect().commonRect(i->getRect());
					std::list<Rect> wrj = j->getRect().withoutRect(i->getRect());
					addToCurrentRects(ZRect(j->getId(), cr, j->getZ(), true, true));
					for(std::list<Rect>::const_iterator k = wrj.begin(); k != wrj.end(); k++) {
						addToCurrentRects(ZRect(j->getId(), *k, j->getZ(), true, false));
					}
					j = newRectList.erase(j);
				} else 
					// 7. Betrachte alle nichttransparenten "to paint" TOP Rects, entferne Schnittrects darunterliegender TOP Rects
					if(!i->isTransparent() && i->isInFrontOf(*j)) {
						std::list<Rect> wr = j->getRect().withoutRect(i->getRect());
						for(std::list<Rect>::const_iterator k = wr.begin(); k != wr.end(); k++) {
							addToCurrentRects(ZRect(j->getId(), *k, j->getZ(), j->isTransparent(), j->isMarked()));
						}
						j = newRectList.erase(j);
					} else {
						j++;
					}
			}
		}
	}



	// 8. Betrachte alle old Rects, markiere transparente Schnittrects darüberliegender TOP Rects als 'to paint'
	for(std::list<ZRect>::iterator i = oldRectList.begin(); i != oldRectList.end(); i++) {

		for(std::list<ZRect>::iterator j = newRectList.begin(); j != newRectList.end(); ) {
			if(j->isMarked() || (!j->isTransparent()) || (!i->getRect().isTouched(j->getRect()))) {
				j++;
				continue;
			}

			if(j->isInFrontOf(*i)) {
				Rect cr = j->getRect().commonRect(i->getRect());
				std::list<Rect> wrj = j->getRect().withoutRect(i->getRect());
				addToCurrentRects(ZRect(j->getId(), cr, j->getZ(), true, true));
				for(std::list<Rect>::const_iterator k = wrj.begin(); k != wrj.end(); k++) {
					addToCurrentRects(ZRect(j->getId(), *k, j->getZ(), true, true));
				}
				j = newRectList.erase(j);
			} else {
				j++;
			}
		}
	}

	// 9. Betrachte alle old Rects, markiere Schnittrects darunterliegender TOP Rects als 'to paint', entferne oldRect Schnitte dabei
	for(std::list<ZRect>::iterator i = oldRectList.begin(); i != oldRectList.end(); ) {
		bool erased = false;
		for(std::list<ZRect>::iterator j = newRectList.begin(); j != newRectList.end(); ) {
			if((!j->isMarked()) && i->isInFrontOf(*j) && i->getRect().isTouched(j->getRect())){ 
				Rect cr = j->getRect().commonRect(i->getRect());
				std::list<Rect> wrj = j->getRect().withoutRect(i->getRect());
				addToCurrentRects(ZRect(j->getId(), cr, j->getZ(), j->isTransparent(), true));
				for(std::list<Rect>::const_iterator k = wrj.begin(); k != wrj.end(); k++) {
					addToCurrentRects(ZRect(j->getId(), *k, j->getZ(), j->isTransparent(), false));
				}

				wrj = i->getRect().withoutRect(j->getRect());
				for(std::list<Rect>::const_iterator k = wrj.begin(); k != wrj.end(); k++) {
					addToPreviousRects(ZRect(i->getId(), *k, i->getZ(), i->isTransparent()));
				}
				erased = true;
				i = oldRectList.erase(i);
				j = newRectList.erase(j);

				if(i == oldRectList.end()) {
					break;
				}
			} else {
				j++;
			}
		}
		if(!erased) {
			i++;
		}

	}



	// 10. Entferne alle Rects die nicht als 'to paint' markiert sind
	for(std::list<ZRect>::iterator j = newRectList.begin(); j != newRectList.end(); ) {
		if(!j->isMarked()) {
			j = newRectList.erase(j);
		} else {
			j++;
		}
	}



}


// cut borders of screen from rects
void SDL_Object::cutBorders(const Rect& screen) {
	ZRect::cutBorders(screen, oldRectList);
	ZRect::cutBorders(screen, newRectList);
}



void SDL_Object::updateAreasToUpdate()
{

	//	rootObjectList.sort(sort_objects_by_z());
	/*
	Update areas

	- if size/position has changed: add old and new rect OK
	- if puffer invalid: add new rect                    OK

	- remove same new rects with same or larger z

	- remove intersections of old rects with new rects with larger z
	*/

	//	ZRect::eraseOverlappingRects(newRectList);
	//	ZRect::eraseOverlappingRects(oldRectList);

	//durch alle Objekte laufen, oldRectList überprüfen und das größte z zuweisen

	for(std::list<ObjectNode*>::const_iterator i = rootObjectList.begin(); i != rootObjectList.end(); ++i) {
		((SDL_Object*)(*i))->checkHighestZ(oldRectList, newRectList);
	}
	//	Remove all newRects from oldRects 
	ZRect::eraseOverlappingRects(oldRectList, newRectList);

	/*
	Aktualisiere Gebiete:

	- if size/position has changed: add old and new rect
	- if puffer invalid: add new rect

	- remove same new rects with same z
	- remove intersections of old rects with new rects with larger z
	// - merge new rects?
	// - merge old rects?


	Copy contents:

	puffer invalid:
	- remove all areas with larger z (neues rect)

	puffer valid:
	- copy only intersection with larger z (altes rect)
	*/

}

void SDL_Object::checkHighestZ(std::list<ZRect>& old_rect_list, std::list<ZRect>& new_rect_list) {

	std::list<ZRect> add_to_list;

	// Finde die Rects der Elemente die am vordersten sind
	for(std::list<ZRect>::iterator i = old_rect_list.begin(); i != old_rect_list.end(); ) {

		if(i->getRect().isTouched(getAbsoluteRect())) {

			// old_rect vor Objekt?

			if(i->isInFrontOf(ZRect(getId(), Rect(), getZ())))
				// Oldrect ist näher am Betrachter => Dahinterliegendes (this) muss neugezeichnet werden
				// Suche größtes dahinterliegendes!
			{
				//		std::ostringstream os;
				//		os << "Old rect touches " << getAbsoluteRect().toString() << " with Z " << i->getZ() << ">=" << getZ() << " und ID " << i->ID << ">" << ID;
				//		to_init_log(os.str());


				//TODO größte ID?
				// jeder braucht noch TempID und tempz, sonst wird z.B. ID 2 durch ID 0 upgedated und ID 1 übersprungen!
				//	os.str("");
				//	os << "Update ID " << i->ID << " with ID " << ID;
				//	to_init_log(os.str());

				// part gets the new id, part gets the old id
				add_to_list.push_back(ZRect(getId(), i->getRect().commonRect(getAbsoluteRect()), i->getZ()));

				// füge Restteil ein
				std::list<Rect> wr = i->getRect().withoutRect(getAbsoluteRect());
				for(std::list<Rect>::iterator j = wr.begin(); j != wr.end(); j++) {
					add_to_list.push_back(ZRect(i->getId(), *j, i->getZ()));
					//		to_init_log("Add Z " + j->toString());
				}
				i = old_rect_list.erase(i);
			} else if(ZRect(getId(), Rect(), getZ()).isInFrontOf(*i))
			{
				//new_rect_list.push_back(ZRect(getId(), i->getRect().commonRect(getAbsoluteRect()), getZ()));
				add_to_list.push_back(ZRect(getId(), i->getRect().commonRect(getAbsoluteRect()), getZ()));
				//	to_init_log("Add new Rect from Z: " + i->getRect().commonRect(getAbsoluteRect()).toString() + "(rect: " + getAbsoluteRect().toString() + " / old rect: " + i->getRect().toString() + ")");
				//	std::ostringstream os;
				//	os << ID << " > " << i->ID;
				//	to_init_log(os.str());
				std::list<Rect> wr = i->getRect().withoutRect(getAbsoluteRect());
				for(std::list<Rect>::iterator j = wr.begin(); j != wr.end(); j++) {
					add_to_list.push_back(ZRect(i->getId(), *j, i->getZ()));
					//					to_init_log("Add Z " + j->toString());
				}
				i = old_rect_list.erase(i);				
			} else {
				i++;
			}
		} else {
			i++;
		}
	}
	old_rect_list.insert(old_rect_list.end(), add_to_list.begin(), add_to_list.end());


	// es können mehrere Rects ein Gebiet mit NewRect beanspruchen! Nur vordersten nehmen!
	// verdeckte newrects außerdem abschneiden! TODO

	for(std::list<ZRect>::iterator i = new_rect_list.begin(); i != new_rect_list.end(); ) {
		if(i->getRect().isTouched(getAbsoluteRect()) && 
			ZRect(getId(), Rect(), getZ()).isInFrontOf(*i)) {
				// Rechteck ist weiter entfernt, Davorliegendes muss nicht neugezeichnet werden
				// Entferne Teil von oldRectList
				//to_init_log("Remove " + i->getRect().commonRect(getAbsoluteRect()).toString() + " from newRect " + i->getRect().toString());
				// alte rect-Teile mit altem Z initialisieren
				std::list<Rect> l = i->getRect().withoutRect(getAbsoluteRect());
				for(std::list<Rect>::iterator j = l.begin(); j != l.end(); j++) {
					new_rect_list.push_back(ZRect(i->getId(), *j, i->getZ()));
				}
				new_rect_list.push_back(ZRect(getId(), i->getRect().commonRect(getAbsoluteRect()), getZ()));
				i = new_rect_list.erase(i);
		} else {
			i++;
		}
	}




	ObjectNode* tmp = getChildren();  // process all children of gadget
	if (tmp) {
		do {
			((SDL_Object*)tmp)->checkHighestZ(old_rect_list, new_rect_list);
			tmp = tmp->getNextBrother();
		} while (tmp != getChildren());
	}	
}


// put single object on screen
void SDL_Object::putOnScreen(DC* const dc)
{
	BOOST_ASSERT(dc);

	if (!isShown()) {
		return;
	}

	/*Copy contents:

	puffer invalid / moved:
	- remove all areas with larger z (neues rect)

	puffer valid:
	- copy only intersection with larger z (altes rect)
	*/
	//alle objekte mit newrect rein? mmh oder durch alle durchlaufen... bei highestZ... mmmh....
	std::list<Rect> blitRectList;
	/*
	// everything that isn't covered by other objects (newrects) needs to be redrawn
	if(!isPufferValid() || wasMoved()) { // size has changed, item has moved or contents have changed
	// first assume to blit everything
	Rect common_rect = Rect(Point(0,0), dc->getSize()).commonRect(getAbsoluteRect());
	if(common_rect.getSize() != Size()) {


	blitRectList.push_back(common_rect);

	// now remove all areas which are covered by new objects with a larger Z	
	for(std::list<ZRect>::iterator i = newRectList.begin(); i != newRectList.end(); i++) {
	if(i->isInFrontOf(ZRect(getId(), Rect(), getZ()))) {
	std::list<Rect> add_blit_rect_list;
	// check all blitRectList parts
	for(std::list<Rect>::iterator j = blitRectList.begin(); j != blitRectList.end(); ) {
	if(i->getRect().isTouched(*j)) {
	// remove the area which is overlapped by the new rectangle
	std::list<Rect> new_list = j->withoutRect(i->getRect());
	add_blit_rect_list.insert(add_blit_rect_list.end(), new_list.begin(), new_list.end());
	j = blitRectList.erase(j);
	} else {
	j++;
	}
	}
	blitRectList.insert(blitRectList.end(), add_blit_rect_list.begin(), add_blit_rect_list.end());
	add_blit_rect_list.clear();				
	}
	}		
	}



	// object was not moved or redrawn
	// no check required, except checking whether objects that were above
	// this object moved away.

	// only redraw parts that were formerly covered by other objects, we removed newRects from oldRects before
	else {
	for(std::list<ZRect>::iterator i = oldRectList.begin(); i != oldRectList.end(); i++) {
	if(i->getId() == getId()) {
	blitRectList.push_back(i->getRect());
	}
	}		
	}*/
	//	TODO newRectList immer leer!
	for(std::list<ZRect>::const_iterator i = newRectList.begin(); i != newRectList.end(); i++) {
		if(i->getId() == getId()) {
			blitRectList.push_back(i->getRect());
		}
	}

	if(blitRectList.size() > 0) {
		//Situation: Liegt B über C und A über B und C, dann eliminiert darüberliegendes B das old_rect komplett...
		//			   bzw. kein new_rect wird gesetzt!

		//	Liegt old_rect über 

		// use drawPuffer only with solid objects
		if(getDrawType() != ANTI_ALIASED_OBJECT)
		{
			bool clear_puffer = false;
			if(drawPuffer == NULL)
			{
				reinitializeDrawPuffer(dc);
			} else {
				if(getDrawType() == TRANSPARENT_OBJECT) {
					clear_puffer = true;
				}
			}

			if(!isPufferValid())
			{
				if(clear_puffer) {
					SDL_FillRect(drawPuffer, NULL, 0);
				}
				dc->switchToSurface(drawPuffer);
				dc->drawFromPoint(Point(0,0));		
				draw(dc); // fill puffer
				dc->switchToOriginalSurface();
				makePufferValid();
			}
			else {
				dc->drawFromPoint(getAbsolutePosition());
			}

			// copy rectangles from puffer to screen, add rectangle to dc screen update procedure
			for(std::list<Rect>::iterator i = blitRectList.begin(); i != blitRectList.end(); )
			{
				Point p = getAbsolutePosition();
				SDL_Rect source = Rect::createRect(i->getLeft() - p.getX(), i->getTop() - p.getY(), i->getWidth(), i->getHeight());
				SDL_Rect target = Rect::createRect(i->getLeft(), i->getTop(), 0, 0);
				SDL_BlitSurface(drawPuffer, &source, dc->getSurface(), &target);
				dc->addRectangle(*i);
				i = blitRectList.erase(i);
			}

		} else 
		{
			dc->addRectangle(getAbsoluteRect());
			dc->drawFromPoint(this->getAbsolutePosition());
			draw(dc);
		}



		blitRectList.clear();
	}


	ObjectNode* tmp = getChildren();
	if (tmp) {
		do {
			((SDL_Object*)tmp)->putOnScreen(dc);
			tmp = tmp->getNextBrother();
		} while (tmp != getChildren());
	}
}






void SDL_Object::signalSizeChange() {
	SDL_Object* temp_parent = (SDL_Object*)getParent();
	adjustPosition(temp_parent);
	
	// signal parent and child objects that the size has changed
	if(temp_parent) {
		temp_parent->adjustSize((SDL_Object*)(getParent()->getParent()), CHILD_WAS_CHANGED, getSize());
	}

	ObjectNode* tmp = getChildren();  // process all children of gadget
	if (tmp) {
		do {
			((SDL_Object*)tmp)->adjustSize(this, PARENT_WAS_CHANGED, getSize());
			((SDL_Object*)tmp)->adjustPosition(this);
			tmp = tmp->getNextBrother();
		} while (tmp != getChildren());
	}		

}


// don't call this function during initialization! oldrect will be initialized wrongly (? really?)
void SDL_Object::setZ(const signed int zcoord)
{
	// TODO ID?
	addToPreviousRects(ZRect(getId(), getAbsoluteRect(), getZ())); // TODO? does this work?

	ObjectNode::setZ(zcoord);

	addToCurrentRects(ZRect(getId(), getAbsoluteRect(), getZ()));
}


// contents of 'zrect' are now visible again, re-copy all objects at the top
void SDL_Object::addToPreviousRects(ZRect zrect) {
	oldRectList.push_back(zrect);
}


// contents of 'rect' were changed (because the object moved or because the object was redrawn)
void SDL_Object::addToCurrentRects(ZRect zrect) {
	newRectList.push_back(zrect);
}


void SDL_Object::makePufferInvalid() {
	pufferValid = false;
}


void SDL_Object::Show(const bool show)
{
	// show value has changed
	if(show != shown) {

		shown = show;

		if(SDL_Object::focus == this) {
			SDL_Object::resetFocus();
		}
		if(SDL_Object::highlighted == this) {
			SDL_Object::resetHighlighted();
		}

		wasHidden = !shown;
		wasShown = !shown;

		if(isShown()) {
			// draw the new item
			addToCurrentRects(ZRect(getId(), getAbsoluteRect(), getZ()));
		} else {
			// signal all objects that were below this object that they might need a redraw
			addToPreviousRects(ZRect(getId(), getAbsoluteRect(), getZ()));
		}

		if(getParent()) {
			getParent()->setChildrenWereChanged();
		}
	}
}

void SDL_Object::draw(DC* const dc) const {
	BOOST_ASSERT(dc);
}

void SDL_Object::deleteDrawPuffer() {
	SDL_FreeSurface(drawPuffer);
	drawPuffer = NULL;
	makePufferInvalid();
}


void SDL_Object::reinitializeDrawPuffer(DC* const dc) {
	const SDL_PixelFormat* pixel_format = dc->getSurface()->format;
	drawPuffer = SDL_CreateRGBSurface( SDL_SWSURFACE, getWidth(), getHeight(), dc->getBits(), pixel_format->Rmask, pixel_format->Gmask, pixel_format->Bmask, pixel_format->Amask);
	makePufferInvalid();
	if(getDrawType() == TRANSPARENT_OBJECT) {
		SDL_SetColorKey(drawPuffer, SDL_SRCCOLORKEY , SDL_MapRGB(drawPuffer->format, 0, 0, 0));
	}

}


/**
* Process all root objects
*/
void SDL_Object::processAll()
{
	for(std::list<ObjectNode*>::const_iterator i = rootObjectList.begin(); i != rootObjectList.end(); ++i) {
		((SDL_Object*)(*i))->process();
	}
}



void SDL_Object::drawAll(DC* const dc) {
	BOOST_ASSERT(dc);

	for(std::list<ObjectNode*>::const_iterator i = rootObjectList.begin(); i != rootObjectList.end(); i++ ) {		
		((SDL_Object*)(*i))->putOnScreen(dc);
	}

	oldRectList.clear();
	newRectList.clear();
}


SDL_Object* SDL_Object::checkHighlight(const Point& mouse)
{
	if(!isShown()) {
		return NULL;
	}

	ObjectNode* tmp = getChildren();  // process all children of gadget

	SDL_Object* result = NULL;
	if(tmp) {
		do 
		{
			result = ((SDL_Object*)tmp)->checkHighlight(mouse);
			tmp = tmp->getNextBrother();
		} while( tmp != getChildren() && (result == NULL) );
	}

	return result;
}

void SDL_Object::redrawAllRootObjects() {
	for(std::list<ObjectNode*>::const_iterator i = rootObjectList.begin(); i != rootObjectList.end(); i++ ) {		
		((SDL_Object*)(*i))->redrawWholeObject();
	}
}

void SDL_Object::redrawWholeObject() {
	if(!isShown()) {
		return;
	}

	makePufferInvalid();

	// todo evtl raus
	ObjectNode* tmp = getChildren();  // process all children of gadget
	if (tmp) {
		do {
			((SDL_Object*)tmp)->redrawWholeObject();
			tmp = tmp->getNextBrother();
		} while (tmp != getChildren());
	}	
}

void SDL_Object::reloadOriginalSize()
{

	//=> Bool Variable und dann in process pruefen (nach show) damit erst dann upgedatet wird wenn das Teil wieder gezeigt wird.  TODO

	ObjectNode* tmp = getChildren();  // process all children of gadget
	if (tmp) {
		do {
			((SDL_Object*)tmp)->reloadOriginalSize();
			tmp = tmp->getNextBrother();
		} while (tmp != getChildren());
	}

}

void SDL_Object::resetData()
{ 
	ObjectNode* tmp = getChildren();  // process all children of gadget
	if (tmp) {
		do {
			((SDL_Object*)tmp)->resetData();
			tmp = tmp->getNextBrother();

		} while (tmp != getChildren());
	}
}


const SDL_Object* SDL_Object::focus = NULL;
const SDL_Object* SDL_Object::highlighted = NULL;
std::list<ZRect> SDL_Object::oldRectList;
std::list<ZRect> SDL_Object::newRectList;
