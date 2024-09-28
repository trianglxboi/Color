#include "ColorPCH.h"
#include "GenericWindow.h"

#include "EventSystem/MouseEvent.h"
#include "EventSystem/KeyEvent.h"
#include "EventSystem/AppEvent.h"

#include "Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

namespace Color
{
	static uint16_t s_WindowCount = 0;

	static void GLFWErrorCallback(int errorcode, const char* error)
	{
		CL_CORE_ERROR("GLFW Error ({}): {}", errorcode, error);
	}

	GenericWindow::GenericWindow(const WindowProps& props)
		: m_Data { m_Handle, props.Title, props.Width, props.Height, props.Resizable, props.Fullscreen, props.VSync }
	{
	}

	GenericWindow::~GenericWindow()
	{
		if (IsOpen())
		{
			Destroy();
		}
	}

	bool GenericWindow::Init()
	{
		if (IsOpen())
		{
			CL_CORE_WARN("Init called on an already open window, discarding request.");
			return false;
		}

		CL_CORE_INFO("Creating window '{}' ({}x{})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (s_WindowCount == 0 && !glfwInit())
		{
			const char* error;
			int errorcode = glfwGetError(&error);

			CL_CORE_ERROR("Failed to initialize with GLFW. Error ({}): {}", errorcode, error);
			return false;
		}
		glfwSetErrorCallback(GLFWErrorCallback);

		if (RendererAPI::GetGraphicsAPI() == GraphicsAPI::OpenGL)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			if constexpr (c_IsTestBuild)
			{
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			}
		}
		glfwWindowHint(GLFW_RESIZABLE, m_Data.Resizable);

		GLFWmonitor* monitor = m_Data.Fullscreen ? glfwGetPrimaryMonitor() : nullptr;
		m_Handle = glfwCreateWindow
		(
			m_Data.Width,
			m_Data.Height,
			m_Data.Title.c_str(),
			monitor,
			nullptr
		);

		if (!m_Handle)
		{
			CL_CORE_ERROR("Failed to create the GLFW window!");
			glfwTerminate();
			return false;
		}

		m_Context = GraphicsContext::Create(m_Handle);
		if (!m_Context->Init())
		{
			CL_CORE_ERROR("Failed to initialize the GraphicsContext!");
			glfwDestroyWindow(m_Handle); m_Handle = nullptr;
			glfwTerminate();
			return false;
		}
		glfwSetWindowUserPointer(m_Handle, &m_Data);

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			WindowClosedEvent e;
			data.BroadcastEvent(e);

			data.HandleRef = nullptr;
		});
		
		glfwSetWindowFocusCallback(m_Handle, [](GLFWwindow* window, int focused)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			if (focused)
			{
				WindowFocusEvent e;
				data.BroadcastEvent(e);
			}
			else
			{
				WindowLostFocusEvent e;
				data.BroadcastEvent(e);
			}
		});

		glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			data.Width  = (uint32_t) width;
			data.Height = (uint32_t) height;

			WindowResizedEvent e(width, height);
			data.BroadcastEvent(e);
		});
		
		glfwSetWindowPosCallback(m_Handle, [](GLFWwindow* window, int xpos, int ypos)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			WindowMovedEvent e(xpos, ypos);
			data.BroadcastEvent(e);
		});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent e((KeyCode) key, false);
				data.BroadcastEvent(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent e((KeyCode) key, true);
				data.BroadcastEvent(e);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e((KeyCode) key);
				data.BroadcastEvent(e);
				break;
			}
			}
		});
		
		glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			KeyTypedEvent e((KeyCode) keycode);
			data.BroadcastEvent(e);
		});
		
		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			if (action == GLFW_PRESS)
			{
				MouseButtonPressedEvent e((MouseCode) button);
				data.BroadcastEvent(e);
			}
			// Since mouse buttons only have two actions (press and release), if the action isn't press, it's 100% a release event.
			else
			{
				MouseButtonReleasedEvent e((MouseCode) button);
				data.BroadcastEvent(e);
			}
		});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float) xpos, (float) ypos);
			data.BroadcastEvent(e);
		});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xoff, double yoff)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float) xoff, (float) yoff);
			data.BroadcastEvent(e);
		});

		CL_CORE_TRACE("Window creation successful.");
		s_WindowCount++;
		return true;
	}

	bool GenericWindow::IsOpen() const
	{
		return m_Handle && !glfwWindowShouldClose(m_Handle);
	}

	void GenericWindow::Update()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	bool GenericWindow::Destroy()
	{
		if (!IsOpen())
		{
			return false;
		}

		glfwDestroyWindow(m_Handle);
		if (--s_WindowCount == 0)
		{
			CL_CORE_TRACE("No remanining windows left, terminating GLFW.");
			glfwTerminate();
		}

		return true;
	}

	void GenericWindow::RequestAttention()
	{
		if (!IsOpen())
		{
			return;
		}

		glfwRequestWindowAttention(m_Handle);
	}

	void GenericWindow::Focus()
	{
		if (!IsOpen())
		{
			return;
		}

		glfwFocusWindow(m_Handle);
	}

	bool GenericWindow::HasFocus() const
	{
		if (!IsOpen())
		{
			return false;
		}

		return glfwGetWindowAttrib(m_Handle, GLFW_FOCUSED);
	}

	void GenericWindow::SetTitle(std::string_view title)
	{
		m_Data.Title = title;

		if (IsOpen())
		{
			glfwSetWindowTitle(m_Handle, title.data());
		}
	}

	void GenericWindow::SetSize(const glm::uvec2& size)
	{
		SetSize(size.x, size.y);
	}

	void GenericWindow::SetSize(uint32_t width, uint32_t height)
	{
		if (IsOpen())
		{
			// m_Props data will update in glfwSizeCallback.
			glfwSetWindowSize(m_Handle, width, height);
		}
		else
		{
			m_Data.Width = width;
			m_Data.Height = height;
		}
	}

	void GenericWindow::SetWidth(uint32_t width)
	{
		SetSize(width, m_Data.Height);
	}

	void GenericWindow::SetHeight(uint32_t height)
	{
		SetSize(m_Data.Width, height);
	}

	void GenericWindow::SetVSync(bool vSync)
	{
		m_Data.VSync = vSync;

		if (IsOpen())
		{
			glfwSwapInterval(vSync ? 1 : 0);
		}
	}

	void GenericWindow::SetEventCallback(EventCallbackFn fn)
	{
		m_Data.EventCallback = fn;
	}
}
