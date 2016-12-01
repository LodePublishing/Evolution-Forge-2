#ifndef WIN32
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_DYN_LINK
#else
#undef main
#endif

#define BOOST_TEST_MAIN

#pragma warning(push, 0) 
#include <boost/test/unit_test.hpp>
#pragma warning(pop)
#include "SDL.h"
#include <guicorefixture/bitmap_fixture.hpp>
#include <guicorefixture/brush_fixture.hpp>
#include <guicorefixture/buttonanimation_fixture.hpp>
#include <guicorefixture/buttoncolors_fixture.hpp>
#include <guicorefixture/color_fixture.hpp>
#include <guicorefixture/cursor_fixture.hpp>
#include <guicorefixture/font_fixture.hpp>
#include <guicorefixture/fonttype_fixture.hpp>
#include <guicorefixture/objectsize_fixture.hpp>
#include <guicorefixture/pen_fixture.hpp>
#include <guicorefixture/windowcolors_fixture.hpp>

#include <guicore/animation_storage.hpp>
#include <guicore/bitmap_storage.hpp>
#include <guicore/brush_storage.hpp>
#include <guicore/buttonanimation_storage.hpp>
#include <guicore/buttoncolors_storage.hpp>
#include <guicore/color_storage.hpp>
#include <guicore/cursor_storage.hpp>
#include <guicore/font_storage.hpp>
#include <guicore/fonttype_storage.hpp>
#include <guicore/objectsize_storage.hpp>
#include <guicore/pen_storage.hpp>
#include <guicore/windowcolors_storage.hpp>

// --- Bitmap ---

BOOST_FIXTURE_TEST_SUITE( Bitmap_test, Bitmap_Fixture )

	BOOST_AUTO_TEST_CASE (Bitmap_constructor)
{
	BOOST_CHECK_EQUAL(test_bitmap1->getFileName(), test_fileName1);
	BOOST_CHECK_EQUAL(test_bitmap2->getFileName(), test_fileName2);
	BOOST_CHECK_EQUAL(test_bitmap1->isTransparent(), test_transparent1);
	BOOST_CHECK_EQUAL(test_bitmap2->isTransparent(), test_transparent2);
	BOOST_CHECK_EQUAL((*test_bitmap1)->w, 302);
	BOOST_CHECK_EQUAL((*test_bitmap2)->w, 320);
}

BOOST_AUTO_TEST_CASE (Bitmap_storage)
{
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap1->getId())->getFileName(), test_fileName1);
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap2->getId())->getFileName(), test_fileName2);
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap1->getId())->isTransparent(), test_transparent1);
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap2->getId())->isTransparent(), test_transparent2);
	BOOST_CHECK_EQUAL((*BitmapStorage::instance().get(test_bitmap1->getId()))->w, 302);
	BOOST_CHECK_EQUAL((*BitmapStorage::instance().get(test_bitmap2->getId()))->w, 320);

	BitmapStorage::saveToXML();
	BitmapStorage::reset();

	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap1->getId())->getFileName(), test_fileName1);
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap2->getId())->getFileName(), test_fileName2);
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap1->getId())->isTransparent(), test_transparent1);
	BOOST_CHECK_EQUAL(BitmapStorage::instance().get(test_bitmap2->getId())->isTransparent(), test_transparent2);
	BOOST_CHECK_EQUAL((*BitmapStorage::instance().get(test_bitmap1->getId()))->w, 302);
	BOOST_CHECK_EQUAL((*BitmapStorage::instance().get(test_bitmap2->getId()))->w, 320);
}


BOOST_AUTO_TEST_SUITE_END( )

	// --- END Bitmap ---

	// --- Brush ---

	BOOST_FIXTURE_TEST_SUITE( Brush_test, Brush_Fixture )

	BOOST_AUTO_TEST_CASE (Brush_constructor)
{
	BOOST_CHECK_EQUAL(test_brush->getColor(), colorFixture.test_color);
	BOOST_CHECK_EQUAL(test_brush->getStyle(), test_style);
}

