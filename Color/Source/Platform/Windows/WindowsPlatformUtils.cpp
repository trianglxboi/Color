#include "ColorPCH.h"
#include "WindowsPlatformUtils.h"

namespace Color
{
	void WindowsPlatformUtils::Exit_(int exitcode)
	{
		ExitProcess(exitcode);
	}
}
