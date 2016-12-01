#ifndef _GUICORE_FIXTURE_BITMAPFIXTURE_HPP
#define _GUICORE_FIXTURE_BITMAPFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/shared_ptr.hpp>
#pragma warning(pop)

#include <guicore/bitmap.hpp>
#include <map>

struct Bitmap_Fixture
{
	const std::string test_fileName1;
	const std::string test_fileName2;

	const boost::shared_ptr<const Bitmap> test_bitmap1;
	const boost::shared_ptr<const Bitmap> test_bitmap2;

	Bitmap_Fixture();	
	~Bitmap_Fixture();
private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Bitmap> > test_bitmapMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const Bitmap> > init_bitmapmap_helper();
};

#endif // _GUICORE_FIXTURE_BITMAPFIXTURE_HPP
