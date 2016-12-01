#ifndef _LANG_TEXT_HPP
#define _LANG_TEXT_HPP

#include <string>
#include <map>

#pragma warning(push, 0)  
#include <boost/signals.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include <misc/miscellaneous.hpp>


class Text : public UUID<Text>
{
public:
		Text(const std::map<const boost::uuids::uuid, const std::string>& textMap);
		Text(const boost::uuids::uuid id, const std::map<const boost::uuids::uuid, const std::string>& textMap);
		~Text() { }

		void updateLanguage(const boost::uuids::uuid languageId) const;
		void updateParameters(const std::list<std::string> parameterList) const;

		// use public boost::signals::trackable on the object wanting to connect to test
		// .connect(boost::bind(&CLASS::function, this, _1));
		boost::signals::connection connect(boost::signal<void (std::string)>::slot_function_type subscriber) const;
		void disconnect(boost::signals::connection subscriber) const;
		const std::map<const boost::uuids::uuid, const std::string>& getTextMap() const;
	const std::string& getText() const;
private:
	const std::map<const boost::uuids::uuid, const std::string> textMap; // languageId -> string
	
	// only indirect access via signals!
	
	const std::string& getText(const boost::uuids::uuid languageId) const;
	void updateText(const std::string& text) const;

	mutable boost::signal<void (std::string)> sig;
	mutable boost::uuids::uuid languageId;
};
// current Text
inline const std::string& Text::getText() const {
	return getText(languageId);
}


inline boost::signals::connection Text::connect(boost::signal<void (std::string)>::slot_function_type subscriber) const {
	return sig.connect(subscriber);
}

inline void Text::disconnect(boost::signals::connection subscriber) const {
	subscriber.disconnect();
}

inline const std::string& Text::getText(const boost::uuids::uuid languageId) const {
	if(textMap.find(languageId) == textMap.end()) {
		throw std::exception();
	}
	this->languageId = languageId;
	return textMap.find(languageId)->second;
}

inline const std::map<const boost::uuids::uuid, const std::string>& Text::getTextMap() const {
	return textMap;
}

inline void Text::updateLanguage(const boost::uuids::uuid languageId) const {
	updateText(getText(languageId));
}

inline void Text::updateParameters(const std::list<std::string> parameterList) const {
	std::string newString = getText(languageId);
	Misc::formatString(newString, parameterList);
	updateText(newString);
}


// signals all (UI) Objects that have registered this text that the text has changed TODO hack?
inline void Text::updateText(const std::string& text) const {
	sig(text);
}

#endif // _LANG_TEXT_HPP
