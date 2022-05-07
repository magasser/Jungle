#include "jnglpch.h"
#include "TextureAtlas.h"

namespace Jungle
{
	TextureAtlas2D::TextureAtlas2D(const Ref<Texture2D>& texture, const glm::vec2& cellSize)
		: m_Texture(texture), m_CellSize(cellSize)
	{

	}

	Ref<TextureAtlas2D> TextureAtlas2D::Create(const std::string& path, const glm::vec2& cellSize)
	{
		const Ref<Texture2D> texture = Texture2D::Create(path);
		return CreateRef<TextureAtlas2D>(texture, cellSize);
	}

	Ref<TextureAtlas2D> TextureAtlas2D::Create(const Ref<Texture2D>& texture, const glm::vec2& cellSize)
	{
		return CreateRef<TextureAtlas2D>(texture, cellSize);
	}

	Ref<SubTexture2D> TextureAtlas2D::GetSubTexture(const glm::vec2& coords, const glm::vec2& spriteSize)
	{
		/*auto it = m_SubTextures.find(coords);
		if (it != m_SubTextures.end())
		{
			return it->second;
		}

		Ref<SubTexture2D> subTexture = SubTexture2D::Create(m_Texture, coords, m_CellSize, spriteSize);
		m_SubTextures.insert({ coords, subTexture });*/

		return SubTexture2D::Create(m_Texture, coords, m_CellSize, spriteSize);
	}
}