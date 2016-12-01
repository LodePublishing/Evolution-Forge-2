#ifndef _LANG_TEXTLISTENER_HPP
#define _LANG_TEXTLISTENER_HPP

#include "text.hpp"
#include <string>
#include <list>
#include <sstream>

#pragma warning(push, 0)
#include <boost/shared_ptr.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#pragma warning(pop)


template <typename T> 
class TextListener
{
public:
	TextListener(const boost::shared_ptr<const Text>& text):
		text(text)
	{ 
		//this->text->connect(boost::bind(&T::updateText, this, _1));
		//this->text->updateParameters(parameterList);
	}
	~TextListener() { }

	// use public boost::signals::trackable on the object wanting to connect to test
	// .connect(boost::bind(&CLASS::function, this, _1, _2));
	boost::signals::connection connect(boost::signal<void (const std::string&, const unsigned int& width, const unsigned int& height)>::slot_function_type subscriber) {
		return sig.connect(subscriber);
	}
	void disconnect(boost::signals::connection subscriber) const {
		subscriber.disconnect();
	}
	// update variable part of the text
//	void updateParameters(const std::list<std::string>& parameterList) {
//		text->updateParameters(parameterList);
//	}

protected:
	// hook for signal from Text
	//void updateText(const std::string& text);

	mutable boost::signal<void (const std::string&, const unsigned int& width, const unsigned int& height)> sig;

private:
	//const boost::shared_ptr<const Text> text;

	TextListener& operator=(const TextListener& object);
	TextListener(const TextListener& object);
};


#endif // _LANG_TEXTLISTENER_HPP

