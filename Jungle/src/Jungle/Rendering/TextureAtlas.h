#pragma once

#include <glm/glm.hpp>

#include "Jungle/Core/Core.h"
#include "Jungle/Rendering/Texture.h"

namespace Jungle
{
	class JUNGLE_API TextureAtlas
	{
	public:
		virtual ~TextureAtlas() = default;
	};

	class JUNGLE_API TextureAtlas2D : public TextureAtlas
	{
	public:
		TextureAtlas2D(const Ref<Texture2D>& texture, const glm::vec2& cellSize);

		const Ref<Texture>& GetTexture() const { return m_Texture; }
		Ref<SubTexture2D> GetSubTexture(const glm::vec2& coords, const glm::vec2& spriteSize = { 1, 1 });
		
		static Ref<TextureAtlas2D> Create(const std::string& path, const glm::vec2& cellSize);
		static Ref<TextureAtlas2D> Create(const Ref<Texture2D>& texture, const glm::vec2& cellSize);

	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_CellSize;

		//std::unordered_map<glm::vec2, Ref<SubTexture2D>> m_SubTextures;
	};
}