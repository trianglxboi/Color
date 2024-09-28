#pragma once

namespace Color
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height);
	};
}
