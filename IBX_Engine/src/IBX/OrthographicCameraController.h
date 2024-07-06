#pragma once

#include "IBX/Renderer/OrthographicCamera.h"
#include "IBX/Core/Timestep.h"

#include "IBX/Events/ApplicationEvent.h"
#include "IBX/Events/MouseEvent.h"

namespace IBX_Engine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool enableRotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool m_EnableRotation;
			
		// Data used to construct this camera must be initialized first above
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}