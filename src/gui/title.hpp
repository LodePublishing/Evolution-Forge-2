#ifndef _GUI_TITLE_HPP
#define _GUI_TITLE_HPP

#include "object.hpp"
#include "statictext.hpp"

#include <guicore/windowcolors.hpp>

class Title : public Object {
	public:
		Title(SDL_Object* const parent_object, 
			const boost::shared_ptr<const Text>& text, 
			const std::list<std::string>& parameterList,
			const boost::shared_ptr<const WindowColors>& window_colors);
		~Title();
		void draw(DC* const dc) const;
		
		void updateParameters(const std::list<std::string>& parameterList);

		// register in static text
		void updateTextAndSize(const std::string& text, const Size& size);
	private:
		StaticText* const title;
		const boost::shared_ptr<const WindowColors> windowColors;
};

#endif // _GUI_TITLE_HPP