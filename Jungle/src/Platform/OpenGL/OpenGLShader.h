#pragma once

#include "../../GLM/glm/glm.hpp"

#include "Jungle/Rendering/Shader.h"

namespace Jungle
{
	class JUNGLE_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniform(const std::string& name, int i);
		void UploadUniform(const std::string& name, float f);
		void UploadUniform(const std::string& name, const glm::vec2& vec);
		void UploadUniform(const std::string& name, const glm::vec3& vec);
		void UploadUniform(const std::string& name, const glm::vec4& vec);

		void UploadUniform(const std::string& name, const glm::mat2& mat);
		void UploadUniform(const std::string& name, const glm::mat3& mat);
		void UploadUniform(const std::string& name, const glm::mat4& mat);

	private:
		uint32_t m_RendererID;
	};
}


