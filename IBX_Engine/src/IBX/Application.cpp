#include "ibxpch.h"

#include "Application.h"

#include "IBX/Log.h"

#include <Glad/glad.h>

#include "Input.h"

#include "glm/glm.hpp"


namespace IBX_Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		IBX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Unique pointer allows for automatic memory management (no need to manually delete the pointer)
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		auto m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		// OPEN GL

		// Vertex Array Object
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		// Vertex Buffer Object
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0, 1, 2 };

		// Index Buffer Object
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				// vpos gets halved and then shifted to the right by 0.5 making the range 0-1
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{

	}


	void Application::OnEvent(Event& e)
	{
		// Uncomment for debugging
		//	IBX_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);

		// Tell the dispatcher if it sees a WindowCloseEvent to call the OnWindowClose function
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// Go backwards through the layer stack and call OnEvent for each layer
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			// If the event has been handled, break out of the loop
			// If overlays handle the event, the layers should not recieve the event
			if (e.Handled())
				break;
		}

	}
	
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);

		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Clear the screen
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Bind the shader
			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->BeginNewFrame();

			// Update imgui on all layers (from bottom to top)
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender(); // Draw ImGui

			m_ImGuiLayer->EndCurrentFrame();

			// Update the window
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		// Set m_Running to false to stop the application loop
		m_Running = false;
		return true;
	}
}