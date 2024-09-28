include "Paths.lua"

workspace "Color"
	architecture "x64" -- x86 will never be supported. ARM64 might get support in future, we're currently focused on x64.
	configurations
	{
		"Development",
		"Preview",
		"Shipping"
	}
	startproject "Sandbox"

group "ThirdParty"
	include "Color/ThirdParty/yaml-cpp"
	include "Color/ThirdParty/GLFW"
	include "Color/ThirdParty/Glad"
group ""

include "Color"
include "Sandbox"
