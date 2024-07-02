#include <IBX_Engine.h>

class ExampleLayer : public IBX_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(IBX_Engine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1, 0, 1, 1,
			 0.5f, -0.5f, 0.0f, 0, 1, 1, 1,
			 0.0f,  0.5f, 0.0f, 1, 1, 0, 1,
		};

		// Vertex Buffer Object
		std::shared_ptr<IBX_Engine::VertexBuffer> vertexBuffer;
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
		std::shared_ptr<IBX_Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(IBX_Engine::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		float squareVerts[3 * 7] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		m_SquareVA.reset(IBX_Engine::VertexArray::Create());
		std::shared_ptr<IBX_Engine::VertexBuffer> squareVB;

		squareVB.reset(IBX_Engine::VertexBuffer::Create(squareVerts, sizeof(squareVerts)));

		std::shared_ptr<IBX_Engine::IndexBuffer> squareIB;
		squareIB.reset(IBX_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		IBX_Engine::BufferLayout layout2 = {
			{ IBX_Engine::ShaderDataType::Float3, "a_Position" },
		};

		squareVB->SetLayout(layout2);
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
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
		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentsrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				// vpos gets halved and then shifted to the right by 0.5 making the range 0-1
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader.reset(new IBX_Engine::Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new IBX_Engine::Shader(blueShaderVertexSrc, blueShaderFragmentsrc));
	}

	void OnUpdate() override
	{

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		} 
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}
		else if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}

		IBX_Engine::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1 });
		IBX_Engine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		IBX_Engine::Renderer::BeginScene(m_Camera);

		IBX_Engine::Renderer::Submit(m_BlueShader, m_SquareVA);
		IBX_Engine::Renderer::Submit(m_Shader, m_VertexArray);

		IBX_Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(IBX_Engine::Event& event) override
	{

	}

private:
	std::shared_ptr<IBX_Engine::Shader> m_Shader;
	std::shared_ptr<IBX_Engine::VertexArray> m_VertexArray;

	std::shared_ptr<IBX_Engine::Shader> m_BlueShader;
	std::shared_ptr<IBX_Engine::VertexArray> m_SquareVA;

	IBX_Engine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 0.05f;
	float m_CameraRotationSpeed = 0.5f;

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