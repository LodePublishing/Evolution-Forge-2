#ifndef _GUI_LONGTEXT_HPP
#define _GUI_LONGTEXT_HPP


#include "button.hpp"
#include <guicore/fonttype.hpp>
#include "basictext.hpp"

class LongText : public BasicText
{
public:
	LongText(SDL_Object* const lt_parent, 
		const Rect lt_pos,
		const Size distance_bottom_right,
		const boost::shared_ptr<const Text>& text,  // place holder of the actual text
		const std::list<std::string>& parameterList,
		const boost::shared_ptr<const Text>& lineFormatText, // empty line with one string-placeholder, maybe some formatters at the end and beginning
		const boost::shared_ptr<const Color>& lt_color1, 
		const boost::shared_ptr<const Color>& lt_color2, 
		const boost::shared_ptr<const FontType>& lt_font, 
		const boost::shared_ptr<const FontType>& big_lt_font,
		const boost::shared_ptr<const ButtonColors>& lt_button, 
		const boost::shared_ptr<const ButtonColors>& lt_visited_button,// = TEXT_BUTTON, 
		Object* scroll_bar = NULL, 
		bool use_help_chapters = false, 
		const ePositionMode lt_mode = DO_NOT_ADJUST, 
		const eAutoSize auto_size = NO_AUTO_SIZE);

	~LongText();

	void reloadOriginalSize();

	void draw(DC* const dc) const;
	void process();

	const signed int getPressed() const;
	Uint16 getTextHeight() const;
	Uint16 getTextWidth() const;

	void updateParameters(const std::list<std::string> parameterList) const;
	// use public boost::signals::trackable on the object wanting to connect to test
	// .connect(boost::bind(&CLASS::function, this, _1));
	boost::signals::connection connect(boost::signal<void (std::string, Size)>::slot_function_type subscriber) const;
	void disconnect(boost::signals::connection subscriber) const;

private:
	std::string drawText;
	mutable boost::signal<void (std::string, Size)> sig;
	void updateText(const std::string& text);

	Object* scrollBar;
	std::list<StaticText*> longText; // parsed text
	std::list<Button*> longButton; // parsed buttons
	std::list<signed int> longNumber; // numbers of parsed buttons
	std::list<BitmapObject*> longBitmap; // parsed Bitmaps TODO

	const boost::shared_ptr<const Color> color1;
	const boost::shared_ptr<const Color> color2;
	const boost::shared_ptr<const FontType> fontType;
	const boost::shared_ptr<const FontType> bigFontType;
	const boost::shared_ptr<const ButtonColors> button;
	const boost::shared_ptr<const ButtonColors> visitedButton;
	const boost::shared_ptr<const Text> lineFormatText;
	bool useHelpChapters;

	LongText& operator=(const LongText& object);
	LongText(const LongText& object);
};

#endif // _GUI_LONGTEXT_HPP

