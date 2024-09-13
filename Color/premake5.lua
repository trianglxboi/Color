project "Color"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir    "%{OutputDir.Intermediates}/%{prj.name}"

	pchheader "ColorPCH.h"
	pchsource "Source/ColorPCH.cpp"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"Source",
		"Source/Color",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	filter "architecture:x64"
		defines
		{
			"CL_BITS_64",
			"CL_ARCH_X64"
		}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"CL_PLATFORM_WINDOWS",
			"CL_STABLE_PLATFORM"
		}
		removefiles
		{
			"Source/Platform/Linux/**.cpp"
		}
		links
		{
			"Shlwapi.lib"
		}

	filter "system:linux"
		defines
		{
			"CL_PLATFORM_LINUX",
			"CL_EXPERIMENTAL_PLATFORM"
		}

	filter "configurations:Development"
		runtime "Debug"
		symbols "On"
		defines
		{
			"CL_DEVELOPMENT",
			"CL_TEST_BUILD"
		}

	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_PREVIEW",
			"CL_TEST_BUILD"
		}

	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_SHIPPING"
		}
