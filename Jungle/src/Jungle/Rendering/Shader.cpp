#include "jnglpch.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Jungle/Core/Verification.h"
#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"



namespace Jungle
{
	ShaderRef Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}