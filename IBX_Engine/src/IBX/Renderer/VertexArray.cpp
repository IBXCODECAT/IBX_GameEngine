#include "ibxpch.h"

#include "VertexArray.h"

#include "Renderer.h"
#include "IBX/Renderer//OpenGL//OpenGLVertexArray.h"

namespace IBX_Engine
{
	IBXRef<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}