BOOST_AUTO_TEST_CASE (Brush_storage)
{
	BOOST_CHECK_EQUAL(BrushStorage::instance().get(test_brush->getId())->getColor(), colorFixture.test_color);
	BOOST_CHECK_EQUAL(BrushStorage::instance().get(test_brush->getId())->getStyle(), test_style);

	BrushStorage::saveToXML();
	BrushStorage::reset();

	BOOST_CHECK_EQUAL(BrushStorage::instance().get(test_brush->getId())->getColor(), colorFixture.test_color);
	BOOST_CHECK_EQUAL(BrushStorage::instance().get(test_brush->getId())->getStyle(), test_style);
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END Brush ---

	// --- ButtonAnimation ---

	BOOST_FIXTURE_TEST_SUITE( ButtonAnimation_test, ButtonAnimation_Fixture )


	BOOST_AUTO_TEST_CASE (ButtonAnimation_constructor)
{
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*test_buttonanimation->getStartBrush()->getColor()), static_cast<Uint32> (*startBrushFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*test_buttonanimation->getEndBrush()->getColor()), static_cast<Uint32> (*endBrushFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*test_buttonanimation->getStartTextColor()), static_cast<Uint32> (*startTextColorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*test_buttonanimation->getEndTextColor()), static_cast<Uint32> (*endTextColorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*test_buttonanimation->getStartBorderPen()->getColor()), static_cast<Uint32> (*startBorderPenFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*test_buttonanimation->getEndBorderPen()->getColor()), static_cast<Uint32> (*endBorderPenFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL((*test_buttonanimation->getBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
}

BOOST_AUTO_TEST_CASE (ButtonAnimation_storage)
{
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getStartBrush()->getColor()), static_cast<Uint32> (*startBrushFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getEndBrush()->getColor()), static_cast<Uint32> (*endBrushFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getStartTextColor()), static_cast<Uint32> (*startTextColorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getEndTextColor()), static_cast<Uint32> (*endTextColorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getStartBorderPen()->getColor()), static_cast<Uint32> (*startBorderPenFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getEndBorderPen()->getColor()), static_cast<Uint32> (*endBorderPenFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL((*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getBitmap())->w, (*bitmapFixture.test_bitmap1)->w);

	ButtonAnimationStorage::saveToXML();
	ButtonAnimationStorage::reset();

	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getStartBrush()->getColor()), static_cast<Uint32> (*startBrushFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getEndBrush()->getColor()), static_cast<Uint32> (*endBrushFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getStartTextColor()), static_cast<Uint32> (*startTextColorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getEndTextColor()), static_cast<Uint32> (*endTextColorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getStartBorderPen()->getColor()), static_cast<Uint32> (*startBorderPenFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL(static_cast<Uint32> (*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getEndBorderPen()->getColor()), static_cast<Uint32> (*endBorderPenFixture.colorFixture.test_color));
	BOOST_CHECK_EQUAL((*ButtonAnimationStorage::instance().get(test_buttonanimation->getId())->getBitmap())->w, (*bitmapFixture.test_bitmap1)->w);
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END ButtonAnimation ---

	// --- ButtonColors ---

	BOOST_FIXTURE_TEST_SUITE( ButtonColors_test, ButtonColors_Fixture )

	BOOST_AUTO_TEST_CASE (ButtonColors_constructor)
{
	BOOST_CHECK_EQUAL(test_buttoncolors->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(test_buttoncolors->getAnimationType(), test_animationType);

	BOOST_CHECK_EQUAL(test_buttoncolors->getButtonAnimation(DISABLED_BUTTON_PHASE)->getId(), buttonAnimationDisabledFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(test_buttoncolors->getButtonAnimation(NORMAL_BUTTON_PHASE)->getId(), buttonAnimationNormalFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(test_buttoncolors->getButtonAnimation(PRESSED_BUTTON_PHASE)->getId(), buttonAnimationPressedFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(test_buttoncolors->getButtonAnimation(HIGHLIGHT_BUTTON_PHASE)->getId(), buttonAnimationHighlightFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(test_buttoncolors->getButtonAnimation(PRESSED_HIGHLIGHTED_BUTTON_PHASE)->getId(), buttonAnimationPressedHighlightedFixture.test_buttonanimation->getId());
}

BOOST_AUTO_TEST_CASE (ButtonColors_storage)
{
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getAnimationType(), test_animationType);
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(DISABLED_BUTTON_PHASE)->getId(), buttonAnimationDisabledFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(NORMAL_BUTTON_PHASE)->getId(), buttonAnimationNormalFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(PRESSED_BUTTON_PHASE)->getId(), buttonAnimationPressedFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(HIGHLIGHT_BUTTON_PHASE)->getId(), buttonAnimationHighlightFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(PRESSED_HIGHLIGHTED_BUTTON_PHASE)->getId(), buttonAnimationPressedHighlightedFixture.test_buttonanimation->getId());

	ButtonColorsStorage::saveToXML();
	ButtonColorsStorage::reset();

	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getSpeed(), test_speed);
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getAnimationType(), test_animationType);
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(DISABLED_BUTTON_PHASE)->getId(), buttonAnimationDisabledFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(NORMAL_BUTTON_PHASE)->getId(), buttonAnimationNormalFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(PRESSED_BUTTON_PHASE)->getId(), buttonAnimationPressedFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(HIGHLIGHT_BUTTON_PHASE)->getId(), buttonAnimationHighlightFixture.test_buttonanimation->getId());
	BOOST_CHECK_EQUAL(ButtonColorsStorage::instance().get(test_buttoncolors->getId())->getButtonAnimation(PRESSED_HIGHLIGHTED_BUTTON_PHASE)->getId(), buttonAnimationPressedHighlightedFixture.test_buttonanimation->getId());
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END ButtonColors ---

	// --- Color ---

	BOOST_FIXTURE_TEST_SUITE( Color_test, Color_Fixture )

	BOOST_AUTO_TEST_CASE (Color_constructor)
{
	// TODO Test other functions
	BOOST_CHECK_EQUAL(test_color->r(), test_sdlcolor.r);
	BOOST_CHECK_EQUAL(test_color->g(), test_sdlcolor.g);
	BOOST_CHECK_EQUAL(test_color->b(), test_sdlcolor.b);
	// TODO ucolor?
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*test_color)).r, test_sdlcolor.r);
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*test_color)).g, test_sdlcolor.g);
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*test_color)).b, test_sdlcolor.b);
}

	BOOST_AUTO_TEST_CASE (Color_mix)
{
	Color temp_color(dcFixture.test_dc->getSurface(), 255, 100, 10);
		
	Color new_color = test_color->mixColor(dcFixture.test_dc->getSurface(), temp_color);

	int r = (test_sdlcolor.r + 255) / 2;
	int g = (test_sdlcolor.g + 100) / 2;
	int b = (test_sdlcolor.b + 10) / 2;
	
	BOOST_CHECK_EQUAL(new_color.r(), r);
	BOOST_CHECK_EQUAL(new_color.g(), g);
	BOOST_CHECK_EQUAL(new_color.b(), b);
}

	BOOST_AUTO_TEST_CASE (Color_mixGradient)
{
	Color temp_color(dcFixture.test_dc->getSurface(), 250, 100, 10);
		
	Color new_color = test_color->mixColor(dcFixture.test_dc->getSurface(), temp_color, 40);

	int r = (test_sdlcolor.r*40 + 250*60) / 100;
	int g = (test_sdlcolor.g*40 + 100*60) / 100;
	int b = (test_sdlcolor.b*40 + 10*60) / 100;
	
	BOOST_CHECK_EQUAL(new_color.r(), r);
	BOOST_CHECK_EQUAL(new_color.g(), g);
	BOOST_CHECK_EQUAL(new_color.b(), b);
}

	BOOST_AUTO_TEST_CASE (Color_absoluteBrightness)
{
	Color temp_color = test_color->changeAbsoluteBrightness(dcFixture.test_dc->getSurface(), 10);

	int r = test_sdlcolor.r + 10;
	int g = test_sdlcolor.g + 10;
	int b = test_sdlcolor.b + 10;

	if(r > 255) { r = 255; }
	if(g > 255) { g = 255; }
	if(b > 255) { b = 255; }
	
	BOOST_CHECK_EQUAL(temp_color.r(), r);
	BOOST_CHECK_EQUAL(temp_color.g(), g);
	BOOST_CHECK_EQUAL(temp_color.b(), b);
}

