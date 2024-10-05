#include "ColorPCH.h"
#include "Buffer.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Color
{
	size_t SizeOfShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
		}

		unreachable();
		return 0;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const float* vertices, size_t size)
	{
		switch (RendererAPI::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLVertexBuffer>(vertices, size);
		}

		unreachable();
		return false;
	}

	Ref<VertexBuffer> VertexBuffer::Create(size_t size)
	{
		switch (RendererAPI::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLVertexBuffer>(size);
		}

		unreachable();
		return false;
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, size_t count)
	{
		switch (RendererAPI::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL: return CreateScope<OpenGLIndexBuffer>(indices, count);
		}

		unreachable();
		return false;
	}
}
