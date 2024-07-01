#include "ibxpch.h"

#include "Buffer.h"
#include "IBX/Renderer/OpenGL//OpenGLBuffer.h"

namespace IBX_Engine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:	IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:	IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indices, count);
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}