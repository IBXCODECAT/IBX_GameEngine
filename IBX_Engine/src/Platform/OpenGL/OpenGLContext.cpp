#include "ibxpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace IBX_Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		IBX_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		// Initialize Glad (OpenGL loader)
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IBX_CORE_ASSERT(status, "Failed to initialize Glad!");

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}