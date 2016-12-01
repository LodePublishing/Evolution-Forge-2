#ifndef _GUI_MULTILINETEXT_HPP
#define _GUI_MULTILINETEXT_HPP

#include <vector>

#include <lang/text.hpp>

#include <guicore/windowcolors.hpp>
#include "basictext.hpp"

class MultiLineText : public BasicText
{
public:
	MultiLineText(SDL_Object* const mlt_parent, 
		const Rect& mlt_pos,
		const boost::shared_ptr<const Text>& text,
		const std::list<std::string>& parameterList,
		const boost::shared_ptr<const WindowColors> window_colors);
	~MultiLineText();

	void draw(DC* const dc) const;
	void process();
	void reloadOriginalSize();

	void updateParameters(const std::list<std::string> parameterList) const;
	// use public boost::signals::trackable on the object wanting to connect to test
	// .connect(boost::bind(&CLASS::function, this, _1));
	boost::signals::connection connect(boost::signal<void (std::string, Size)>::slot_function_type subscriber) const;
	void disconnect(boost::signals::connection subscriber) const;

private:	
	std::string drawText;
	mutable boost::signal<void (std::string, Size)> sig;
	void updateText(const std::string& text);

	const boost::shared_ptr<const WindowColors> windowColors;
	const boost::shared_ptr<const Text> text;



	std::vector<std::pair<int, int> > linebreaks;
};


inline void MultiLineText::updateParameters(const std::list<std::string> parameterList) const {
	text->updateParameters(parameterList);
}


inline boost::signals::connection MultiLineText::connect(boost::signal<void (std::string, Size)>::slot_function_type subscriber) const {
	return sig.connect(subscriber);
}

inline void MultiLineText::disconnect(boost::signals::connection subscriber) const {
	subscriber.disconnect();
}



#endif // _GUI_MULTILINETEXT_HPP
