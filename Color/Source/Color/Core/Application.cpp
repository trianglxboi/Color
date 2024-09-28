#include "ColorPCH.h"
#include "Application.h"

#include "Renderer/Renderer.h"

#include "Utils/PlatformUtils.h"
#include "Utils/FileSystem.h"

namespace Color
{
	Application::Application(const ApplicationSpecification& specification, const CommandLine& cmdline)
		: m_Specification(specification), m_Cmdline(cmdline)
	{
		checkf(!s_Instance, "An application instance already exists!");
		s_Instance = this;

		Log::Init();
		CL_CORE_INFO("Initialized logging.");

		CL_CORE_INFO("Engine Build Info:");
		CL_CORE_INFO("  Build Configuration -> {} (test? = {})", BuildConfigToString(c_BuildConfig), c_IsTestBuild);
		CL_CORE_INFO("  Platform            -> {}-{} ({})", PlatformToString(c_Platform), PlatformArchitectureToString(c_PlatformArchitecture), PlatformStabilityToString(c_PlatformStability));
		CL_CORE_INFO("  Compiler Info:");
		CL_CORE_INFO("    Compiler         -> {} ({})", GetCompilerName(c_Compiler), GetCompilerAbbreviation(c_Compiler));
		CL_CORE_INFO("    Compilation Date -> {}", __DATE__);
		CL_CORE_INFO("    Compilation Time -> {}", __TIME__);

		if (!m_Specification.WorkingDir.empty())
		{
			std::string initialWdir = FileSystem::GetWorkingDirectory();
			std::string specWdir = FileSystem::Abs(m_Specification.WorkingDir);

			if (initialWdir != specWdir)
			{
				if (FileSystem::IsDirectory(specWdir))
				{
					CL_CORE_WARN("Application specification requested a different working directory, changing...");
					FileSystem::SetWorkingDirectory(specWdir);
					CL_CORE_INFO("Changed the working directory '{}' -> '{}'", initialWdir, specWdir);
				}
				else
				{
					CL_CORE_ERROR("Application specification specified a custom working directory '{}', but the said path either doesn't exist or is not a directory.", m_Specification.WorkingDir);
				}
			}
		}

		m_MainWindow = Window::Create(m_Specification.MainWindowProps);
		if (!m_MainWindow || !m_MainWindow->Init())
		{
			CL_CORE_FATAL("Application main window creation failure!");
		}
		m_MainWindow->SetEventCallback(CL_BIND_METHOD(OnEvent));
		CL_CORE_INFO("Main window created successfully.");

		
		Renderer::Init();
		CL_CORE_INFO("Initialized rendering engine.");
	}

	Application::~Application()
	{
		if (this == s_Instance)
		{
			s_Instance = nullptr;
		}
	}

	void Application::Run()
	{
		if (m_Running)
		{
			CL_CORE_WARN("Tried to call Run() on an already running Application. Discarding request.");
			return;
		}

		m_Running = true;

		while (m_Running)
		{
			float time = PlatformUtils::GetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(ts);
			}

			for (Layer* layer : m_LayerStack)
			{
				layer->OnRender();
			}

			m_MainWindow->Update();
		}

		CleanUp();
	}

	void Application::CleanUp()
	{
		// Delete leftover layers
		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}
		m_LayerStack = LayerStack{}; // Will deconstruct old layer stack (so the vector gets cleared)

		Renderer::Shutdown();
		m_MainWindow->Destroy();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(CL_BIND_METHOD(OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(CL_BIND_METHOD(OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			if (e.Handled)
			{
				break;
			}

			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		Quit();
		return true;
	}

	bool Application::OnWindowResize(WindowResizedEvent& e)
	{
		Renderer::SetViewport(0, 0, e.GetSizeX(), e.GetSizeY());
		return false;
	}

	void Application::Quit()
	{
		if (!m_Running)
		{
			CL_CORE_WARN("Tried to call Quit() on an already non-running Application. Discarding request.");
			return;
		}

		m_Running = false;
	}

	void Application::Exit(int exitcode)
	{
		// TODO: Use PlatformUtils when we have one.
		std::exit(exitcode);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer, bool disown)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay, bool disown)
	{
		m_LayerStack.PopOverlay(overlay);
	}
}
