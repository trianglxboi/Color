#pragma once

#include "Renderer/RendererAPI.h"

namespace Color
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		virtual ~OpenGLRendererAPI() override;

		virtual void Init() override;
		virtual void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(float r, float g, float b, float a) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetLineWidth(float width) override;
		virtual void Clear() override;
	};
}
