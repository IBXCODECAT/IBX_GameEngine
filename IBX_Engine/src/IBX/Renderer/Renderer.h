#pragma once

namespace IBX_Engine
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1, DirectX = 2, Vulkan = 3, Metal = 4
	};
	
	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}