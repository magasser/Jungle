#include "jnglpch.h"
#include "Texture.h"

#include "Jungle/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Jungle
{
	Ref<Texture2D> Jungle::Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}
