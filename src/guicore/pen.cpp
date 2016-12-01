#include "pen.hpp"

#include "color_storage.hpp"

Pen::Pen(const boost::shared_ptr<const Color> color, const Uint16 width, const ePenStyle style):
	width(width),
	color(color),
	style(style)
{ }

Pen::Pen(const boost::uuids::uuid id, const boost::shared_ptr<const Color> color, const Uint16 width, const ePenStyle style):
	UUID<Pen>(id),
	width(width),
	color(color),
	style(style)
{ }

Pen::~Pen() { }

