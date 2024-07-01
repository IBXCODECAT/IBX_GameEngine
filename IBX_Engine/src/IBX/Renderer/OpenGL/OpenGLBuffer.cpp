#include "ibxpch.h"

#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace IBX_Engine
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Vertex buffer ///////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		// Create a buffer
		glCreateBuffers(1, &m_RendererID);

		// Bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		// Set buffer data
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// Index buffer ////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		// Create a buffer
		glCreateBuffers(1, &m_RendererID);

		// Bind the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

		// Set buffer data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}