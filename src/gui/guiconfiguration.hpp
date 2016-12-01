#ifndef _GUI_GUICONFIGURATION_HPP
#define _GUI_GUICONFIGURATION_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include <geometry/size.hpp>
#include <sdlwrap/enums/bitdepth.hpp>

class GuiConfiguration : public UUID<GuiConfiguration>
{
public:
        GuiConfiguration(const boost::uuids::uuid id,
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
                );

	GuiConfiguration(const Size resolutionSize,
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
		);

	~GuiConfiguration();

	Size getResolutionSize() const;
	eBitDepth getBitDepth() const;
	bool isFullScreen() const;
	unsigned int getDesiredFramerate() const;
	unsigned int getDesiredCPU() const;
	bool isUnloadGraphics() const;
	bool isSmoothMovements() const;		
	bool isTransparency() const;
	bool isToolTips() const;
	bool isSoftwareMouse() const;
	bool isGlowingButtons() const;	

private:
	const Size resolutionSize;
	const eBitDepth bitDepth;
	const bool fullScreen;
	const unsigned int desiredFramerate; // X Frames per generation
	const unsigned int desiredCPU; // hold X FPS

	const bool unloadGraphics;
	const bool smoothMovements;
	const bool transparency;
	const bool softwareMouse;
	const bool glowingButtons;
	const bool toolTips;
	
	GuiConfiguration();
};

inline eBitDepth GuiConfiguration::getBitDepth() const {
	return bitDepth;
}

inline Size GuiConfiguration::getResolutionSize() const {
	return resolutionSize;
}

inline bool GuiConfiguration::isFullScreen() const {
	return fullScreen;
}

inline unsigned int GuiConfiguration::getDesiredFramerate() const {
	return desiredFramerate;
}

inline unsigned int GuiConfiguration::getDesiredCPU() const {
	return desiredCPU;
}

inline bool GuiConfiguration::isGlowingButtons() const {
	return glowingButtons;
}

inline bool GuiConfiguration::isTransparency() const {
	return transparency;
}

inline bool GuiConfiguration::isUnloadGraphics() const {
	return unloadGraphics;
}

inline bool GuiConfiguration::isToolTips() const {
	return toolTips;
}

inline bool GuiConfiguration::isSmoothMovements() const {
	return smoothMovements;
}

inline bool GuiConfiguration::isSoftwareMouse() const {
	return softwareMouse;
}

#endif // _GUI_GUICONFIGURATION_HPP
