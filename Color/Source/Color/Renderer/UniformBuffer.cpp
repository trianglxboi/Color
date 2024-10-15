#include "ColorPCH.h"
#include "UniformBuffer.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Color
{
	Ref<UniformBuffer> UniformBuffer::New(size_t size, size_t binding)
	{
		switch (RendererAPI::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLUniformBuffer>(size, binding);
		}

		unreachable();
		return false;
	}
}
