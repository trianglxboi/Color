#include "SandboxApp.h"

// >>> Entry Point Declared & Implemented Here <<< //
#include "Core/EntryPoint.h"

#include "Core/Assert.h"
#include "Misc/Random.h"

namespace Sandbox
{
	SandboxApp::SandboxApp(const Color::ApplicationSpecification& specification, const Color::CommandLine& cmdline)
		: Color::Application(specification, cmdline)
	{
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
