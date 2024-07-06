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

	float squareVerts[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0, 0, // Bottom Left
		 0.5f, -0.5f, 0.0f, 1, 0, // Bottom Right
		 0.5f,  0.5f, 0.0f, 1, 1, // Top Right
		-0.5f,  0.5f, 0.0f, 0, 1  // Top Left
	};

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	m_VertexArray = IBX_Engine::VertexArray::Create();

	IBX_Engine::Ref<IBX_Engine::VertexBuffer> squareVB;
	squareVB = IBX_Engine::VertexBuffer::Create(squareVerts, sizeof(squareVerts));

	IBX_Engine::Ref<IBX_Engine::IndexBuffer> squareIB;
	squareIB = IBX_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

	IBX_Engine::BufferLayout squareBufferLayout = {
		{ IBX_Engine::ShaderDataType::Float3, "a_Position" },
		{ IBX_Engine::ShaderDataType::Float2, "a_TexCoord" }
	};

	squareVB->SetLayout(squareBufferLayout);
	m_VertexArray->AddVertexBuffer(squareVB);
	m_VertexArray->SetIndexBuffer(squareIB);

	m_FlatColorShader = IBX_Engine::Shader::Create("assets/Shaders/Color.glsl");

	auto textureShader = m_ShaderLibrary.Load("assets/Shaders/Texture.glsl");

	//m_TextureShader = IBX_Engine::Shader::Create("assets/Shaders/Texture.glsl");

	m_Texture = IBX_Engine::Texture2D::Create("assets/checkerboard.png");
	m_LogoTexture = IBX_Engine::Texture2D::Create("assets/kitty.png");

	const int slot = 0;

	std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(textureShader)->Bind();
	std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", slot);
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

	IBX_Engine::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	IBX_Engine::Renderer::Submit(textureShader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

	m_LogoTexture->Bind();
	IBX_Engine::Renderer::Submit(textureShader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));

	IBX_Engine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
