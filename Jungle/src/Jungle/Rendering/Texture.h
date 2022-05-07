#pragma once

#include <glm/glm.hpp>

#include "Jungle/Core/Core.h"

namespace Jungle
{
	class JUNGLE_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class JUNGLE_API Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};

	class JUNGLE_API SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D>& GetTexture() const { return m_Texture; }
		const glm::vec2* GetTextureCoords() const { return m_TextureCoords; }

		static Ref<SubTexture2D> Create(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });
		
	private:
		Ref<Texture2D> m_Texture;

		glm::vec2 m_TextureCoords[4];
	};
}
