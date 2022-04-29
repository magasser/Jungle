#pragma once

#include "../../GLM/glm/glm.hpp"

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

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
	};
}
