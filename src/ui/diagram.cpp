#include "diagram.hpp"

#if 0


#pragma warning(push, 0)
#include <boost/assert.hpp>
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

Diagram::Diagram(SDL_Object* const diagram_parent, 
		const Rect& diagram_rect, 
		const Size distance_bottom_right,
		const boost::shared_ptr<const WindowColors>& windowColors,
		const ePositionMode position_mode) :
	Object(diagram_parent, 
			diagram_rect, 
			distance_bottom_right, 
			position_mode),
	graphMax(),
	graphList(),
	graphType(),
	graphPen(),
	graphDashedPen(),
	graphBrush(),
	itemText(),
	windowColors(windowColors)
{
	resetData();
}


Diagram::~Diagram()
{ 
	for(std::vector<PropertyField*>::iterator i = itemText.begin(); i != itemText.end(); ++i) {
		delete(*i);
	}
	itemText.clear();
}

void Diagram::showValues(const bool show) 
{
	for(std::vector<PropertyField*>::iterator i = itemText.begin(); i!= itemText.end(); ++i) {
		(*i)->showValue(show);
	}
}

void Diagram::addItem(const boost::shared_ptr<const Text>& item_text, const boost::shared_ptr<const Text>& item_value_text, const std::string& item_value, const boost::shared_ptr<const Color>& text_color, const boost::shared_ptr<const Color>& value_color)
{
	itemText.push_back(new PropertyField(this, Rect(Point(8, 15+13 * itemText.size()), Size(0,0)), Size(0,0), DO_NOT_ADJUST, 70, item_text, item_value_text, boost::assign::list_of(item_value), boost::shared_ptr<const Text>(), text_color, windowColors->getFont()));
}

void Diagram::addGraph(const boost::shared_ptr<const Pen>& graph_pen, 
	const boost::shared_ptr<const Pen>& graph_dashed_pen, 
	const boost::shared_ptr<const Brush>& graph_brush, 
	const eGraphType graph_type)
{
	graphPen.push_back(graph_pen);
	graphDashedPen.push_back(graph_dashed_pen);
	graphBrush.push_back(graph_brush);
	graphType.push_back(graph_type);
	std::list<GraphPoint> t;
	graphList.push_back(t);
	graphMax.push_back(1);
}




void Diagram::setItemValues(const std::vector<std::string>& value_list)
{
	BOOST_ASSERT(value_list.size() == itemText.size());

	std::vector<std::string>::const_iterator j = value_list.begin();
	for(std::vector<PropertyField*>::iterator i = itemText.begin(); i != itemText.end(); ++i, ++j) {
		(*i)->updateValueParameters(boost::assign::list_of(*j));
	}
}


void Diagram::reloadOriginalSize()
{
	Object::reloadOriginalSize();
	Sint16 h = 0;
	for(std::vector<PropertyField*>::iterator i = itemText.begin(); i != itemText.end(); ++i, ++h) {
		(*i)->setOriginalPosition(Point(8, 15 + 13 * h)); // TODO FONT_SIZE+5
	}
}

void Diagram::resetData()
{
	for(unsigned int i = 0; i < graphList.size(); ++i) {
		graphList[i].clear();
	}
}

void Diagram::process()
{
	if(!isShown()) {
		return;
	}
	Object::process();
	bool has_changed = false;
	
	if(SDL_Object::smoothMovements) {
		for(unsigned int k = 0; k < graphList.size(); ++k) {
			for(std::list<GraphPoint>::iterator i = graphList[k].begin(); i != graphList[k].end(); ++i) {
				if(i->move()) {
					has_changed = true;
				}
			}
		}
	}
	if(has_changed) {
		makePufferInvalid();
	}
}

