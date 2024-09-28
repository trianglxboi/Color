#include "ColorPCH.h"
#include "GraphicsContext.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Color
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RendererAPI::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLContext>((GLFWwindow*) window);
		}

		unreachable();
		return false;
	}
}
