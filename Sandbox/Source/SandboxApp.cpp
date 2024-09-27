#include "SandboxApp.h"

// >>> Entry Point Declared & Implemented Here <<< //
#include "Core/EntryPoint.h"

#include "Sandbox2D.h"

namespace Sandbox
{
	SandboxApp::SandboxApp(const Color::ApplicationSpecification& specification, const Color::CommandLine& cmdline)
		: Color::Application(specification, cmdline)
	{
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

	return new Sandbox::SandboxApp(specification, cmdline);
}