void Diagram::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	dc->setBrush(windowColors->getBackgroundBrush());
	dc->setPen(windowColors->getBorderPen());
	dc->DrawRectangle(getRelativeRect());
	for(Sint16 x = 1; x < 10; x++) {
		dc->DrawVerticalLine(Point(x * (getWidth()-2) / 10 + 1, 1), getHeight() - 2);
	}
	for(Sint16 y = 1; y < 10; y++) {
		dc->DrawHorizontalLine(Point(1, y * (getHeight()-2) / 10 + 1), getWidth() - 2);
	}
	
	std::vector<float> scale(graphType.size());
	for(unsigned int i = graphType.size(); i--;) {
		scale[i] = (float)(getHeight() - 2)/(float)graphMax[i];
	}

	unsigned int diagram_first_box = 9999;
	
	for(unsigned int i = 0; i < graphType.size(); i++) {
		if(graphList[i].size())
		{
			switch(graphType[i])
			{
				case GRAPH_LINE:
				for(std::list<GraphPoint>::const_iterator item = graphList[i].begin(); item != graphList[i].end(); ++item)
				{
					std::list<GraphPoint>::const_iterator next_item = item;
					++next_item;
			
					Point p = Point(0, getHeight());
			
					Sint16 x = p.getX() + item->x;
					
					// TODO floor/ceil evtl
					Sint16 y1 = p.getY() - (Sint16)(item->current_y1 * scale[i]);
					Sint16 y2 = p.getY() - (Sint16)(item->current_y2 * scale[i]);
	
					if(y1 + 10 < y2) {
						dc->setPen(graphDashedPen[i]);
					} else {
						dc->setPen(graphPen[i]);
					}

					dc->setBrightness(item->highlight);
					if(y1<y2) {
						dc->DrawVerticalLine(Point(x, y1), y2-y1);
					} else {
						dc->DrawVerticalLine(Point(x, y2), y1-y2);
					}
					dc->resetBrightness();
					

					if(next_item != graphList[i].end())
					{
// TODO!!				pen = gui.lookUpPen((ePen)(graphPen[i] + ((/*(bold)||*/(item->highlight>100))?3:0)));  // TODO
//						dc->setPen(Pen(pen->getColor()->changeRelativeBrightness(dc->getSurface(), item->highlight), pen->getWidth(), pen->getStyle()));
						Sint16 goal_y1 = p.getY() - (Sint16)(next_item->current_y1 * scale[i]);
						Sint16 goal_y2 = p.getY() - (Sint16)(item->current_y2 * scale[i]);
						dc->DrawLine(Point(x, goal_y2), Point(p.getX() + next_item->x, goal_y1));
					} // end of  j != graphList.end()
				} // end of for
				break;
				case GRAPH_FILLED_LINE:break;
				case GRAPH_BOX:diagram_first_box = i;break;
				case GRAPH_SECOND_BOX:
					{
						BOOST_ASSERT(diagram_first_box != 9999);
//						dc->setBrush(*gui.lookUpBrush(graphBrush[i])); TODO!
			
						std::list<GraphPoint>::const_iterator item = graphList[diagram_first_box].begin();
						for(std::list<GraphPoint>::const_iterator item2 = graphList[i].begin(); item2 != graphList[i].end(); ++item, ++item2)
						{
							std::list<GraphPoint>::const_iterator next_item = item2;
							++next_item;
							if(next_item != graphList[i].end())
							{
								unsigned int y;
								if(item->current_y2 < item2->current_y2) {
									y = item2->current_y2 - item->current_y2;
								} else {
									y = item->current_y2 - item2->current_y2;
								}
						
								unsigned int high_light;
						
								if(item->highlight > item2->highlight) {
									high_light = item->highlight;
								} else {
									high_light = item2->highlight;
								}
		
								dc->setPen(graphPen[i]);
				
								dc->setBrightness(high_light);
								dc->DrawRectangle(Point(0, getHeight()) +
									Point(item->x, 0) - Size(0, (Sint16)(item->current_y2 * scale[i])),
									Size(next_item->x - item->x, static_cast<Uint16>(y * scale[i])));
								dc->resetBrightness();
							} // end of  j != graphList.end()
						} // end of for
					}
				 break;
				default:break;
			}
		}
	}
				

// first draw the supply:

