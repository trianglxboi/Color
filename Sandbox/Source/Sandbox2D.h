#pragma once

#include "Core/Layer.h"
#include "Scene/Scene.h"

namespace Sandbox
{
	class Sandbox2D : public Color::Layer
	{
	public:
		Sandbox2D();
		virtual ~Sandbox2D() override;

		virtual void OnAttach() override;
		virtual void OnEvent(Color::Event& e) override;
		virtual void OnUpdate(Color::Timestep ts) override;
		virtual void OnRender() override;
		virtual void OnDetach() override;
	private:
		Color::Ref<Color::Scene> m_Scene;
	};
}
