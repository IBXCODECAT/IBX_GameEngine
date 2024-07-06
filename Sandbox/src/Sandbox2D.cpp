#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IBX/Renderer/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{

	
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnEvent(IBX_Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnUpdate(IBX_Engine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	IBX_Engine::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1 });
	IBX_Engine::RenderCommand::Clear();

	IBX_Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	IBX_Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);

	IBX_Engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
