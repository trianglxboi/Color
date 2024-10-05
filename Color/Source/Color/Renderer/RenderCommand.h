#pragma once

#include "Renderer/RendererAPI.h"

namespace Color
{
	// A wrapper around RendererAPI functions. Also contains the RendererAPI singleton instance.
	class RenderCommand
	{
	public:
		static void InitInstRendererAPI();

		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(float r, float g, float b, float a)
		{
			s_RendererAPI->SetClearColor(r, g, b, a);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void SetLineWidth(float width)
		{
			s_RendererAPI->SetLineWidth(width);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawLines(const Ref<VertexArray>& vertexArray, size_t vertexCount)
		{
			s_RendererAPI->DrawLines(vertexArray, vertexCount);
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, size_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}
	private:
		inline static Scope<RendererAPI> s_RendererAPI = nullptr;
	};
}
