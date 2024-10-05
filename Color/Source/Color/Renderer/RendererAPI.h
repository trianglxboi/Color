#pragma once

#include "Renderer/VertexArray.h"

namespace Color
{
	enum class GraphicsAPI
	{
		OpenGL
	};

	std::string_view GraphicsAPIToString(GraphicsAPI api);

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetLineWidth(float width) = 0;
		virtual void Clear() = 0;

		virtual void DrawLines(const Ref<VertexArray>& vertexArray, size_t vertexCount) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, size_t indexCount = 0) = 0;

		static Scope<RendererAPI> Create();
		static GraphicsAPI GetGraphicsAPI() { return s_API; }
	private:
		inline static GraphicsAPI s_API = GraphicsAPI::OpenGL;
	};
}
