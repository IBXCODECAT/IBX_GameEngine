#include "ibxpch.h";
#include "LayerStack.h"

namespace IBX_Engine
{
	// LayerStack is owned by the application
	// This means that layers live for the entire lifetime of the application
	// and are later deallocated when the application is closed
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) delete layer;
	}

	// Add a layer to the layer stack (Layers are added in the order they are pushed) at begin + index
	void LayerStack::PushLayer(Layer* layer)
	{
		IBX_CORE_DEBUG("Pushing layer: {0}", layer->GetName());
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	// Add an overlay to the layer stack (Overlays are added after the layers)
	void LayerStack::PushOverlay(Layer* overlay)
	{
		IBX_CORE_DEBUG("Pushing overlay: {0}", overlay->GetName());
		m_Layers.emplace_back(overlay);
	}

	// Remove a layer from the layer stack, this does not delete the layer but it does move the insert index back
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	// Remove an overlay from the layer stack, this does not delete the overlay
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}