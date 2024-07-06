#include "IBX/Renderer/OpenGL/OpenGLShader.h"

#include <IBX_Engine.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public IBX_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true), m_SquarePosition(0.0f)
	{
		float squareVerts[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0, 0, // Bottom Left
			 0.5f, -0.5f, 0.0f, 1, 0, // Bottom Right
			 0.5f,  0.5f, 0.0f, 1, 1, // Top Right
			-0.5f,  0.5f, 0.0f, 0, 1  // Top Left
		};

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		m_SquareVA = IBX_Engine::VertexArray::Create();
		IBX_Engine::Ref<IBX_Engine::VertexBuffer> squareVB;

		squareVB.reset(IBX_Engine::VertexBuffer::Create(squareVerts, sizeof(squareVerts)));

		IBX_Engine::Ref<IBX_Engine::IndexBuffer> squareIB;
		squareIB.reset(IBX_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		IBX_Engine::BufferLayout squareBufferLayout = {
			{ IBX_Engine::ShaderDataType::Float3, "a_Position" },
			{ IBX_Engine::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareBufferLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);

		m_FlatColorShader = IBX_Engine::Shader::Create("assets/Shaders/Color.glsl");

		auto textureShader = m_ShaderLibrary.Load("assets/Shaders/Texture.glsl");
			
		//m_TextureShader = IBX_Engine::Shader::Create("assets/Shaders/Texture.glsl");

		m_Texture = IBX_Engine::Texture2D::Create("assets/checkerboard.png");
		m_LogoTexture = IBX_Engine::Texture2D::Create("assets/kitty.png");

		const int slot = 0;

		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", slot);
	}

	void OnUpdate(IBX_Engine::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		IBX_Engine::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1 });
		IBX_Engine::RenderCommand::Clear();

		IBX_Engine::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		IBX_Engine::Renderer::Submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

		m_LogoTexture->Bind();
		IBX_Engine::Renderer::Submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));

		IBX_Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(IBX_Engine::Event& e) override
	{
		m_CameraController.OnEvent(e);

		if (e.GetEventType() == IBX_Engine::EventType::WindowResize)
		{
			IBX_Engine::WindowResizeEvent& re = (IBX_Engine::WindowResizeEvent&)e;
		}
	}

private:
	IBX_Engine::ShaderLibrary m_ShaderLibrary;
	
	IBX_Engine::Ref<IBX_Engine::Shader> m_FlatColorShader;

	IBX_Engine::Ref<IBX_Engine::Texture2D> m_Texture, m_LogoTexture;

	IBX_Engine::Ref<IBX_Engine::VertexArray> m_SquareVA;

	IBX_Engine::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = IBX_Engine::Color::Green;

	glm::vec3 m_SquarePosition;

};

class Sandbox : public IBX_Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

IBX_Engine::Application* IBX_Engine::CreateApplication()
{
	return new Sandbox();
}