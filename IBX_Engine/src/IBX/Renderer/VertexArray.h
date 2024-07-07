#pragma once

#include <memory>
#include "IBX/Renderer/Buffer.h"

namespace IBX_Engine
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const IBXRef<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const IBXRef<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<IBXRef<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const IBXRef<IndexBuffer>& GetIndexBuffer() const = 0;

		static IBXRef<VertexArray> Create();
	};
}