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

SourceDir = {}
SourceDir["Color"] = "%{ProjectDir.Color}/Source"
SourceDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
SourceDir["yamlcpp"] = "%{ProjectDir.yamlcpp}/src"
SourceDir["GLFW"] = "%{ProjectDir.GLFW}/src"
SourceDir["Glad"] = "%{ProjectDir.Glad}/src"
