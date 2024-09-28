#pragma once

#include "Platform/Generic/GenericWindow.h"

namespace Color
{
	class WindowsWindow : public GenericWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
	};
}
