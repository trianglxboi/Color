VULKAN_SDK = os.getenv("VULKAN_SDK")

if VULKAN_SDK == nil then
	print("VulkanSDK not installed.")
	exit(-1)
end

OutputDir = {}
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ProjectDir = {}
ProjectDir["Color"] = "%{wks.location}/Color"
ThirdPartyDir = "%{ProjectDir.Color}/ThirdParty"
ProjectDir["Sandbox"] = "%{wks.location}/Sandbox"
ProjectDir["yamlcpp"] = "%{ThirdPartyDir}/yaml-cpp"
ProjectDir["GLFW"] = "%{ThirdPartyDir}/GLFW"
ProjectDir["Glad"] = "%{ThirdPartyDir}/Glad"

IncludeDir = {}
IncludeDir["Color"] = "%{ProjectDir.Color}/Source/Color"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
IncludeDir["fmt"] = "%{ThirdPartyDir}/fmt/include"
IncludeDir["spdlog"] = "%{ThirdPartyDir}/spdlog/include"
IncludeDir["glm"] = "%{ThirdPartyDir}/glm"
IncludeDir["yamlcpp"] = "%{ProjectDir.yamlcpp}/include"
IncludeDir["GLFW"] = "%{ProjectDir.GLFW}/include"
IncludeDir["Glad"] = "%{ProjectDir.Glad}/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

SourceDir = {}
SourceDir["Color"] = "%{ProjectDir.Color}/Source"
SourceDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
SourceDir["yamlcpp"] = "%{ProjectDir.yamlcpp}/src"
SourceDir["GLFW"] = "%{ProjectDir.GLFW}/src"
SourceDir["Glad"] = "%{ProjectDir.Glad}/src"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
Library["SPIRV_Tools_Release"] = "%{LibraryDir.VulkanSDK}/SPIRV-Tools.lib"
