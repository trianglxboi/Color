#pragma once

#include "Core/Layer.h"

#include <vector>

namespace Color
{
	// NOTE: Non-owning, this object won't take ownership of the layers it's going to contain.
	// However, in the specific case with the Application, the Application itself takes ownership of the layers of the layer stackç
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_iterator cbegin() const { return m_Layers.cbegin(); }
		std::vector<Layer*>::const_iterator cend() const { return m_Layers.cend(); }

		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
		std::vector<Layer*>::const_reverse_iterator crbegin() const { return m_Layers.crbegin(); }
		std::vector<Layer*>::const_reverse_iterator crend() const { return m_Layers.crend(); }

		const std::vector<Layer*>& GetLayers() const { return m_Layers; }
	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayersEnd = 0;
	};
}
