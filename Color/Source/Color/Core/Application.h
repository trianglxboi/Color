#pragma once

#include "Core/Base.h"

#include <string>

namespace Color
{
	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDir;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification, const CommandLine& cmdline);
		virtual ~Application();

		void Run();
		void Quit();
		void Exit(int exitcode = 0);

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		const CommandLine& GetCmdline() const { return m_Cmdline; }

		bool IsRunning() const { return false; }

		static Application* Get() { return s_Instance; }
	private:
		void CleanUp();
	private:
		ApplicationSpecification m_Specification;
		CommandLine m_Cmdline;

		bool m_Running = false;
	private:
		inline static Application* s_Instance = nullptr;
	};

	Application* CreateApplication(const CommandLine& cmdline);
}
