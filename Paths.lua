OutputDir = {}
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ProjectDir = {}
ProjectDir["Color"] = "%{wks.location}/Color"
ProjectDir["Sandbox"] = "%{wks.location}/Sandbox"

ThirdPartyDir = "%{ProjectDir.Color}/ThirdParty"

IncludeDir = {}
IncludeDir["Color"] = "%{ProjectDir.Color}/Source/Color"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
IncludeDir["spdlog"] = "%{ThirdPartyDir}/spdlog/include"
IncludeDir["glm"] = "%{ThirdPartyDir}/glm"

SourceDir = {}
SourceDir["Color"] = "%{ProjectDir.Color}/Source"
SourceDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
