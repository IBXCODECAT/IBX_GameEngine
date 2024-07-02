#include "ibxpch.h"

#include "RenderCommand.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace IBX_Engine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}