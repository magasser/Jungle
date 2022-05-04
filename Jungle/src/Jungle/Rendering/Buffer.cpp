#include "jnglpch.h"
#include "Buffer.h"

#include "Jungle/Rendering/Renderer.h"
#include "Jungle/Core/Verification.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Jungle
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(size);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* vertices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(vertices, count);
		}
		
		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}