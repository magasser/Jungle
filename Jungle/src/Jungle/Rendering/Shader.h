#pragma once

#include "Jungle/Core/Core.h"

namespace Jungle
{
	class JUNGLE_API Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}
