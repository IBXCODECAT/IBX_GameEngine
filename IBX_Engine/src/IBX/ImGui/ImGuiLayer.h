#pragma once

#include "IBX/Core/Layers/Layer.h"

#include "IBX/Events/ApplicationEvent.h"
#include "IBX/Events/KeyEvent.h"
#include "IBX/Events/MouseEvent.h"

namespace IBX_Engine
{
	class IBX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		/// <summary>
		/// Begin a new imgui frame
		/// </summary>
		void BeginNewFrame();

		/// <summary>
		/// End the current imgui frame
		/// </summary>
		void EndCurrentFrame();
	private:
		float m_Time = 0.0f;
	};
}