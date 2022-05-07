#include "jnglpch.h"
#include "Framebuffer.h"

#include "Jungle/Rendering/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Jungle
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(specification);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}