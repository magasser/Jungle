#include "jnglpch.h"
#include "OpenGLShader.h"


#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Jungle/Core/Verification.h"
namespace Jungle
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			JNGL_CORE_LOG_ERROR("{0}", infoLog.data());
			JNGL_CORE_ASSERT(false, "Vertex shader compilation failure.");

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			JNGL_CORE_LOG_ERROR("{0}", infoLog.data());
			JNGL_CORE_ASSERT(false, "Fragment shader compilation failure.");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			JNGL_CORE_LOG_ERROR("{0}", infoLog.data());
			JNGL_CORE_ASSERT(false, "Shader link compilation failure.");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(const std::string& name, int i)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform1i(location, i);
	}

	void OpenGLShader::UploadUniform(const std::string& name, float f)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform1f(location, f);
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec2& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform2fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec3& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform3fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec4& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniform4fv(location, 1, glm::value_ptr(vec));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat2& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat3& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		JNGL_CORE_ASSERT(location >= 0, "Failed to get uniform location.");

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
}