#include "ColorPCH.h"
#include "Popup.h"

#include "Platform/Windows/WindowsPopup.h"
#include "Platform/Linux/LinuxPopup.h"

namespace Color
{
	Scope<Popup> Popup::Create(std::string_view caption, std::string_view content, PopupButtonSet buttonset, PopupIcon icon)
	{
		return CreateScope<CL_ConcatWithPlatformName(Popup)>(caption, content, buttonset, icon);
	}
}
