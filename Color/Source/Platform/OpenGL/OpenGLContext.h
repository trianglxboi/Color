#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Color
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual bool Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window = nullptr;
	};
}
