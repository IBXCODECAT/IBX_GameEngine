#pragma once

#include "IBX_Engine.h"

class Sandbox2D : public IBX_Engine::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnEvent(IBX_Engine::Event& e) override;

	void OnUpdate(IBX_Engine::Timestep ts) override;
	void OnImGuiRender() override;
private:

	IBX_Engine::OrthographicCameraController m_CameraController;

	// Temp
	IBX_Engine::Ref<IBX_Engine::Shader> m_Shader;
	IBX_Engine::Ref<IBX_Engine::VertexArray> m_VertexArray;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};