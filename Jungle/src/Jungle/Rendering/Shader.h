#pragma once

#include <string>

#include "Jungle/Core/Core.h"

namespace Jungle
{
	class JUNGLE_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static ShaderRef Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	using ShaderRef = Ref<Shader>;
}
