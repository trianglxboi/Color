#include "SandboxApp.h"

// >>> Entry Point Declared & Implemented Here <<< //
#include "Core/EntryPoint.h"
#include "Project/Project.h"

#include "Sandbox2D.h"

namespace Sandbox
{
	SandboxApp::SandboxApp(const Color::ApplicationSpecification& specification, const Color::CommandLine& cmdline)
		: Color::Application(specification, cmdline)
	{
		checkf(Color::Project::Load("Sandbox.clprj"), "Failed to load Sandbox project file!");

		PushLayer(new Sandbox2D());
	}

	SandboxApp::~SandboxApp()
	{
	}
}

Color::Application* Color::CreateApplication(const Color::CommandLine& cmdline)
{
	ApplicationSpecification specification;
	specification.Name = "Sandbox";
	specification.MainWindowProps.Title = specification.Name;

	return new Sandbox::SandboxApp(specification, cmdline);
}
