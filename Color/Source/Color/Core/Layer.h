#pragma once

#include "EventSystem/Event.h"
#include "Misc/Timestep.h"

namespace Color
{
	class Layer
	{
	public:
		Layer() = delete;
		Layer(std::string_view name);
		virtual ~Layer() = default;

		virtual void OnAttach() { }
		virtual void OnEvent(Event& e) { }
		virtual void OnUpdate(Timestep ts) { }
		virtual void OnRender() { }
		virtual void OnDetach() { }

		const std::string& GetLayerName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