// and finally the unit text:
	dc->setFont(windowColors->getFont());//gui.lookUpFont(SMALL_SHADOW_BOLD_FONT)); TODO? shadow...
	for(unsigned int i = 0; i < graphList.size(); i++) {
		for(std::list<GraphPoint>::const_iterator item = graphList[i].begin(); item != graphList[i].end(); ++item) {
			if(item->text!="") {
				std::list<GraphPoint>::const_iterator next_item = item;
				++next_item;
		
				Point p = Point(0, getHeight());
				if(next_item != graphList[i].end())
				{
					if(item != graphList[i].begin())
					{
						Sint16 y1 = p.getY() - (Sint16)(item->current_y1 * scale[i]);
						Sint16 y2 = p.getY() - (Sint16)(item->current_y2 * scale[i]);
						Sint16 x = p.getX() + item->x;
							// TODO sehr ungenau...
/*						bool mark = false;
						for(std::list<unsigned int>::const_iterator l = tempSelectedItems.begin(); l != tempSelectedItems.end(); ++l)
							if(*l == i->id)
							{
								mark = true;
								break;
							}
					
						if(mark)*/	
/*							dc->setTextForeground(*gui.lookUpColor(IMPORTANT_COLOR));
						else*/
							dc->setTextForeground(windowColors->getTextColor());// *gui.lookUpColor(BRIGHT_TEXT_COLOR)); TODO
						Uint16 width = (windowColors->getFont()->getTextExtent(item->text)).getWidth(); // gui.lookUpFont(SMALL_SHADOW_BOLD_FONT)->
						Sint16 tx;
						if(x - width/2 < 0) {
							tx = 0;
						} else if(x + width/2 >= getWidth()) {
							tx = getWidth() - width;
						} else {
							tx = x - width/2;
						}
						dc->DrawText(item->text, Point(tx, y1 + (y2 - y1)/2));
					}
				} // end of  j != graphList.end()
			} // end of if(item->text!="")
		} // end of for
	} // end of for

	dc->setPen(windowColors->getBorderPen());// *gui.lookUpPen(RECTANGLE_PEN));
//
		#if 0 
		if(infoWindow->isShown())
		{
			if(stats[(*anarace->getStartCondition())->getRace()][infoWindow->getUnit()].needSupply)
			{
				dc->setPen(*gui.lookUpPen(DASHED_SUPPLY_PEN));
				int y1=stats[(*anarace->getStartCondition())->getRace()][infoWindow->getUnit()].needSupply*5;
				if(y1<0) y1=-y1;
					dc->DrawHorizontalLine(getAbsoluteClientRectLeftBound()+infoWindow->getBx()+1,
								 getAbsoluteClientRectLowerBound()-y1, 
								 getAbsoluteClientRectLeftBound()+infoWindow->getBx()+infoWindow->getBWidth()-1);
			}

			if(stats[(*anarace->getStartCondition())->getRace()][infoWindow->getUnit()].minerals)
			{
				dc->setPen(*gui.lookUpPen(DASHED_MINERALS_PEN));
				dc->DrawHorizontalLine(getAbsoluteClientRectLeftBound()+infoWindow->getBx()+1,
							 getAbsoluteClientRectLowerBound()-stats[(*anarace->getStartCondition())->getRace()][infoWindow->getUnit()].minerals/1000,
							 getAbsoluteClientRectLeftBound()+infoWindow->getBx()+infoWindow->getBWidth()-1);
			}

			if(stats[(*anarace->getStartCondition())->getRace()][infoWindow->getUnit()].current[HAVE_GAS])
			{
				dc->setPen(*gui.lookUpPen(DASHED_GAS_PEN));
				dc->DrawHorizontalLine(getAbsoluteClientRectLeftBound()+infoWindow->getBx()+1,
							 getAbsoluteClientRectLowerBound()-stats[(*anarace->getStartCondition())->getRace()][infoWindow->getUnit()].current[HAVE_GAS]/1000,
							 getAbsoluteClientRectLeftBound()+infoWindow->getBx()+infoWindow->getBWidth()-1);
			}
			dc->setPen(*gui.lookUpPen(DASHED_MARKER_PEN));
			dc->DrawVerticalLine(getAbsoluteClientRectLeftBound()+infoWindow->getBx()+infoWindow->getBWidth(),
						 getAbsoluteClientRectUpperBound()+10,
						 getAbsoluteClientRectLowerBound());
						 
			dc->DrawVerticalLine(getAbsoluteClientRectLeftBound()+infoWindow->getBx(),
						 getAbsoluteClientRectUpperBound()+10,
						 getAbsoluteClientRectLowerBound());
		}
		#endif
	Object::draw(dc);
}

#endif