BOOST_AUTO_TEST_CASE(Color_absoluteBrightness_nop)
{
	Color temp_color = test_color->changeAbsoluteBrightness(dcFixture.test_dc->getSurface(), 0);
	BOOST_CHECK_EQUAL(temp_color.r(), test_sdlcolor.r);
	BOOST_CHECK_EQUAL(temp_color.g(), test_sdlcolor.g);
	BOOST_CHECK_EQUAL(temp_color.b(), test_sdlcolor.b);
}

BOOST_AUTO_TEST_CASE (Color_relativeBrightness)
{
	Color temp_color1 = test_color->changeRelativeBrightness(dcFixture.test_dc->getSurface(), 10);
	Color temp_color2 = test_color->changeRelativeBrightness(dcFixture.test_dc->getSurface(), 150);

	int r1 = test_sdlcolor.r / 10;
	int g1 = test_sdlcolor.g / 10;
	int b1 = test_sdlcolor.b / 10;

	int r2 = test_sdlcolor.r * 3 / 2;
	int g2 = test_sdlcolor.g * 3 / 2;
	int b2 = test_sdlcolor.b * 3 / 2;

	if(r2 > 255) { r2 = 255; }
	if(g2 > 255) { g2 = 255; }
	if(b2 > 255) { b2 = 255; }
	
	BOOST_CHECK_EQUAL(temp_color1.r(), r1);
	BOOST_CHECK_EQUAL(temp_color1.g(), g1);
	BOOST_CHECK_EQUAL(temp_color1.b(), b1);
	BOOST_CHECK_EQUAL(temp_color2.r(), r2);
	BOOST_CHECK_EQUAL(temp_color2.g(), g2);
	BOOST_CHECK_EQUAL(temp_color2.b(), b2);
}

