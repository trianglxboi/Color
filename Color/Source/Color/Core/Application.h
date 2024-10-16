#pragma once

#include "Core/LayerStack.h"
#include "Core/Window.h"

#include "EventSystem/AppEvent.h"
#include "EventSystem/Event.h"

namespace Color
{
	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDir;

		WindowProps MainWindowProps;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification, const CommandLine& cmdline);
		virtual ~Application();

		void Run();
		void Quit();
		void Exit(int exitcode = 0);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer, bool disown = false);
		void PopOverlay(Layer* overlay, bool disown = false);

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		const CommandLine& GetCmdline() const { return m_Cmdline; }

		Window* GetMainWindow() const { return m_MainWindow.get(); }
		bool IsRunning() const { return false; }

		static Application* Get() { return s_Instance; }
	private:
		void CleanUp();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowClosedEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);
	private:
		ApplicationSpecification m_Specification;
		CommandLine m_Cmdline;

		Scope<Window> m_MainWindow;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
		bool m_Running = false;
	private:
		inline static Application* s_Instance = nullptr;
	};

	Application* CreateApplication(const CommandLine& cmdline);
}
