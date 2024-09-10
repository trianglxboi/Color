#include "ColorPCH.h"
#include "Application.h"

namespace Color
{
	Application::Application(const ApplicationSpecification& specification, const CommandLine& cmdline)
		: m_Specification(specification), m_Cmdline(cmdline)
	{
		// TODO: Assert !s_Instance
		s_Instance = this;

		// TODO: Handle working directory
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
			// TODO: warn
			return;
		}

		m_Running = true;

		while (m_Running)
		{

		}

		CleanUp();
	}

	void Application::CleanUp()
	{
	}

	void Application::Quit()
	{
		if (!m_Running)
		{
			// TODO: warn
			return;
		}

		m_Running = false;
	}

	void Application::Exit(int exitcode)
	{
		// TODO: Use PlatformUtils when we have one.
		std::exit(exitcode);
	}
}
