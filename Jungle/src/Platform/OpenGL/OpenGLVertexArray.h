#pragma once

#include "Jungle/Rendering/VertexArray.h"

namespace Jungle
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const VertexBufferRef& vertexBuffer) override;
		virtual void SetIndexBuffer(const IndexBufferRef& indexBuffer) override;

		virtual const std::vector<VertexBufferRef>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const IndexBufferRef& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		std::vector<VertexBufferRef> m_VertexBuffers;
		IndexBufferRef m_IndexBuffer;

	private:
		uint32_t m_RendererID;
	};
}

