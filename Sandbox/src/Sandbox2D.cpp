#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IBX/Renderer/OpenGL/OpenGLShader.h"

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Stopped(false), m_Func(func)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
		//IBX_CORE_TRACE("{0} took {1}ms", m_Name, duration);
	}
private:
	const char* m_Name;
	Fn m_Func;

	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = IBX_Engine::Texture2D::Create("assets/Checkerboard.png");
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
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		// Update
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	{
		// Render
		PROFILE_SCOPE("Renderer Prep");
		IBX_Engine::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1 });
		IBX_Engine::RenderCommand::Clear();
	}


	{
		PROFILE_SCOPE("Renderer Draw");
		IBX_Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		IBX_Engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, 36.0f, { 0.8f, 1.0f }, m_SquareColor);
		IBX_Engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, 0.0f, { 0.5f, 0.75f }, IBX_Engine::Color::Red);
		IBX_Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, 0.0f, { 10.0f, 10.0f }, m_CheckerboardTexture);
	}
	
	IBX_Engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}
