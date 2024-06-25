#pragma once

namespace IBX_Engine
{
	class GraphicsContext
	{	
	public:
		// Initialize the graphics context
		virtual void Init() = 0; 
		// Swap the front and back buffers
		virtual void SwapBuffers() = 0;
	};
}