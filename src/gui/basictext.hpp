#ifndef _GUI_BASICTEXT_HPP
#define _GUI_BASICTEXT_HPP

#include "object.hpp"

class BasicText : public Object
{
	public:
		BasicText(SDL_Object* const st_parent, 
			const Rect& st_pos, 
			const Size& distance_bottom_right, 
			const boost::shared_ptr<const Text>& st_text,
			const std::list<std::string>& parameterList,
			const ePositionMode position_mode = HORIZONTALLY_CENTERED,
			const eAutoSize auto_size = AUTO_SIZE);
		~BasicText();
		
		void updateParameters(const std::list<std::string> parameterList) const;
		// use public boost::signals::trackable on the object wanting to connect to test
        // .connect(boost::bind(&CLASS::function, this, _1));
        boost::signals::connection connect(boost::signal<void (std::string, Size)>::slot_function_type subscriber) const;
        void disconnect(boost::signals::connection subscriber) const;
	protected:
		std::string drawText;
		const boost::shared_ptr<const Text> text;
		mutable boost::signal<void (std::string, Size)> sig;
		
		// register this in the text object signal
		virtual void updateText(const std::string& text) = 0;
	private:
		BasicText& operator=(const BasicText& object);
		BasicText(const BasicText& object);
};



inline boost::signals::connection BasicText::connect(boost::signal<void (std::string, Size)>::slot_function_type subscriber) const {
        return sig.connect(subscriber);
}

inline void BasicText::disconnect(boost::signals::connection subscriber) const {
        subscriber.disconnect();
}

inline void BasicText::updateParameters(const std::list<std::string> parameterList) const {
	text->updateParameters(parameterList);
}

#endif // _GUI_BASICTEXT_HPP

