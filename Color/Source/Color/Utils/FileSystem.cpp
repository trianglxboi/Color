#include "ColorPCH.h"
#include "FileSystem.h"

#include "Platform/Windows/WindowsFileSystem.h"

namespace Color
{
	Scope<FileSystem> FileSystem::s_NativeInstance = CreateScope<CL_ConcatWithPlatformName(FileSystem)>();
}