BOOST_AUTO_TEST_CASE (Color_relativeBrightness_nop)
{
	Color temp_color1 = test_color->changeRelativeBrightness(dcFixture.test_dc->getSurface(), 100);
	Color temp_color2 = test_color->changeRelativeBrightness(dcFixture.test_dc->getSurface(), 0);

	BOOST_CHECK_EQUAL(temp_color1.r(), test_sdlcolor.r);
	BOOST_CHECK_EQUAL(temp_color1.g(), test_sdlcolor.g);
	BOOST_CHECK_EQUAL(temp_color1.b(), test_sdlcolor.b);
	BOOST_CHECK_EQUAL(temp_color2.r(), 0);
	BOOST_CHECK_EQUAL(temp_color2.g(), 0);
	BOOST_CHECK_EQUAL(temp_color2.b(), 0);
}

BOOST_AUTO_TEST_CASE (Color_storage)
{

	ColorStorage::init(dcFixture.test_dc->getSurface());

	BOOST_CHECK_EQUAL(ColorStorage::instance().get(test_color->getId())->r(), test_sdlcolor.r);
	BOOST_CHECK_EQUAL(ColorStorage::instance().get(test_color->getId())->g(), test_sdlcolor.g);
	BOOST_CHECK_EQUAL(ColorStorage::instance().get(test_color->getId())->b(), test_sdlcolor.b);
	BOOST_CHECK_EQUAL(static_cast<Uint32>(*ColorStorage::instance().get(test_color->getId())), static_cast<Uint32>(*test_color));
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*ColorStorage::instance().get(test_color->getId()))).r, test_sdlcolor.r);
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*ColorStorage::instance().get(test_color->getId()))).g, test_sdlcolor.g);
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*ColorStorage::instance().get(test_color->getId()))).b, test_sdlcolor.b);

	ColorStorage::saveToXML();
	ColorStorage::reset();
	ColorStorage::init(dcFixture.test_dc->getSurface());

	BOOST_CHECK_EQUAL(ColorStorage::instance().get(test_color->getId())->r(), test_sdlcolor.r);
	BOOST_CHECK_EQUAL(ColorStorage::instance().get(test_color->getId())->g(), test_sdlcolor.g);
	BOOST_CHECK_EQUAL(ColorStorage::instance().get(test_color->getId())->b(), test_sdlcolor.b);
	BOOST_CHECK_EQUAL(static_cast<Uint32>(*ColorStorage::instance().get(test_color->getId())), static_cast<Uint32>(*test_color));
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*ColorStorage::instance().get(test_color->getId()))).r, test_sdlcolor.r);
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*ColorStorage::instance().get(test_color->getId()))).g, test_sdlcolor.g);
	BOOST_CHECK_EQUAL((static_cast<SDL_Color>(*ColorStorage::instance().get(test_color->getId()))).b, test_sdlcolor.b);
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END Color ---

	// --- Cursor ---

	BOOST_FIXTURE_TEST_SUITE( Cursor_test, Cursor_Fixture )

	BOOST_AUTO_TEST_CASE (Cursor_constructor)
{
	// actual testing is done in sdlwraptest because cursor needs an initialized SDL environment
	BOOST_CHECK_EQUAL(test_arrowCursor->getFileName(), test_arrowFileName);
	BOOST_CHECK_EQUAL(test_handCursor->getFileName(), test_handFileName);
	BOOST_CHECK_EQUAL(test_clock1Cursor->getFileName(), test_clock1FileName);
	BOOST_CHECK_EQUAL(test_clock2Cursor->getFileName(), test_clock2FileName);

	BOOST_REQUIRE(((SDL_Cursor*)(*test_arrowCursor)) != NULL);
	BOOST_REQUIRE(((SDL_Cursor*)(*test_handCursor)) != NULL);
	BOOST_REQUIRE(((SDL_Cursor*)(*test_clock1Cursor)) != NULL);
	BOOST_REQUIRE(((SDL_Cursor*)(*test_clock2Cursor)) != NULL);
	
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_arrowCursor))->area.w, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_handCursor))->area.w, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_clock1Cursor))->area.w, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_clock2Cursor))->area.w, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_arrowCursor))->area.h, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_handCursor))->area.h, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_clock1Cursor))->area.h, 32);
	BOOST_CHECK_EQUAL(((SDL_Cursor*)(*test_clock2Cursor))->area.h, 32);
}

