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

		unreachable();
		return nullptr;
	}

	const char* PlatformToString(Platforms platform)
	{
		switch (platform)
		{
		case Platforms::Windows: return "Windows";
		case Platforms::Linux:   return "Linux";
		}

		unreachable();
		return nullptr;
	}

	const char* PlatformStabilityToString(PlatformStability stability)
	{
		switch (stability)
		{
		case PlatformStability::Stable:       return "Stable";
		case PlatformStability::Experimental: return "Experimental";
		}

		unreachable();
		return nullptr;
	}

	const char* PlatformArchitectureToString(PlatformArchitecture architecture)
	{
		switch (architecture)
		{
		case PlatformArchitecture::x64: return "x64";
		}

		unreachable();
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

		unreachable();
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

		unreachable();
		return nullptr;
	}
}
