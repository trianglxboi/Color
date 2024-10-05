#include "ColorPCH.h"
#include "Sandbox2D.h"

#include "Asset/EditorAssetManager.h"
#include "Project/Project.h"

#include "Scene/SceneSerializer.h"
#include "Scene/Components.h"

#include "Utils/FileSystem.h"

// temporary renderer stuff for testing purposes
#include "Renderer/VertexArray.h"
#include "Renderer/RenderCommand.h"

namespace Sandbox
{
	Color::Ref<Color::VertexArray> g_VertexArray;
	Color::Ref<Color::VertexBuffer> g_VertexBuffer;
	Color::Ref<Color::IndexBuffer> g_IndexBuffer;

	Sandbox2D::Sandbox2D()
		: Color::Layer("Sandbox2D")
	{
	}

	Sandbox2D::~Sandbox2D()
	{
	}

	void Sandbox2D::OnAttach()
	{
		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		g_VertexArray = Color::VertexArray::Create();
		g_VertexArray->Bind();

		g_VertexBuffer = Color::VertexBuffer::Create(vertices, sizeof(vertices));
		g_VertexBuffer->SetLayout({
			{ Color::ShaderDataType::Float3, "a_Position" }
		});
		g_VertexBuffer->Bind();

		g_IndexBuffer = Color::IndexBuffer::Create(indices, 6);
		g_IndexBuffer->Bind();

		g_VertexArray->AddVertexBuffer(g_VertexBuffer);
		g_VertexArray->SetIndexBuffer(g_IndexBuffer);

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
		Color::RenderCommand::Clear();

		// Will not draw as of now on GPUs that don't have a default shader.
		Color::RenderCommand::DrawIndexed(g_VertexArray);
	}

	void Sandbox2D::OnDetach()
	{
		m_Scene->StopRuntime();
	}
}
