#include "ibxpch.h"
#include "Texture.h"

#include "IBX/Renderer/Renderer.h"
#include "IBX/Renderer/OpenGL/OpenGLTexture.h"

namespace IBX_Engine
{
	IBXRef<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateIBXRef<OpenGLTexture2D>(width, height);
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IBXRef<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    IBX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateIBXRef<OpenGLTexture2D>(path);
		}

		IBX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}