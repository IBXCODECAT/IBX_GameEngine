#include "IBX/Renderer/OpenGL/OpenGLShader.h"

#include <IBX_Engine.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public IBX_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		float squareVerts[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0, 0, // Bottom Left
			 0.5f, -0.5f, 0.0f, 1, 0, // Bottom Right
			 0.5f,  0.5f, 0.0f, 1, 1, // Top Right
			-0.5f,  0.5f, 0.0f, 0, 1  // Top Left
		};

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		m_SquareVA.reset(IBX_Engine::VertexArray::Create());
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

		// Shader
		std::string flatColorShaderVertexSRC = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSRC = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		std::string textureShaderVertexSRC = R"(

			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSRC = R"(

			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_FlatColorShader.reset(IBX_Engine::Shader::Create(flatColorShaderVertexSRC, flatColorShaderFragmentSRC));
		m_TextureShader.reset(IBX_Engine::Shader::Create(textureShaderVertexSRC, textureShaderFragmentSRC));

		m_Texture = IBX_Engine::Texture2D::Create("assets/checkerboard.png");
		m_LogoTexture = IBX_Engine::Texture2D::Create("assets/kitty.png");

		const int slot = 0;

		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", slot);
	}

	void OnUpdate(IBX_Engine::Timestep ts) override
	{
		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		} 
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_K))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}

		IBX_Engine::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1 });
		IBX_Engine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		IBX_Engine::Renderer::BeginScene(m_Camera);


		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		/*
		
		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", IBX_Engine::Color::Color(m_SquareColor));

		for (int x = 0; x < 25; x++)
		{		
			for (int y = 0; y < 25; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				
				IBX_Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		*/

		m_Texture->Bind();
		IBX_Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

		m_LogoTexture->Bind();
		IBX_Engine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));

		IBX_Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(IBX_Engine::Event& event) override
	{

	}

private:
	IBX_Engine::Ref<IBX_Engine::Shader> m_Shader;
	IBX_Engine::Ref<IBX_Engine::VertexArray> m_VertexArray;

	IBX_Engine::Ref<IBX_Engine::Shader> m_FlatColorShader;
	IBX_Engine::Ref<IBX_Engine::Shader> m_TextureShader;

	IBX_Engine::Ref<IBX_Engine::Texture2D> m_Texture, m_LogoTexture;

	IBX_Engine::Ref<IBX_Engine::VertexArray> m_SquareVA;

	IBX_Engine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;

	glm::vec3 m_SquareColor = IBX_Engine::Color::Green;
	
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 1.0f;

	float m_SquareMoveSpeed = 1.0f;

	float m_CameraRotationSpeed = 25.0f;

	glm::vec3 m_SquarePosition;

};

class Sandbox : public IBX_Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

IBX_Engine::Application* IBX_Engine::CreateApplication()
{
	return new Sandbox();
}