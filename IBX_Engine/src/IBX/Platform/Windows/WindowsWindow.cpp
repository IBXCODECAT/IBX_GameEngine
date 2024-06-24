#include "ibxpch.h"
#include "WindowsWindow.h"

#include "IBX/Events/ApplicationEvent.h"
#include "IBX/Events/MouseEvent.h"
#include "IBX/Events/KeyEvent.h"

#include <glad/glad.h>

namespace IBX_Engine {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		IBX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		IBX_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			IBX_CORE_ASSERT(success, "Could not intialize GLFW!");

			// Set GLFW error callback function
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		// Create window and set opengl context
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// Initialize Glad (OpenGL loader)
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IBX_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks - Window resize
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			
			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Update window size
			data.Width = width;
			data.Height = height;

			// Create and dispatch window resize event
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		// Set GLFW callbacks - Window close
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Create and dispatch window close event
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		// Set GLFW callbacks - Key press
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Switch on key action
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					// GLFW does not provide us with a repeat count, so we'll just assume it's 1
					// If we want that in the future it's possible to extract it
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {

			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Create and dispatch key typed event
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		// Set GLFW callbacks - mouse button
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Switch on mouse button action
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		// Set GLFW callbacks - mouse scroll
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {

			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Create and dispatch mouse scroll event
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		// Set GLFW callbacks - mouse move
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {

			// Get window data from GLFW window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			// Create and dispatch mouse move event
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}