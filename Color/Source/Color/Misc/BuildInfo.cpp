#include "ColorPCH.h"
#include "BuildInfo.h"

namespace Color
{
	const char* BuildConfigToString(BuildConfig config)
	{
		switch (config)
		{
		case BuildConfig::Development: return "Development";
		case BuildConfig::Preview:     return "Preview";
		case BuildConfig::Shipping:    return "Shipping";
		}

		// TODO: unreachable code block
		return nullptr;
	}

	const char* PlatformToString(Platforms platform)
	{
		switch (platform)
		{
		case Platforms::Windows: return "Windows";
		case Platforms::Linux:   return "Linux";
		}

		// TODO: unreachable code block
		return nullptr;
	}

	const char* PlatformStabilityToString(PlatformStability stability)
	{
		switch (stability)
		{
		case PlatformStability::Stable:       return "Stable";
		case PlatformStability::Experimental: return "Experimental";
		}

		// TODO: unreachable code block
		return nullptr;
	}

	const char* PlatformArchitectureToString(PlatformArchitecture architecture)
	{
		switch (architecture)
		{
		case PlatformArchitecture::x64: return "x64";
		}

		// TODO: unreachable code block
		return nullptr;
	}

	const char* GetCompilerName(Compilers compiler)
	{
		switch (compiler)
		{
		case Compilers::MSVC:  return "Microsoft Visual C++ Compiler";
		case Compilers::Clang: return "Clang++";
		case Compilers::GCC:   return "GNU C++ Compiler";
		}

		// TODO: unreachable code block
		return nullptr;
	}

	const char* GetCompilerAbbreviation(Compilers compiler)
	{
		switch (compiler)
		{
		case Compilers::MSVC:  return "MSVC";
		case Compilers::Clang: return "Clang";
		case Compilers::GCC:   return "GCC";
		}

		// TODO: unreachable code block
		return nullptr;
	}
}
