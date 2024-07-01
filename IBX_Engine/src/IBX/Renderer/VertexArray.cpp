#include "ibxpch.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "IBX/Renderer//OpenGL//OpenGLVertexArray.h"

namespace IBX_Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}