BOOST_AUTO_TEST_CASE (Cursor_storage)
{
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_arrowCursor->getId())->getFileName(), test_arrowFileName);
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_handCursor->getId())->getFileName(), test_handFileName);
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_clock1Cursor->getId())->getFileName(), test_clock1FileName);
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_clock2Cursor->getId())->getFileName(), test_clock2FileName);

	CursorStorage::saveToXML();
	CursorStorage::reset();

	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_arrowCursor->getId())->getFileName(), test_arrowFileName);
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_handCursor->getId())->getFileName(), test_handFileName);
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_clock1Cursor->getId())->getFileName(), test_clock1FileName);
	BOOST_CHECK_EQUAL(CursorStorage::instance().get(test_clock2Cursor->getId())->getFileName(), test_clock2FileName);
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END Cursor ---

	// --- Font ---

	BOOST_FIXTURE_TEST_SUITE( Font_test, Font_Fixture )

	BOOST_AUTO_TEST_CASE (Font_constructor)
{
	BOOST_CHECK_EQUAL(test_font->getFileName(), test_fileName);
	BOOST_CHECK_EQUAL(test_font->getSize(), test_size);
	BOOST_CHECK_EQUAL(test_font->isShadow(), test_shadow);
	BOOST_CHECK_EQUAL(test_font->isUnderlined(), test_underlined);
}

