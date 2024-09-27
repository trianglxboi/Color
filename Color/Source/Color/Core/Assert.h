#pragma once

#include "Core/Log.h"
#include "Misc/MiscDefines.h"

#ifdef CL_PLATFORM_WINDOWS
	#define CL_DEBUGBREAK_BASE() __debugbreak()
#elif defined CL_PLATFORM_LINUX
	#include <signal.h>
	#define CL_DEBUGBREAK_BASE() raise(SIGTRAP)
#endif

#define CL_BASE_ASSERT(type, expr) if (!(expr)) { CL_ASSERT_ERROR(type " failed! Expression '" #expr "' evaluated to false."); CL_DEBUGBREAK_BASE(); }
#define CL_BASE_ASSERTA(type, expr) if (!(expr)) { CL_ASSERT_ERROR(type " failed in file '" __FILE__ "' at line " CL_STRINGIFY(__LINE__) "! Expression '" #expr "' evaluated to false."); CL_DEBUGBREAK_BASE(); }
#define CL_BASE_ASSERTF(type, expr, ...) if (!(expr)) { CL_ASSERT_ERROR(type " failed in file '" __FILE__ "' at line " CL_STRINGIFY(__LINE__) "! Expression '" #expr "' evaluated to false. " __VA_ARGS__); CL_DEBUGBREAK_BASE(); }
#define CL_BASE_UNREACHABLE() { CL_ASSERT_ERROR("Unreachable point in file '" __FILE__ "' at line " CL_STRINGIFY(__LINE__) " was hit!"); CL_DEBUGBREAK_BASE(); }

#define verify(expr)         CL_BASE_ASSERT("Check", expr)
#define verifya(expr)        CL_BASE_ASSERTA("Check", expr)
#define verifyf(expr, ...)   CL_BASE_ASSERTF("Check", expr, __VA_ARGS__)
#define always_unreachable() CL_BASE_UNREACHABLE()

#ifdef CL_TEST_BUILD

#define CL_DEBUGBREAK     CL_DEBUGBREAK_BASE

#define check(expr)       CL_BASE_ASSERT("Check", expr)
#define checka(expr)      CL_BASE_ASSERTA("Check", expr)
#define checkf(expr, ...) CL_BASE_ASSERTF("Check", expr, __VA_ARGS__)
#define unreachable()     CL_BASE_UNREACHABLE()

#else

#define CL_DEBUGBREAK

#define check(expr)
#define checka(expr)
#define checkf(expr, ...)
#define unreachable()

#endif
