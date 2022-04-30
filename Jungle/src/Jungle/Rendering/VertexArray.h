#pragma once

#include <string>

#include "Jungle/Core/Core.h"
#include "Buffer.h"

namespace Jungle
{
	class JUNGLE_API VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const VertexBufferRef& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const IndexBufferRef& indexBuffer) = 0;

		virtual const std::vector<VertexBufferRef>& GetVertexBuffers() const = 0;
		virtual const IndexBufferRef& GetIndexBuffer() const = 0;

		static VertexArrayRef Create();
	};

	using VertexArrayRef = Ref<VertexArray>;
}
