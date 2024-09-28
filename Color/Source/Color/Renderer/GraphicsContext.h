#pragma once

#include "Core/Base.h"

namespace Color
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual bool Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};
}
