#include "ColorPCH.h"
#include "VertexArray.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Color
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLVertexArray>();
		}

		unreachable();
		return false;
	}
}
