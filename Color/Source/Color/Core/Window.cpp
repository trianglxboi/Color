#include "ColorPCH.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Linux/LinuxWindow.h"

namespace Color
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<CL_ConcatWithPlatformName(Window)>(props);
	}
}
