#pragma once

#include "IBX_Engine.h"

class Sandbox2D : public IBX_Engine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnEvent(IBX_Engine::Event& e) override;

	void OnUpdate(IBX_Engine::Timestep ts) override;
	void OnImGuiRender() override;
private:

	IBX_Engine::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = IBX_Engine::Color::Blue;
};