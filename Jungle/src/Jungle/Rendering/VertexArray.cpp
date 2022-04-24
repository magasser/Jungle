#include "jnglpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Jungle
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		default:					JNGL_CORE_ASSERT(false, "Unknown renderer API."); return nullptr;
		}
	}
}
