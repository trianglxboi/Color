#include "ColorPCH.h"
#include "Renderer.h"

#include "Renderer/RenderCommand.h"

namespace Color
{
	void Renderer::Init()
	{
		RenderCommand::InitInstRendererAPI();
		CL_CORE_INFO("Initialized RendererAPI instance, current GraphicsAPI is '{}'.", GraphicsAPIToString(RendererAPI::GetGraphicsAPI()));

		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(x, y, width, height);
	}
}
