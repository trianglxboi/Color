#pragma once

#include "Core/Base.h"

namespace Color
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;

		virtual void SetData(const void* data, size_t size, size_t offset = 0) = 0;

		static Ref<UniformBuffer> New(size_t size, size_t binding);
	};
}
