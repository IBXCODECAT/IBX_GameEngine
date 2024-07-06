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

	// Temp
	IBX_Engine::Ref<IBX_Engine::Shader> m_FlatColorShader;
	IBX_Engine::Ref<IBX_Engine::Shader> m_TextureShader;

	IBX_Engine::Ref<IBX_Engine::VertexArray> m_VertexArray;

	IBX_Engine::Ref<IBX_Engine::Texture2D> m_Texture;
	IBX_Engine::Ref<IBX_Engine::Texture2D> m_LogoTexture;

	IBX_Engine::ShaderLibrary m_ShaderLibrary;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};