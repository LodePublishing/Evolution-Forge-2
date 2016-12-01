#include "graphpoint.hpp"

#include <geometry/point.hpp>

GraphPoint::GraphPoint() :
	current_y1(0),
	start_y1(0),
	target_y1(0),
	current_y2(0),
	start_y2(0),
	target_y2(0),
	x(0),
	highlight(0),
	text()
{}
GraphPoint::GraphPoint(const Sint16 target_x, const Sint16 number_y1, const Sint16 number_y2, const std::string& point_text) :
	current_y1(number_y1),
	start_y1(number_y1),
	target_y1(number_y1),
	current_y2(number_y2),
	start_y2(number_y2),
	target_y2(number_y2),
	x(target_x),
	highlight(150),
	text(point_text)
{}


GraphPoint::~GraphPoint()
{}


bool GraphPoint::move()
{
	bool has_changed = false;
	if(Point::mv(current_y1, start_y1, target_y1)) {
		has_changed = true;
	}
	if(Point::mv(current_y2, start_y2, target_y2)) {
		has_changed = true;
	}
//	Sint16 h = (Sint16)highlight;
	if(Point::mv(highlight, 150, 100)) {
		has_changed = true;
	}
//	highlight = static_cast<Uint8>(h);
	return has_changed;
}

void GraphPoint::adjustTargetY(const Sint16 number_y1, const Sint16 number_y2)
{
	if(number_y1 != target_y1)
	{
		start_y1 = current_y1;
		target_y1 = number_y1;
		highlight = 150;
	}
	
	if(number_y2 != target_y2)
	{
		start_y2 = current_y2;
		target_y2 = number_y2;
		highlight = 150;
	}
}
void GraphPoint::setTargetY(const Sint16 number_y1, const Sint16 number_y2)
{
	if((number_y1 != target_y1) || ( number_y2 != target_y2)) {
		highlight = 150;
	}
	
	current_y1 = start_y1 = target_y1 = number_y1;
	current_y2 = start_y2 = target_y2 = number_y2;
}

void GraphPoint::setTargetX(Sint16 number_x) {
	x = number_x;
}

void GraphPoint::setText(const std::string& point_text) {
	text = point_text;
}

