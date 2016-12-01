#include "brush.hpp"
#include "color_storage.hpp"

Brush::Brush(const boost::shared_ptr<const Color>& color, const eBrushStyle style):
	color(color),
	style(style)
{ }

Brush::Brush(const boost::uuids::uuid id, const boost::shared_ptr<const Color>& color, const eBrushStyle style):
	UUID<Brush>(id),
	color(color),
	style(style)
{ }


Brush::~Brush()
{ }

template<class Archive>
void save_construct_data(Archive &ar, Brush* brush, const unsigned int version) { 

	const boost::uuids::uuid& id = brush->getId();
	const boost::uuids::uuid& colorId = brush->getColor()->getId();
	const eBrushStyle& style = brush->getStyle();

	if(version > 0) {
	}

	ar & BOOST_SERIALIZATION_NVP(id)
		& BOOST_SERIALIZATION_NVP(colorId)
		& BOOST_SERIALIZATION_NVP(style);
}

template<class Archive> 
void load_construct_data(Archive& ar, Brush*& brush, const unsigned int version)
{
	boost::uuids::uuid id;
	boost::uuids::uuid colorId;
	eBrushStyle style;

	ar & BOOST_SERIALIZATION_NVP(id)
		& BOOST_SERIALIZATION_NVP(colorId)
		& BOOST_SERIALIZATION_NVP(style);

	if(version > 0) {
	}
	
	::new(brush)Brush(id, ColorStorage::instance().get(colorId), style);
}