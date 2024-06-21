#pragma once

#include "IBX/Layers/Layer.h"

namespace IBX_Engine
{
	class IBX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& e);

	private:
		float m_Time = 0.0f;
	};
}