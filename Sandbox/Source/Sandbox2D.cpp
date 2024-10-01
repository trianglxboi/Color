#include "ColorPCH.h"
#include "Sandbox2D.h"

#include "Asset/EditorAssetManager.h"
#include "Project/Project.h"

#include "Scene/SceneSerializer.h"
#include "Scene/Components.h"

#include "Utils/FileSystem.h"

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
		m_Scene = std::static_pointer_cast<Color::Scene>(Color::ActiveProject::GetEditorAssetManager()->GetAsset(1841035918487706163).lock());
	}

	void Sandbox2D::OnEvent(Color::Event& e)
	{
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
