#include "jnglpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Jungle/Core/Verification.h"

#define MAX_SHADER_SOURCES	5

namespace Jungle
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")						return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")	return GL_FRAGMENT_SHADER;

		JNGL_CORE_ASSERT(false, "Unknown shader type '{0}'.", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);

		Compile(shaderSources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;

		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;

		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (!in)
		{
			JNGL_CORE_LOG_ERROR("Failed to load shader file {0}.", filepath);
			return result;
		}

		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);

		in.read(&result[0], result.size());

		in.close();

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		static const char* typeToken = "#type";
		static const size_t typeTokenLength = strlen(typeToken);

		uint64_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			uint64_t eol = source.find_first_of("\r\n", pos);
			JNGL_CORE_ASSERT(eol != std::string::npos, "Syntax error.");

			uint64_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			GLenum glType = ShaderTypeFromString(type);
			JNGL_CORE_VERIFY(glType, "Invalid shader type '{0}'.", type);
			
			uint64_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			
			shaderSources[glType] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		JNGL_CORE_ASSERT(shaderSources.size() <= MAX_SHADER_SOURCES, "Unsupported number of shaders {0} maximum is {1}.", shaderSources.size(), MAX_SHADER_SOURCES);

		std::array<GLenum, MAX_SHADER_SOURCES> glShaderIDs;

		uint32_t programID = glCreateProgram();
		int glShaderIDIndex = 0;

		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const char* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				JNGL_CORE_LOG_ERROR("{0}", infoLog.data());
				JNGL_CORE_ASSERT(false, "Failed to compile shader.");
				break;
			}

			glShaderIDs[glShaderIDIndex++] = shader;
		}

		for (auto id : glShaderIDs)
		{
			glAttachShader(programID, id);
		}

		glLinkProgram(programID);

		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(programID);

			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			JNGL_CORE_LOG_ERROR("{0}", infoLog.data());
			JNGL_CORE_ASSERT(false, "Shader link compilation failure.");

			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(programID, id);
		}

		m_RendererID = programID;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(const std::string& name, int i) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform1i(location, i);
	}

	void OpenGLShader::UploadUniform(const std::string& name, float f) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform1f(location, f);
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec2& vec) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform2fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec3& vec) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform3fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec4& vec) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform4fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat2& mat) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat3& mat) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& mat) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
}