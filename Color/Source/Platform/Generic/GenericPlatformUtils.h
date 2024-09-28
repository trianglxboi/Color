#pragma once

#include "Utils/PlatformUtils.h"

namespace Color
{
	class GenericPlatformUtils : public PlatformUtils
	{
	protected:
		virtual float GetTime_() const override;
	};
}
