#include "ibxpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "IBX/Renderer/OpenGL/OpenGLShader.h"

namespace IBX_Engine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}