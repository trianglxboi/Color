#include "ColorPCH.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Color
{
	static void OpenGLMessageCallback
	(
		unsigned    src,
		unsigned    type,
		unsigned    id,
		unsigned    severity,
		int         length,
		const char* msg,
		const void* userParam
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         CL_CORE_FATAL(msg); break;
		case GL_DEBUG_SEVERITY_MEDIUM:       CL_CORE_ERROR(msg); break;
		case GL_DEBUG_SEVERITY_LOW:          CL_CORE_WARN(msg);  break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: CL_CORE_TRACE(msg); break;
		}

		unreachable();
	}

	OpenGLRendererAPI::OpenGLRendererAPI()
	{
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}

	void OpenGLRendererAPI::Init()
	{
	#ifdef CL_TEST_BUILD
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		glDebugMessageCallback(OpenGLMessageCallback, NULL);	
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::SetViewport(int32_t x, int32_t y, uint32_t width, uint32_t height)
	{
		checkf(width * height != 0, "Neither width nor the viewport of the viewport can be zero!");
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
