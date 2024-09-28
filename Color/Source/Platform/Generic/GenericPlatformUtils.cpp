#include "ColorPCH.h"
#include "GenericPlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Color
{
	float GenericPlatformUtils::GetTime_() const
	{
		return (float) glfwGetTime();
	}
}
