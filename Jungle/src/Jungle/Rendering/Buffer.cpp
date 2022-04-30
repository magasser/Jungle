#include "jnglpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Jungle/Core/Verification.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Jungle
{
	VertexBufferRef VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	IndexBufferRef IndexBuffer::Create(uint32_t* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLIndexBuffer>(vertices, size);
		}
		
		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}