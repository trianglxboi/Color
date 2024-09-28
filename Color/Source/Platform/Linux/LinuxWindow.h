#pragma once

#include "Platform/Generic/GenericWindow.h"

namespace Color
{
	class LinuxWindow : public GenericWindow
	{
	public:
		LinuxWindow(const WindowProps& props);
	};
}
