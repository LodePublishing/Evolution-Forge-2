#ifndef _GUI_FIXTURE_GUICONFIGURATIONFIXTURE_HPP
#define _GUI_FIXTURE_GUICONFIGURATIONFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <gui/guiconfiguration.hpp>
#include <map>

struct GuiConfiguration_Fixture
{
	const Size test_resolutionSize;
    const eBitDepth test_bitDepth;
    const bool test_fullScreen;
    const unsigned int test_desiredFramerate;
    const unsigned int test_desiredCPU;
    const bool test_unloadGraphics;
    const bool test_smoothMovements;
    const bool test_transparency;
    const bool test_softwareMouse;
    const bool test_glowingButtons;
    const bool test_toolTips;

	const boost::shared_ptr<const GuiConfiguration> test_guiConfiguration;

	GuiConfiguration_Fixture();	
	~GuiConfiguration_Fixture();

private:
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const GuiConfiguration> > test_guiConfigurationMap;
	const std::map<const boost::uuids::uuid, const boost::shared_ptr<const GuiConfiguration> > init_guiconfigurationmap_helper() const;
};

#endif // _GUI_FIXTURE_GUICONFIGURATIONFIXTURE_HPP
