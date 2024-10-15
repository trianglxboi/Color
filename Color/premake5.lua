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

		"%{IncludeDir.fmt}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.yamlcpp}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.VulkanSDK}"
	}

	links
	{
		"yaml-cpp",
		"GLFW",
		"Glad"
	}

	defines
	{
		"YAML_CPP_STATIC_DEFINE",
		"GLFW_INCLUDE_NONE"
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
			"CL_STABLE_PLATFORM",

			"_CRT_SECURE_NO_WARNINGS",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
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
		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_PREVIEW",
			"CL_TEST_BUILD"
		}
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_SHIPPING"
		}
		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
