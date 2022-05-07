#include "jnglpch.h"
#include "Texture.h"

#include "Jungle/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Jungle
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TextureCoords[0] = { min.x, min.y };
		m_TextureCoords[1] = { max.x, min.y };
		m_TextureCoords[2] = { max.x, max.y };
		m_TextureCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::Create(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		const glm::vec2 min((coords.x * cellSize.x) / (float)texture->GetWidth(), (coords.y * cellSize.y) / (float)texture->GetHeight());
		const glm::vec2 max(((coords.x + spriteSize.x) * cellSize.x) / (float)texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / (float)texture->GetHeight());
		return CreateRef<SubTexture2D>(texture, min, max);
	}
}
