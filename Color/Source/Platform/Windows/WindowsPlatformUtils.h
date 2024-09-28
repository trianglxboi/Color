#pragma once

#include "Platform/Generic/GenericPlatformUtils.h"

namespace Color
{
	class WindowsPlatformUtils : public GenericPlatformUtils
	{
	protected:
		virtual void Exit_(int exitcode) override;
	};
}
