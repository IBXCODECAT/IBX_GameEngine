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

		IBX_CORE_INFO("OpenGL Vendor \"{0}\"", (const char*)(glGetString(GL_VENDOR)));
		IBX_CORE_INFO("OpenGL Renderer \"{0}\"", (const char*)(glGetString(GL_RENDERER)));
		IBX_CORE_INFO("OpenGL Version \"{0}\"", (const char*)(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}