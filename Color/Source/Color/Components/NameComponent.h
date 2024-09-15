#pragma once

#include "Core/Base.h"

#include <string_view>
#include <string>

namespace Color
{
	struct NameComponent
	{
		CL_COMPONENT_ID("NameComponent");

		std::string Name;

		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent& operator=(const NameComponent&) = default;

		NameComponent(std::string_view name)
			: Name(name) { }
	};
}
