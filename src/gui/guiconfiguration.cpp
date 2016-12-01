#include "guiconfiguration.hpp"
#include <misc/io.hpp>
#include <misc/miscellaneous.hpp>

GuiConfiguration::GuiConfiguration(
	const Size resolutionSize,
	const eBitDepth bitDepth,
	const bool fullScreen,

	const unsigned int desiredFramerate,
	const unsigned int desiredCPU,

	const bool unloadGraphics,
	const bool smoothMovements,
	const bool transparency,
	const bool softwareMouse,
	const bool glowingButtons,
	const bool toolTips		
	):
	UUID<GuiConfiguration>(),
resolutionSize(resolutionSize),
	bitDepth(bitDepth),
	fullScreen(fullScreen),
	desiredFramerate(desiredFramerate),
	desiredCPU(desiredCPU),
	unloadGraphics(unloadGraphics),
	smoothMovements(smoothMovements),
	transparency(transparency),
	softwareMouse(softwareMouse),
	glowingButtons(glowingButtons),
	toolTips(toolTips)
{ }

GuiConfiguration::GuiConfiguration(
        const boost::uuids::uuid id,
		const Size resolutionSize,
        const eBitDepth bitDepth,
        const bool fullScreen,

        const unsigned int desiredFramerate,
        const unsigned int desiredCPU,

        const bool unloadGraphics,
        const bool smoothMovements,
        const bool transparency,
        const bool softwareMouse,
        const bool glowingButtons,
        const bool toolTips
        ):
	UUID<GuiConfiguration>(id),
	resolutionSize(resolutionSize),
        bitDepth(bitDepth),
        fullScreen(fullScreen),
        desiredFramerate(desiredFramerate),
        desiredCPU(desiredCPU),
        unloadGraphics(unloadGraphics),
        smoothMovements(smoothMovements),
        transparency(transparency),
        softwareMouse(softwareMouse),
        glowingButtons(glowingButtons),
        toolTips(toolTips)
{ }

GuiConfiguration::~GuiConfiguration()
{ }