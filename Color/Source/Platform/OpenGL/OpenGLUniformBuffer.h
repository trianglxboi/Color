#pragma once

#include "Renderer/UniformBuffer.h"

namespace Color
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(size_t size, size_t binding);
		virtual ~OpenGLUniformBuffer() override;

		virtual void SetData(const void* data, size_t size, size_t offset = 0) override;

		uint32_t m_RendererID = 0;
	};
}
