project "Sandbox"
	language "C++"
	cppdialect "C++17"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir    "%{OutputDir.Intermediates}/%{prj.name}"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.Color}",
		"%{SourceDir.Color}",
		"Source",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Color"
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

	filter "system:linux"
		defines
		{
			"CL_PLATFORM_LINUX",
			"CL_EXPERIMENTAL_PLATFORM"
		}
		
	filter "configurations:Development"
		kind "ConsoleApp"
		runtime "Debug"
		symbols "On"
		defines
		{
			"CL_DEVELOPMENT",
			"CL_TEST_BUILD"
		}

	filter "configurations:Preview"
		kind "ConsoleApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_PREVIEW",
			"CL_TEST_BUILD"
		}

	filter "configurations:Shipping"
		kind "WindowedApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"CL_SHIPPING"
		}
