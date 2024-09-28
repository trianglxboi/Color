#include "ColorPCH.h"
#include "PlatformUtils.h"

#include "Platform/Windows/WindowsPlatformUtils.h"
#include "Platform/Linux/LinuxPlatformUtils.h"

namespace Color
{
	Scope<PlatformUtils> PlatformUtils::s_Instance = CreateScope<CL_ConcatWithPlatformName(PlatformUtils)>();
}
