#pragma once

#include "Misc/MiscDefines.h"

namespace Color
{
	enum class BuildConfig
	{
		Development,
		Preview,
		Shipping
	};

	#ifdef CL_DEVELOPMENT
		inline constexpr BuildConfig c_BuildConfig = BuildConfig::Development;
	#elif defined CL_PREVIEW
		inline constexpr BuildConfig c_BuildConfig = BuildConfig::Preview;
	#elif defined CL_SHIPPING
		inline constexpr BuildConfig c_BuildConfig = BuildConfig::Shipping;
	#else
		#error Unknowm build configuration!
	#endif

	#ifdef CL_TEST_BUILD
		inline constexpr bool c_IsTestBuild = true;
	#else
		inline constexpr bool c_IsTestBuild = false;
	#endif

	enum class Platforms
	{
		Windows,
		Linux
	};

	enum class PlatformStability
	{
		Stable,
		Experimental
	};

	enum class PlatformArchitecture
	{
		x64
	};

	const char* PlatformToString(Platforms platform);
	const char* PlatformStabilityToString(PlatformStability stability);
	const char* PlatformArchitectureToString(PlatformArchitecture architecture);
	
	#ifdef CL_PLATFORM_WINDOWS
		inline constexpr Platforms c_Platform = Platforms::Windows;
		#define CL_PLATFORM_RAW_NAME Windows
	#elif defined CL_PLATFORM_LINUX
		inline constexpr Platforms c_Platform = Platforms::Linux;
		#define CL_PLATFORM_RAW_NAME Linux
	#else
		#error Unknown platform! Color only supports Windows and Linux as of now!
	#endif

	#define CL_ConcatWithPlatformName(x) CL_CONCAT(CL_PLATFORM_RAW_NAME, x)
	#define CL_PLATFORM_NAME CL_STRINGIFY(CL_PLATFORM_RAW_NAME)

	#ifdef CL_ARCH_X64
		inline constexpr PlatformArchitecture c_PlatformArchitecture = PlatformArchitecture::x64;
	#else
		#error Unknown platform architecture! Color only supports x64 as of now.
	#endif

	#ifdef CL_BITS_64
		inline constexpr unsigned char c_PlatformBitness = 64;
	#else
		#error Unknown platform bitness! Color only supports bitness of 64.
	#endif

	#ifdef CL_STABLE_PLATFORM
		inline constexpr PlatformStability c_PlatformStability = PlatformStability::Stable;
	#elif defined CL_EXPERIMENTAL_PLATFORM
		inline constexpr PlatformStability c_PlatformStability = PlatformStability::Experimental;
	#else
		#error Unknown platform stability!
	#endif

	enum class Compilers
	{
		MSVC,
		Clang,
		GCC
	};

	const char* GetCompilerName(Compilers compiler);
	const char* GetCompilerAbbreviation(Compilers compiler);

	#ifdef __clang__
		inline constexpr Compilers c_Compiler = Compilers::Clang;
	#elif defined _MSC_VER
		inline constexpr Compilers c_Compiler = Compilers::MSVC;
	#elif defined __GNUC__
		inline constexpr Compilers c_Compiler = Compilers::GCC;
	#endif

}
