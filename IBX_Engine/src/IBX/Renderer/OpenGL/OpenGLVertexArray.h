#pragma once

#include "IBX/Renderer/VertexArray.h"

namespace IBX_Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const IBXRef<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const IBXRef<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<IBXRef<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const IBXRef<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<IBXRef<VertexBuffer>> m_VertexBuffers;
		IBXRef<IndexBuffer> m_IndexBuffer;
	};
}