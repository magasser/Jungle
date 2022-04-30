#pragma once

#include <string>

#include "Jungle/Core/Core.h"

namespace Jungle
{
	class JUNGLE_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class JUNGLE_API Texture2D : public Texture
	{
	public:
		static Texture2DRef Create(const std::string& path);
	};

	using Texture2DRef = Ref<Texture2D>;
}
