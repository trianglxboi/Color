#include "ColorPCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Color
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		checkf(window, "Window handle is null!");
	}

	bool OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			CL_CORE_ERROR("Failed to initialize Glad! Loading prodecure of OpenGL functions have failed.");
			return false;
		}

		CL_CORE_INFO("OpenGL Info:");
		CL_CORE_INFO("  Renderer     -> {}", (const char*) glGetString(GL_RENDERER));
		CL_CORE_INFO("  Vendor       -> {}", (const char*) glGetString(GL_VENDOR));
		CL_CORE_INFO("  Version      -> {}", (const char*) glGetString(GL_VERSION));
		CL_CORE_INFO("  GLSL Version -> {}", (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (GLVersion.major < 4 || (GLVersion.major == 4 && GLVersion.minor < 5))
		{
			CL_CORE_ERROR
			(
				"Color Engine requires a GPU with at least OpenGL 4.5 functionality! Your current renderer (video card/GPU) supports only up to {}.{}\n"
				"Try updating your graphics drivers or switching to another renderer if possible.",
				GLVersion.major, GLVersion.minor
			);

			return false;
		}

		return true;
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
