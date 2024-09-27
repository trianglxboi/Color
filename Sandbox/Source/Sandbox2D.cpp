#include "ColorPCH.h"
#include "Sandbox2D.h"

namespace Sandbox
{
	Sandbox2D::Sandbox2D()
		: Color::Layer("Sandbox2D")
	{
	}

	Sandbox2D::~Sandbox2D()
	{
	}

	void Sandbox2D::OnAttach()
	{
		m_Scene = Color::CreateRef<Color::Scene>();
		m_Scene->StartRuntime();
	}

	void Sandbox2D::OnEvent(Color::Event& e)
	{
		CL_ERROR("Sandbox2D::OnEvent - {}", e);
	}

	void Sandbox2D::OnUpdate(Color::Timestep ts)
	{
		m_Scene->UpdateRuntime(ts);
	}

	void Sandbox2D::OnRender()
	{
	}

	void Sandbox2D::OnDetach()
	{
		m_Scene->StopRuntime();
	}
}
