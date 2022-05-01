#pragma once

#include "../../GLM/glm/glm.hpp"

#include "Jungle/Rendering/Shader.h"

typedef unsigned int GLenum;

namespace Jungle
{
	class JUNGLE_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; };

		void UploadUniform(const std::string& name, int i) const;
		void UploadUniform(const std::string& name, float f) const;
		void UploadUniform(const std::string& name, const glm::vec2& vec) const;
		void UploadUniform(const std::string& name, const glm::vec3& vec) const;
		void UploadUniform(const std::string& name, const glm::vec4& vec) const;

		void UploadUniform(const std::string& name, const glm::mat2& mat) const;
		void UploadUniform(const std::string& name, const glm::mat3& mat) const;
		void UploadUniform(const std::string& name, const glm::mat4& mat) const;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		std::string m_Name;
		uint32_t m_RendererID;
	};
}


