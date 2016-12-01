#ifndef _GUI_GUI_HPP
#define _GUI_GUI_HPP

#include <set>
#include <map>
#include <math.h>

#include "enums/textid.hpp"
#include "tooltip.hpp"
#include "window.hpp"
#include "guiconfiguration.hpp"

#pragma warning(push, 0)
#include <boost/assert.hpp>
#pragma warning(pop)


class Gui : public UUID<Gui> {
	public:
		Gui(const boost::uuids::uuid id, const std::string& title, const std::string& iconTitle, const boost::shared_ptr<const GuiConfiguration> guiConfiguration);
		Gui(const std::string& title, const std::string& iconTitle, const boost::shared_ptr<const GuiConfiguration> guiConfiguration);
		~Gui();

		const std::string& getTitle() const;
		const std::string& getIconTitle() const;
		const boost::uuids::uuid getGuiConfigurationId() const;
		const boost::shared_ptr<const GuiConfiguration> getGuiConfiguration() const;

		DC* createScreen() const;
		void resetScreen(DC* dc) const;
		
		static const std::string& getVersion();

private:		
		const std::string title;
		const std::string iconTitle;
		const boost::shared_ptr<const GuiConfiguration> guiConfiguration;


// ------------------ SOUND AND MUSIC END -----------------------

		static const std::string GVERSION;
};


inline const boost::shared_ptr<const GuiConfiguration> Gui::getGuiConfiguration() const {
	return guiConfiguration;
}

inline const boost::uuids::uuid Gui::getGuiConfigurationId() const {
	return guiConfiguration->getId();
}

inline const std::string& Gui::getTitle() const {
	return title;
}

inline const std::string& Gui::getIconTitle() const {
	return iconTitle;
}

inline const std::string& Gui::getVersion() {
	return GVERSION;
}


#endif // _GUI_GUI_HPP



