#ifndef _GUI_GUICONFIGURATION_HPP
#define _GUI_GUICONFIGURATION_HPP

#pragma warning(push, 0)  
#include <boost/uuid/uuid.hpp>
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <misc/uuid.hpp>
#include <geometry/size.hpp>
#include <sdlwrap/enums/bitdepth.hpp>
#include <guicore/bitmap.hpp>

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
                const boost::shared_ptr<const Bitmap> backgroundBitmap,
                const bool softwareMouse,
                const bool glowingButtons,
                const bool toolTips,
                const bool dnaSpiral
                );

	GuiConfiguration(const Size resolutionSize,
		const eBitDepth bitDepth,
		const bool fullScreen,
		const unsigned int desiredFramerate,
		const unsigned int desiredCPU,
		const bool unloadGraphics,
		const bool smoothMovements,
		const bool transparency,
		const boost::shared_ptr<const Bitmap> backgroundBitmap,
		const bool softwareMouse,
		const bool glowingButtons,
		const bool toolTips,
		const bool dnaSpiral		
		);

	Size getResolutionSize() const;
	eBitDepth getBitDepth() const;
	bool isFullScreen() const;
	unsigned int getDesiredFramerate() const;
	unsigned int getDesiredCPU() const;
	bool isUnloadGraphics() const;
	bool isSmoothMovements() const;		
	bool isTransparency() const;
	const boost::shared_ptr<const Bitmap> getBackgroundBitmap() const;
	bool isSoftwareMouse() const;
	bool isGlowingButtons() const;
	bool isToolTips() const;
	bool isDnaSpiral() const;

	const boost::shared_ptr<const GuiConfiguration> getDefaultConfiguration();
	~GuiConfiguration();

private:
	const Size resolutionSize;
	const eBitDepth bitDepth;
	const bool fullScreen;
	const unsigned int desiredFramerate; // X Frames per generation
	const unsigned int desiredCPU; // hold X FPS

	const bool unloadGraphics;
	const bool smoothMovements;
	const bool transparency;
	const boost::shared_ptr<const Bitmap> backgroundBitmap;
	const bool softwareMouse;
	const bool glowingButtons;
	const bool toolTips;
	const bool dnaSpiral;

	static const boost::shared_ptr<const GuiConfiguration> defaultConfiguration;

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

inline const boost::shared_ptr<const Bitmap> GuiConfiguration::getBackgroundBitmap() const {
	return backgroundBitmap;
}

inline bool GuiConfiguration::isDnaSpiral() const {
	return dnaSpiral;
}

inline bool GuiConfiguration::isSoftwareMouse() const {
	return softwareMouse;
}

inline const boost::shared_ptr<const GuiConfiguration> GuiConfiguration::getDefaultConfiguration() {
	return defaultConfiguration;
}

#endif // _GUI_GUICONFIGURATION_HPP
