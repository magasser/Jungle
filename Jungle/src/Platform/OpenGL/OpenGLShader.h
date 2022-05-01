#pragma once

#include <glm/glm.hpp>

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

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; };

		void UploadUniformInt(const std::string& name, int i) const;
		void UploadUniformFloat(const std::string& name, float f) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) const;
		
		void UploadUniformMat2(const std::string& name, const glm::mat2& mat) const;
		void UploadUniformMat3(const std::string& name, const glm::mat3& mat) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& mat) const;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		std::string m_Name;
		uint32_t m_RendererID;
	};
}