BOOST_AUTO_TEST_CASE (Font_storage)
{
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->getFileName(), test_fileName);
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->getSize(), test_size);
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->isShadow(), test_shadow);
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->isUnderlined(), test_underlined);

	FontStorage::saveToXML();
	FontStorage::reset();

	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->getFileName(), test_fileName);
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->getSize(), test_size);
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->isShadow(), test_shadow);
	BOOST_CHECK_EQUAL(FontStorage::instance().get(test_font->getId())->isUnderlined(), test_underlined);
}

BOOST_AUTO_TEST_CASE (Font_getTextExtent)
{
	Font* test_font2 = new Font(test_fileName, 16);
	/*BOOST_CHECK_EQUAL(test_font2->getTextExtent("Test").getWidth(), 34); // TODO different sizes win32/linux?
	BOOST_CHECK_EQUAL(test_font2->getTextExtent("Test").getHeight(), 25);
	BOOST_CHECK_EQUAL(test_font2->getTextExtent("Test a long string").getWidth(), 123);
	BOOST_CHECK_EQUAL(test_font2->getTextExtent("Test a long string").getHeight(), 25);*/
	delete test_font2;
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END Font ---

	// --- FontType ---

	BOOST_FIXTURE_TEST_SUITE( FontType_test, FontType_Fixture )

	BOOST_AUTO_TEST_CASE (FontType_constructor)
{
	BOOST_CHECK_EQUAL(test_fonttype->getNormalFont()->getId(), test_fontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getBoldFont()->getId(), test_boldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getShadowFont()->getId(), test_shadowFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getUnderlinedFont()->getId(), test_underlinedFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getShadowBoldFont()->getId(), test_shadowBoldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getShadowUnderlinedFont()->getId(), test_shadowUnderlinedFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getUnderlinedBoldFont()->getId(), test_underlinedBoldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_fonttype->getShadowUnderlinedBoldFont()->getId(), test_shadowUnderlinedBoldFontFixture.test_font->getId());
}

BOOST_AUTO_TEST_CASE (FontType_storage)
{
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getNormalFont()->getId(), test_fontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getBoldFont()->getId(), test_boldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowFont()->getId(), test_shadowFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getUnderlinedFont()->getId(), test_underlinedFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowBoldFont()->getId(), test_shadowBoldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowUnderlinedFont()->getId(), test_shadowUnderlinedFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getUnderlinedBoldFont()->getId(), test_underlinedBoldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowUnderlinedBoldFont()->getId(), test_shadowUnderlinedBoldFontFixture.test_font->getId());

	FontTypeStorage::saveToXML();
	FontTypeStorage::reset();

	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getNormalFont()->getId(), test_fontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getBoldFont()->getId(), test_boldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowFont()->getId(), test_shadowFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getUnderlinedFont()->getId(), test_underlinedFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowBoldFont()->getId(), test_shadowBoldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowUnderlinedFont()->getId(), test_shadowUnderlinedFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getUnderlinedBoldFont()->getId(), test_underlinedBoldFontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(FontTypeStorage::instance().get(test_fonttype->getId())->getShadowUnderlinedBoldFont()->getId(), test_shadowUnderlinedBoldFontFixture.test_font->getId());
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END FontType ---

	// --- ObjectSize ---

	BOOST_FIXTURE_TEST_SUITE( ObjectSize_test, ObjectSize_Fixture )

	BOOST_AUTO_TEST_CASE (ObjectSize_constructor)
{
	BOOST_CHECK_EQUAL(test_objectsize->getWidth(), test_width);
	BOOST_CHECK_EQUAL(test_objectsize->getHeight(), test_height);
}

BOOST_AUTO_TEST_CASE (ObjectSize_storage)
{
	BOOST_CHECK_EQUAL(ObjectSizeStorage::instance().get(test_objectsize->getId())->getWidth(), test_width);
	BOOST_CHECK_EQUAL(ObjectSizeStorage::instance().get(test_objectsize->getId())->getHeight(), test_height);

	ObjectSizeStorage::saveToXML();
	ObjectSizeStorage::reset();

	BOOST_CHECK_EQUAL(ObjectSizeStorage::instance().get(test_objectsize->getId())->getWidth(), test_width);
	BOOST_CHECK_EQUAL(ObjectSizeStorage::instance().get(test_objectsize->getId())->getHeight(), test_height);
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END ObjectSize ---

	// --- Pen ---

	BOOST_FIXTURE_TEST_SUITE( Pen_test, Pen_Fixture )

	BOOST_AUTO_TEST_CASE (Pen_constructor)
{
	BOOST_CHECK_EQUAL(static_cast<Uint32>(*test_pen->getColor()), static_cast<Uint32> (*colorFixture.test_color));
	BOOST_CHECK_EQUAL(test_pen->getStyle(), test_style);
	BOOST_CHECK_EQUAL(test_pen->getWidth(), test_width);
}

BOOST_AUTO_TEST_CASE (Pen_storage)
{
	BOOST_CHECK_EQUAL(static_cast<Uint32>(*PenStorage::instance().get(test_pen->getId())->getColor()), static_cast<Uint32> (*colorFixture.test_color));
	BOOST_CHECK_EQUAL(PenStorage::instance().get(test_pen->getId())->getStyle(), test_style);
	BOOST_CHECK_EQUAL(PenStorage::instance().get(test_pen->getId())->getWidth(), test_width);

	PenStorage::saveToXML();
	PenStorage::reset();

	BOOST_CHECK_EQUAL(static_cast<Uint32>(*PenStorage::instance().get(test_pen->getId())->getColor()), static_cast<Uint32> (*colorFixture.test_color));
	BOOST_CHECK_EQUAL(PenStorage::instance().get(test_pen->getId())->getStyle(), test_style);
	BOOST_CHECK_EQUAL(PenStorage::instance().get(test_pen->getId())->getWidth(), test_width);
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END Pen ---

	// --- WindowColors ---

	BOOST_FIXTURE_TEST_SUITE( WindowColors_test, WindowColors_Fixture )

	BOOST_AUTO_TEST_CASE (WindowColors_constructor)
{
	BOOST_CHECK_EQUAL(test_windowcolors->getFont()->getId(), fontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(test_windowcolors->getTextColor()->getId(), textColorFixture.test_color->getId());
	BOOST_CHECK_EQUAL(test_windowcolors->getBackgroundBrush()->getId(), backgroundBrushFixture.test_brush->getId());
	BOOST_CHECK_EQUAL(test_windowcolors->getBorderPen()->getId(), borderPenFixture.test_pen->getId());
	BOOST_CHECK_EQUAL(test_windowcolors->getOuterBorderPen()->getId(), outerBorderPenFixture.test_pen->getId());
	BOOST_CHECK_EQUAL(test_windowcolors->getHighlightedBorderPen()->getId(), highlightedBorderPenFixture.test_pen->getId());
}

BOOST_AUTO_TEST_CASE (WindowColors_storage)
{
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getFont()->getId(), fontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getTextColor()->getId(), textColorFixture.test_color->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getBackgroundBrush()->getId(), backgroundBrushFixture.test_brush->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getBorderPen()->getId(), borderPenFixture.test_pen->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getOuterBorderPen()->getId(), outerBorderPenFixture.test_pen->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getHighlightedBorderPen()->getId(), highlightedBorderPenFixture.test_pen->getId());

	WindowColorsStorage::saveToXML();
	WindowColorsStorage::reset();

	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getFont()->getId(), fontFixture.test_font->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getTextColor()->getId(), textColorFixture.test_color->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getBackgroundBrush()->getId(), backgroundBrushFixture.test_brush->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getBorderPen()->getId(), borderPenFixture.test_pen->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getOuterBorderPen()->getId(), outerBorderPenFixture.test_pen->getId());
	BOOST_CHECK_EQUAL(WindowColorsStorage::instance().get(test_windowcolors->getId())->getHighlightedBorderPen()->getId(), highlightedBorderPenFixture.test_pen->getId());
}

BOOST_AUTO_TEST_SUITE_END( )

	// --- END WindowColors ---


	// required because of SDL
	int main( int argc, char* argv[] )
{
#ifdef WIN32
	return ::boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv); 
#else
	return ::boost::unit_test::unit_test_main(&init_unit_test, argc, argv); 
#endif
}
