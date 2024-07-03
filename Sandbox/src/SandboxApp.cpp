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
		m_VertexArray.reset(IBX_Engine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1, 0, 1, 1,
			 0.5f, -0.5f, 0.0f, 0, 1, 1, 1,
			 0.0f,  0.5f, 0.0f, 1, 1, 0, 1,
		};

		// Vertex Buffer Object
		IBX_Engine::Ref<IBX_Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(IBX_Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

		IBX_Engine::BufferLayout layout = {
			{ IBX_Engine::ShaderDataType::Float3, "a_Position" },
			{ IBX_Engine::ShaderDataType::Float4, "a_Color" },
			//{ ShaderDataType::Float3, "a_Normal"}
		};

		// Vertex Buffer
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		// Index Buffer 
		IBX_Engine::Ref<IBX_Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(IBX_Engine::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		float squareVerts[3 * 7] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		m_SquareVA.reset(IBX_Engine::VertexArray::Create());
		IBX_Engine::Ref<IBX_Engine::VertexBuffer> squareVB;

		squareVB.reset(IBX_Engine::VertexBuffer::Create(squareVerts, sizeof(squareVerts)));

		IBX_Engine::Ref<IBX_Engine::IndexBuffer> squareIB;
		squareIB.reset(IBX_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		IBX_Engine::BufferLayout layout2 = {
			{ IBX_Engine::ShaderDataType::Float3, "a_Position" },
		};

		squareVB->SetLayout(layout2);
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader
		std::string vertexSRC = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;

				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSRC = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				// vpos gets halved and then shifted to the right by 0.5 making the range 0-1
				color = vec4(v_Position * 0.5 + 0.5, 1.0);

				color = v_Color;
			}
		)";

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

		m_Shader.reset(IBX_Engine::Shader::Create(vertexSRC, fragmentSRC));
		m_FlatColorShader.reset(IBX_Engine::Shader::Create(flatColorShaderVertexSRC, flatColorShaderFragmentSRC));
	}

	void OnUpdate(IBX_Engine::Timestep ts) override
	{
		//IBX_CLIENT_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

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

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<IBX_Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", IBX_Engine::Color::Color(m_SquareColor));

		for (int x = 0; x < 25; x++)
		{		
			for (int y = 0; y < 25; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 special_transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				
				IBX_Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, special_transform);
			}
		}
		
		IBX_Engine::Renderer::Submit(m_Shader, m_VertexArray, transform);

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