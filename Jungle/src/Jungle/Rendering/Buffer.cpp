#include "jnglpch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "Jungle/Core/Verification.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Jungle
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(vertices, size);
		}
		
		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}