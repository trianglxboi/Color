#include "ColorPCH.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Color
{
	std::string_view GraphicsAPIToString(GraphicsAPI api)
	{
		switch (api)
		{
		case GraphicsAPI::OpenGL: return "OpenGL";
		}

		unreachable();
		return "";
	}

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		unreachable();
		return false;
	}
}
