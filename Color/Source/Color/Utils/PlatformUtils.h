#pragma once

#include "Core/Base.h"

namespace Color
{
	class PlatformUtils
	{
	public:
		virtual ~PlatformUtils() = default;
	public:
		static float GetTime() { return s_Instance->GetTime_(); }
		static void Exit(int exitcode) { return s_Instance->Exit_(exitcode); }
	protected:
		virtual float GetTime_() const = 0;
		virtual void Exit_(int exitcode) = 0;
	private:
		static Scope<PlatformUtils> s_Instance;
	};
}
